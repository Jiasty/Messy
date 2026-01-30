#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>


class Person 
{
public:
	virtual void BuyTicket()
	{
		std::cout << "买票-全价" << std::endl;
	}

	// ~Person()
	virtual ~Person() // 建议析构函数以后就写为虚函数，防止资源泄露
	{
		std::cout << "~Person()" << std::endl;
	}
};

class Student : public Person
{
public:
	virtual void BuyTicket()
	{
		std::cout << "买票-半价" << std::endl;
	}

	virtual ~Student()
	{
		delete[] _ptr;
		std::cout << "delete[] _ptr" << std::endl;
		std::cout << "~Student()" << std::endl;
	}

private:
	int _id;
	int* _ptr = new int[10];
};

void Func(Person& p)
{
	// 不同的对象执行相同的事情，结果不同
	p.BuyTicket(); // 基类调用虚函数
}

void test1()
{
	Person p;
	Student s;

	Func(p);
	Func(s);
}

void test3()
{
	/*Person p;
	Student s;*/

	// std::cout <<"************" << std::endl;

	Person* p1 = new Person;
	Person* p2 = new Student;

	// 期望指向父类对象调父类析构，指向子类调子类析构
	delete p1;
	std::cout << std::endl;
	delete p2;
	// p1->destructor + operator delete(p1)
	// p2->destructor + operator delete(p2)
}

// 协变
class A
{
public:
	virtual A& func1()
	{
		std::cout << "A&" << std::endl;
		return *this;
	}

	virtual A* func2()
	{
		std::cout << "A*" << std::endl;
		return nullptr;
	}


private:
	int _a;
};

class B : public A
{
public:
	virtual B& func1()
	{
		std::cout << "B&" << std::endl;
		return *this;
	}

	virtual B* func2()
	{
		std::cout << "B*" << std::endl;
		return nullptr;
	}
private:
	int _b;
};

void test2()
{
	A a;
	a.func1();
	a.func2();

	B b;
	b.func1();
	b.func2();
}


// final 和 override关键字
class First
{
public:
	virtual void funcNotOverride() final
	{
		std::cout << "This func can not be overrrided!" << std::endl;
	}

	virtual void testOverride()
	{
		std::cout << "class First" << std::endl;
	}

};

class Next1 : public First
{
public:
	/*virtual void funcNotOverride()
	{
		std::cout << "Override!" << std::endl;
	}*/

	virtual void testOverride() override
	{
		std::cout << "class First" << std::endl;
	}
};

class Last final
{};

//class Next2 : public Last
//{};



// 多态原理
class Base1
{
public:
	virtual void test()
	{
		std::cout << "test()" << std::endl;
	}
private:
	// 此处含有虚函数表指针(虚表指针)
	int _a = 10;
	char _x = 'a';
};

// 针对上面的代码我们做出以下改造
// 1.我们增加一个派生类Derive去继承Base2
// 2.Derive中重写Func1
// 3.Base2再增加一个虚函数Func2和一个普通函数Func3
class Base2
{
public:
	virtual void Func1()
	{
		std::cout << "Base2::Func1()" << std::endl;
	}
	virtual void Func2()
	{
		std::cout << "Base2::Func2()" << std::endl;
	}
	void Func3()
	{
		std::cout << "Base2::Func3()" << std::endl;
	}
private:
	int _a = 1;
};
class Derive2 : public Base2
{
public:
	virtual void Func1()
	{
		std::cout << "Derive::Func1()" << std::endl;
	}
private:
	int _d = 2;
};

void Func(Base2* b)
{
	b->Func1();
}

// 普通调用，编译时就确定，是哪个类型的对象就去调对应的虚函数
void Func2(Base2 b)
{
	b.Func1();
}

void test4()
{
	Base1 base;
	std::cout << sizeof(base) << std::endl;

	Base2 b;
	Func(&b);

	Derive2 d;
	Func(&d);

	Func2(d); // 非多态
}


// 单继承中的虚函数表
class Base 
{
public:
	virtual void func1() 
	{ 
		std::cout << "Base::func1" << std::endl; 
	}
	virtual void func2() 
	{ 
		std::cout << "Base::func2" << std::endl; 
	}
private:
	int a;
};

class Derive :public Base 
{
public:
	virtual void func1() 
	{ 
		std::cout << "Derive::func1" << std::endl; 
	}
	virtual void func3() 
	{ 
		std::cout << "Derive::func3" << std::endl; 
	}
	virtual void func4() 
	{ 
		std::cout << "Derive::func4" << std::endl; 
	}
private:
	int b;
};

void test5()
{
	Base b;
	Derive d;
}

// @@@打印虚函数表
typedef void (*VFPTR)();
void PrintVirtualFuncTable(VFPTR vTable[])
{
	// 依次取虚表中的虚函数指针打印并调用。调用就可以看出存的是哪个函数
	std::cout << " 虚表地址>" << vTable << std::endl;

	for (int i = 0; vTable[i] != nullptr; i++)
	{
		printf(" 第%d个虚函数地址 :0X%x,->", i, vTable[i]);
		VFPTR f = vTable[i];
		f();
	}

	std::cout << std::endl;
}

void test6()
{
	Base b;
	Derive d;

	// 思路：取出b、d对象的头4bytes，就是虚表的指针，虚函数表本质是一个存虚函数指针的指针数组，这个数组最后面放了一个nullptr
	// 1.先取b的地址，强转成一个int*的指针
	// 2.再解引用取值，就取到了b对象头4bytes的值，这个值就是指向虚表的指针
	// 3.再强转成VFPTR*，因为虚表就是一个存VFPTR类型(虚函数指针类型)的数组。
	// 4.虚表指针传递给PrintVTable进行打印虚表
	// 5.需要说明的是这个打印虚表的代码经常会崩溃，因为编译器有时对虚表的处理不干净，
	//   虚表最后面没有放nullptr，导致越界，这是编译器的问题。
	//   我们只需要点目录栏的 - 生成 - 清理解决方案，再编译就好了。
	VFPTR* vfptrb = (VFPTR*)(*(int*)&b);
	PrintVirtualFuncTable(vfptrb);

	VFPTR* vfptrd = (VFPTR*)(*(int*)&d);
	PrintVirtualFuncTable(vfptrd);
}


// 抽象类 
class Car
{
public:
	virtual void Drive() = 0;
};

class Audi : public Car
{
public:
	virtual void Drive()
	{
		std::cout << "virtual void Drive()" << std::endl;
	}
};

void test7()
{
	// Car c1; 不可实例化出对象
	Audi a4;
	a4.Drive();

	Car* c = &a4;
	c->Drive();
}


 
// 多继承中的虚函数表
//class BaseClass1 
//{
//public:
//	virtual void func1() { std::cout << "BaseClass1::func1" << std::endl; }
//	virtual void func2() { std::cout << "BaseClass1::func2" << std::endl; }
//private:
//	int b1;
//};
//class BaseClass2 
//{
//public:
//	virtual void func1() { std::cout << "BaseClass2::func1" << std::endl; }
//	virtual void func2() { std::cout << "BaseClass2::func2" << std::endl; }
//private:
//	int b2;
//};
//class DeriveClass : public BaseClass1, public BaseClass2 {
//public:
//	virtual void func1() { std::cout << "DeriveClass::func1" << std::endl; }
//	virtual void func3() { std::cout << "DeriveClass::func3" << std::endl; }
//private:
//	int d1;
//};
//typedef void(*VFPTR) ();
//void PrintVTable(VFPTR vTable[])
//{
//	std::cout << " 虚表地址>" << vTable << std::endl;
//	for (int i = 0; vTable[i] != nullptr; ++i)
//	{
//		printf(" 第%d个虚函数地址 :0X%x,->", i, vTable[i]);
//		VFPTR f = vTable[i];
//		f();
//	}
//	std::cout << std::endl;
//}
//void test8()
//{
//	DeriveClass d;
//	VFPTR* vTableb1 = (VFPTR*)(*(int*)&d);
//	PrintVTable(vTableb1);
//
//	VFPTR* vTableb2 = (VFPTR*)(*(int*)((char*)&d + sizeof(BaseClass1)));
//	PrintVTable(vTableb2);
//}


int main()
{
	// test1();
	// test2();
	// test3();
	// test4();
	// test5();
	// test6();
	// test7();
	// test8();

	return 0;
}
