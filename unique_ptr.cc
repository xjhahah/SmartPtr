#include <iostream>

using namespace std;

template <class T>

class UniquePtr
{
public:
	UniquePtr(T* ptr=nullptr)
	{}
	~UniquePtr()
	{
		if (_ptr)
			delete _ptr;
	}
private:
	//C++98防拷贝方式，将重载赋值运算符和拷贝构造设置为私有
	UniquePtr& operator =(UniquePtr<T>& up);
	UniquePtr(UniquePtr<T>const& up);
	//C++11防拷贝方式
	UniquePtr& operator =(UniquePtr<T>& up)=delete;
	UniquePtr(UniquePtr<T>const& up)=delete;
private:
	T* _ptr;
};
int main()
{

	return 0;
}
