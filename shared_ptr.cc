#include <iostream>
#include <mutex>
using namespace std;

template <class T>

class SharedPtr
{
public:
	SharedPtr(T* ptr=nullptr)
		:_ptr(ptr)
		,_pCount(new int(1))
		,_pMutex(new mutex)
	{
		if (_ptr == nullptr)
		{
			*_pCount = 0;
		}
	}
	SharedPtr(const SharedPtr<T>& sp)
		:_ptr(sp._ptr)
		, _pCount(sp._pCount)
		, _pMutex(sp._pMutex)
	{ 
		//如果是一个空指针对象，则不用加引用计数，否则就要将 pCount++
		if (_ptr)
			AddCount();
	}
	SharedPtr<T>&operator=(const SharedPtr<T>& sp)
	{
		if (_ptr != sp._ptr)
		{
			//释放旧空间
			Release();

			_ptr = sp._ptr;
			_pCount = sp._pCount;
			_pMutex = sp._pMutex;
			if (_ptr)
				AddCount();
		}
		return *this;
	}
	int UseCount() 
	{ 
		return *_pCount; 
	}
	int AddCount()
	{
		_pMutex->lock();
		++(*_pCount);
		_pMutex->unlock();
		return *_pCount;
	}
	int SubCount()
	{
		_pMutex->lock();
		--(*_pCount);
		_pMutex->unlock();
		return *_pCount;
	}
	void Release()
	{
		if (_ptr && 0 == SubCount())
		{
			delete _ptr;
			delete _pCount;
			delete _pMutex;
		}
	}
	T* operator->()
	{
		return _ptr;
	}
	T& operator*()
	{
		return *_ptr;
	}
	~SharedPtr()
	{
		Release();
	}
private:
	T* _ptr;
	int* _pCount; //引用计数
	mutex* _pMutex; //互斥锁
};
struct Date
{
	int year;
	int month;
	int day;
};
int main()
{
	SharedPtr<int> sp1(new int(10));
	SharedPtr<int> sp2(sp1);
	*sp2 = 20;
	cout << sp1.UseCount() << endl;
	cout << sp2.UseCount() << endl;
	SharedPtr<int> sp3(new int(10));
	sp2 = sp3;
	cout << sp1.UseCount() << endl;
	cout << sp2.UseCount() << endl;
	cout << sp3.UseCount() << endl;
	sp1 = sp3;
	cout << sp1.UseCount() << endl;
	cout << sp2.UseCount() << endl;
	cout << sp3.UseCount() << endl;

	return 0;
}
