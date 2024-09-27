#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
















//2、拷贝构造显示声明后，编译器不生成默认构造函数。
//class A
//{
//public:
//	A(const A& a)
//	{}
//
//private:
//	int _id;
//};
//
//int main()
//{
//	std::cout << 1;
//	//只有拷贝构造时
//	//A a1(); //编译可通过,是一个函数声明（而不是对象实例化）。
//
//	//A a2; //无法构造
//
//	return 0;
//}


//1、空类大小、空指针引用问题
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