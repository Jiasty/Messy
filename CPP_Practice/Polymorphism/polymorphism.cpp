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

void test4()
{
	Base1 base;
	std::cout << sizeof(base) << std::endl;

	Base2 b;
	Func(&b);

	Derive2 d;
	Func(&d);
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

// 打印虚函数表
typedef void (*VFPTR)();
void PrintVirtualFuncTable(VFPTR vTable[])
{

}

int main()
{
	// test1();
	// test2();
	// test3();
	// test4();
	test5();

	return 0;
}
