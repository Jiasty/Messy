#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>


//3、赋值运算符重载
class MyMath
{
public:

	MyMath(int x = 0, int y = 0, int z = 0)
		:_x(x), _y(y), _z(z)
	{}

	//以一个已经存在的对象来覆盖另一个已存在的对象，不希望m被修改，所以要加const
	MyMath& operator=(const MyMath& m)
	{
		//判断为不同对象才赋值
		if (this != &m)
		{
			_x = m._x;
			_y = m._y;
			_z = m._z;
		}

		return *this;
	}

	//后置++重载
	MyMath operator++(int)
	{
		MyMath temp(*this);
		++_x;
		++_y;
		++_z;

		return temp;
	}
	//前置++重载
	MyMath& operator++()
	{
		_x++;
		_y++;
		_z++;
		return *this;
	}


private:
	int _x;
	int _y;
	int _z;
};

int main()
{
	MyMath m1, m2;
	m1++;

	m2 = m1;

	return 0;
}



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