#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

class A
{
public:
	A(const A& a)
	{}

private:
	int _id;
};

int main()
{
	std::cout << 1;
	//只有拷贝构造时
	//A a1(); //编译可通过

	//A a2; //无法构造

	return 0;
}



//空类大小、空指针引用问题
//class Date
//{};
//
//class A
//{
//public:
//	void func()
//	{
//		return;
//	}
//};
//
//int main()
//{
//	std::cout << "空类的大小为" << sizeof(Date) << std::endl;
//
//	A* p = nullptr;
//	p->func(); //正常运行，func()在公共区域，没有在类里面，编译时就已经确认地址。
//	return 0;
//}