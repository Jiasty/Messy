#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <memory>
#include <exception>
#include <thread>
#include <mutex>

#include <string>
#include <list>

#include "mySharedPtr.h"


// 繁琐的try-catch控制，保证内存安全
int div()
{
	int a, b;
	std::cin >> a >> b;
	if (b == 0)
		throw std::invalid_argument("除0错误");
	return a / b;
}

void Func()
{
	// 1、如果p1这里new 抛异常会如何？
	// 2、如果p2这里new 抛异常会如何？
	// 3、如果div调用这里又会抛异常会如何？
	// int* p1 = new int;
	// int* p2 = new int;
	// std::cout << div() << std::endl;
	// delete p1;
	// delete p2;

	int* p1 = new int[10];
	int* p2 = nullptr;
	try
	{
		p2 = new int[10];
		try
		{
			std::cout << div() << std::endl;
		}
		catch (...)
		{
			delete[] p1;
			p1 = nullptr;
			std::cout << "delete[] p1" << std::endl;
			delete[] p2;
			p2 = nullptr;
			std::cout << "delete[] p2" << std::endl;
			throw;
		}
	}
	catch (...)
	{
		delete[] p1;
		p1 = nullptr;
		std::cout << "delete[] p1" << std::endl;

		throw;
	}

	delete[] p1;
	std::cout << "delete[] p1" << std::endl;
	delete[] p2;
	std::cout << "delete[] p2" << std::endl;
}
void test1()
{
	try
	{
		Func();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}


// 智能指针(RAII机制)
template<typename T>
class SmartPtr
{
public:
	SmartPtr(T* ptr = nullptr)
		:_ptr(ptr)
	{}

	~SmartPtr()
	{
		delete[] _ptr;
		std::cout << "~SmartPtr(): delete[] _ptr;" << std::endl;
	}

	T* GetPtr() const 
	{
		return _ptr;
	}

	// 运算符重载 -> * []
	T& operator[](size_t i)
	{
		return _ptr[i];
	}

private:
	T* _ptr;
};

void test2()
{
	SmartPtr<int> p1(new int[3]{1, 2, 3});

	// SmartPtr<int> p2(p1); // 拷贝会重释放
}


// 利用智能指针RAII机制改进上述异常控制
int Division()
{
	int a, b;
	std::cin >> a >> b;
	if (b == 0)
		throw std::invalid_argument("除0错误");
	return a / b;
}

void Func2()
{
	SmartPtr<int> p1(new int[10]);
	SmartPtr<int> p2(new int[10]);
	
	Division();
}
void test3()
{
	try
	{
		Func2();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (...)
	{}
}


// C++库中的智能指针
class A
{
public:

	A(int a = 0, char x = 'a')
		:_a(a)
		,_x(x)
	{}

	~A()
	{
		std::cout << "~A()" << std::endl;
	}

	void func()
	{
		std::cout << "void func()" << std::endl;
	}
private:
	int _a = 1;
	char _x = 'a';
};

void test4()
{
	std::auto_ptr<int> p1(new int[10]);
	// 转移管理权，极其不合理
	std::auto_ptr<int> p2(p1);

	//////////////////////////////////

	std::unique_ptr<A> p3(new A);
	// 不支持拷贝构造和赋值
	// std::unique_ptr<A> p4(p3);
	// std::unique_ptr<A> p5 = p3;

	A* ptr = p3.get();
	std::cout << "raw ptr: " << ptr << std::endl;

	std::unique_ptr<A[]> p4(new A[10]);

	//////////////////////////////////

	std::shared_ptr<A> p5(new A);
	// 等价std::shared_ptr<A> p5 = std::make_shared<A>();
	// std::shared_ptr<A> p5 = new A; // 不支持隐式类型转换

	std::shared_ptr<A> p6(p5);
	std::cout << "shared_ptr count: " << p5.use_count() << std::endl;

}


// 自己实现的智能指针
void test5()
{
	Jiasty::shared_ptr<A> p1(new A(11, 'x'));
	Jiasty::shared_ptr<A> p2(p1);

	Jiasty::shared_ptr<A> p3(new A(2, 'y'));
	std::cout << "p3 count: " << p3.use_count() << std::endl;

	p3 = p1;
	std::cout << "p3 count: " << p3.use_count() << std::endl;

	(*p1).func();
	p1->func(); // (p1->)->func()

}


// 智能指针shared_ptr拷贝的线程安全问题  // TODO

// 智能指针对象本身拷贝析构是线程安全的
// 底层引用计数加减是线程安全的
// 指向的资源访问不是线程安全的

std::mutex mt;

void Insert(Jiasty::shared_ptr<std::list<int>> sp, int times)
{
	std::cout << "use_count: " << sp.use_count() << std::endl;

	for (int i = 0; i < times; i++)
	{
		Jiasty::shared_ptr<std::list<int>>& cy1(sp);
		Jiasty::shared_ptr<std::list<int>>& cy2(sp);
		Jiasty::shared_ptr<std::list<int>>& cy3(sp);
		Jiasty::shared_ptr<std::list<int>>& cy4(sp);

		mt.lock();
		sp->emplace_back(i);
		mt.unlock();
	}
}

void test6()
{
	Jiasty::shared_ptr<std::list<int>> sp(new std::list<int>);
	std::cout << sp.use_count() << std::endl;
	
	std::thread t1(Insert, sp, 1000000);
	std::thread t2(Insert, sp, 2000000);
	
	t1.join();
	t2.join();
	
	std::cout << sp->size() << std::endl;
	std::cout << sp.use_count() << std::endl;
}


// shared_ptr的循环引用缺陷
struct Node
{
	~Node()
	{
		std::cout << "~Node()" << std::endl;
	}


	int _val;
	// std::shared_ptr<Node> _next;
	// std::shared_ptr<Node> _prev;
	std::weak_ptr<Node> _next;
	std::weak_ptr<Node> _prev;
};

void test7()
{
	std::shared_ptr<Node> l1(new Node);
	std::shared_ptr<Node> l2(new Node);

	std::cout << l1.use_count() << std::endl;
	std::cout << l2.use_count() << std::endl;

	l1->_next = l2;
	l2->_prev = l1;

	std::cout << l1.use_count() << std::endl;
	std::cout << l2.use_count() << std::endl;
}


// 定制删除器
template<class T>
struct FreeFunc
{
	void operator()(T* ptr)
	{
		std::cout << "free:" << ptr << std::endl;
		free(ptr);
	}
};
template<class T>
struct DeleteArrayFunc
{
	void operator()(T* ptr)
	{
		std::cout << "delete[]" << ptr << std::endl;
		delete[] ptr;
	}
};

void test8()
{
	// 仿函数的删除器
	FreeFunc<int> freeFunc;
	std::shared_ptr<int> sp1((int*)malloc(4), freeFunc);

	DeleteArrayFunc<int> deleteArrayFunc;
	std::shared_ptr<int> sp2((int*)malloc(4), deleteArrayFunc);

	// lambda
	Jiasty::shared_ptr<A> sp4(new A[10], [](A* p) {delete[] p; });
	std::shared_ptr<FILE> sp5(fopen("test.txt", "w"), [](FILE* p) {fclose(p); });

	Jiasty::shared_ptr<A> sp6(new A);
}

int main()
{
	// test1();
	// test2();
	// test3();
	// test4();
	// test5();
	// test6();
	// test7();
	test8();

	return 0;
}
