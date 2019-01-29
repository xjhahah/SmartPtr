#include <iostream>

using namespace std;

template <class T>
class AutoPtr
{
public:
	AutoPtr(T* ptr=nullptr)
	{}

	AutoPtr(AutoPtr<T>& ap) //将原来的资源转移到新的对象，跟自己脱离关系
		:_ptr(ap._ptr)
	{
		ap._ptr = nullptr;
	}
	AutoPtr<T>& operator=(AutoPtr<T> ap)
	{
		//确认是不是自己给自己赋值
		if (this != &ap)
		{
			//释放当前对象资源
			if (_ptr)
				delete _ptr;
			_ptr = ap._ptr;
			ap._ptr = nullptr;
		}
		return *this;
	}
	T& operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
	~AutoPtr()
	{
		if (_ptr)
			delete _ptr;
	}
private:
	T* _ptr;
};

struct Date
{
	int year;
	int month;
	int day;
};
int main()
{
	AutoPtr<Date> ap(new Date);
	
	AutoPtr<Date> copy(ap);
	//copy->month = 1;
	ap->year = 2019;
	cout << copy->month << ap->year << endl;
	return 0;
}
