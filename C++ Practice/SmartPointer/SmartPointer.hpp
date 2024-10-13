#pragma once

#include<iostream>

template<class T>
class Shared_ptr
{
public:
	Shared_ptr(T* ptr)
		:_ptr(ptr)
		, _pcount(new int(1))
	{

	}

	Shared_ptr(const T& ptr)
		:_ptr(ptr)
		, _pcount(ptr._pcount)
	{
		PcountPP();
	}
	PcountPP()
	{

	}


private:
	T* _ptr;
	int* _pcount;
};
