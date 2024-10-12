#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>

template<class T>
class Shared_ptr
{
public:
	Shared_ptr(const T& ptr)
		:_ptr(ptr)
		,_pcount(new int(1))
	{

	}

private:
	T* _ptr;
	int* _pcount;
};
