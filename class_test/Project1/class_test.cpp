#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

class Date
{};

class A
{
public:
	void func()
	{
		return;
	}
};

int main()
{
	std::cout << 1;
	std::cout << sizeof(Date) << std::endl;

	A* p = nullptr;
	//p->func(); //正常运行，func()在公共区域，没有在类里面，编译时就已经确认地址。
	//vs无法运行成功也许是MSVC编译器检测太严格。
	return 0;
}