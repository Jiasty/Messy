#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <algorithm>
#include <functional>

#include <string>
#include <vector>

template<class T1, class T2>
void F(T1 t1, T2 t2)
{
	decltype(t1 * t2) ret;
	std::cout << typeid(ret).name() << std::endl;
}

void test1()
{
	// 1、列表初始化
	int c{ 11 };
	std::cout << c << std::endl;

	int arr[] = { 1,2,3,4,5 };
	for (auto e : arr)
		std::cout << e << " ";
	std::cout << std::endl;

	// 2、initializer_list
	auto il = { 10, 20, 30 };
	std::cout << typeid(il).name() << std::endl;

	std::initializer_list<int> il2 = { 1, 2, 3 };
	std::cout << sizeof(il2) << std::endl;

	// 构造
	std::vector<int> v1({ 1, 2, 3 });
	// 隐式类型转换
	std::vector<int> v2 = { 1, 2, 3 };

	// 3、auto
	int i = 1;
	auto j = i;
	auto& k = i;
	j++;
	k++;

	// 4、decltype
	std::vector<int>::iterator it1;
	// typeid单纯推出字符串，不可定义对象
	std::cout << typeid(it1).name() << std::endl;
	// decltype就可以推导现有对象的类型，用它来声明新对象
	decltype(it1) it2;
	std::cout << typeid(it2).name() << std::endl;

	// 5、nullptr
	nullptr;
	NULL;
}


// 6、右值引用与移动语义
void test2()
{
	
}


void Fun(int& x) { std::cout << "左值引用" << std::endl; }
void Fun(const int& x) { std::cout << "const 左值引用" << std::endl; }
void Fun(int&& x) { std::cout << "右值引用" << std::endl; }
void Fun(const int&& x) { std::cout << "const 右值引用" << std::endl; }
// 7、万能引用
template<typename T>
void PerfectForward(T&& t)
{
	// 8、完美转发
	// Fun(t); // t为右指引用对象，为左值
	Fun(std::forward<T>(t)); // 完美转发保持t的原生类型属性，即保留实参的属性
}
void test3()
{
	PerfectForward(10);           // 右值
	int a;
	PerfectForward(a);            // 左值
	PerfectForward(std::move(a)); // 右值 
	const int b = 8;
	PerfectForward(b);      // const 左值 
	PerfectForward(std::move(b)); // const 右值 
}

// 10、lambda表达式
void test4()
{
	// auto + lambda对象名字 + 捕捉列表 + 参数列表 + mutable + 返回值类型 + 函数体

	// 完整写法
	auto add_int1 = [](int a, int b)mutable->int {return a + b; };
	// 捕捉列表不写可省略mutable
	auto add_int2 = [](int a, int b)->int {return a + b; };
	// 返回值类型可省略
	auto add_int3 = [](int a, int b) {return a + b; };
	auto add_int4 = [](int a, int b)mutable {return a + b; };
	// 没有参数，参数列表可省略
	auto tmp = [] {std::cout << "hello world" << std::endl; };


	std::cout << add_int1(1, 2) << std::endl;
	std::cout << add_int2(1, 2) << std::endl;
	std::cout << add_int3(1, 2) << std::endl;
	std::cout << add_int4(1, 2) << std::endl;
	tmp();


	struct Goods
	{
		std::string _name; // 名字
		double _price; // 价格
		int _evaluate; // 评价
		Goods(const char* str, double price, int evaluate)
			:_name(str)
			, _price(price)
			, _evaluate(evaluate)
		{}
	};

	std::vector<Goods> v = { { "苹果", 2.1, 5 }, { "香蕉", 3, 4 }, { "橙子", 2.2,
		3 }, { "菠萝", 1.5, 4 } };

	std::sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2)
		{
			return g1._price < g2._price; 
		});


	std::cout << "**********************************" << std::endl;

	
	int a = 1, b = 2;
	auto swap1 = [](int& x, int& y)
	{
		int tmp = x;
		x = y;
		y = tmp;
	};
	swap1(a, b);
	std::cout << a << " " << b << std::endl;

	// 传值捕捉列表
	// 捕捉a b对象给lambda
	// mutable可以修改传值捕捉对象，不过是修改拷贝的a b，此场景不多,mutable用处不大
	auto swap2 = [a, b]() mutable
	{
		int tmp = a;
		a = b;
		b = tmp;
	};
	swap2();
	std::cout << a << " " << b << std::endl;

	// 引用捕捉列表
	auto swap3 = [&a, &b]()
	{
		int tmp = a;
		a = b;
		b = tmp;
	};
	swap3();
	std::cout << a << " " << b << std::endl;

	std::cout << "**********************************" << std::endl;

	// 捕捉列表进阶
	{
		int a = 1, b = 2, c = 3, d = 4;

		// 传值捕捉所有父作用域变量
		auto func1 = [=]()
		{
			return a + b + c * d;
		};
		std::cout << func1() << std::endl;

		// 引用捕捉所有父作用域变量
		auto func2 = [&]()
		{
			a++;
			b++;
			c++;
			d++;
		};
		func2();
		std::cout << a << b << c << d << std::endl;

		// 混合捕捉
		// 除了c d其他都传引用捕捉
		auto func3 = [&, c, d]()
		{
			a++;
			b++;
			return a + b + c * d;
		};
		std::cout << func3() << std::endl;
		// 除了a b其他都传引用捕捉
		auto func4 = [=, &c, &d]()
		{
			c++;
			d++;
			return a + b + c * d;
		};
		std::cout << func4() << std::endl;
	}
}


// 11、可变参数模板--递归法
void _CppPrintf()
{
	std::cout << "End" << std::endl;
}

template<typename T, typename... Args>
void _CppPrintf(const T& first, Args... rest)
{
	std::cout << first << " "; // 处理第一个    
	_CppPrintf(rest...); // 递归调用，把剩下的传下去
}

template<typename ...Args>
void CppPrintf(Args... args) // args是一个“函数参数包”(Function Parameter Pack)
{ 
	// 获取参数包里的参数个数
	std::cout << "ArgumentsSize:" << sizeof...(args) << std::endl;
	_CppPrintf(args...);
}
void test5()
{
	CppPrintf(1);
	CppPrintf(1, "111");
	CppPrintf(1, "111", 'c');
}

// 12、可变参数模板--逗号表达式法
template<typename T>
void printArg(T t)
{
	std::cout << t << " ";
}

template<typename... Args>
void expand(Args... args)
{
	// 逗号表达式 (exp1, exp2) 会执行 exp1，然后返回 exp2
	// 这里利用数组初始化的顺序，强行执行 printArg(args)
	int dummy[] = { 0, (printArg(args), 0)... };
}

// 13、包装器--function
// 不是定义可调用对象(函数指针、仿函数对象、lambda表达式)，而是包装它们
int Add(int a, int b)
{
	return a + b;
}

struct Functor
{
	int operator() (int a, int b)
	{
		return a + b;
	}
};

class Plus
{
public:
	static int AddII(int a, int b)
	{
		return a + b;
	}

	double AddDD(double a, double b)
	{
		return a + b;
	}
};

void test6()
{
	std::function<int(int, int)> f1;

	// std::function<int(int, int)> f2(Add);
	std::function<int(int, int)> f2 = Add;

	std::function<int(int, int)> f3 = Functor();

	std::function<int(int, int)> f4 = [](int a, int b) {return a + b; };

	// 重载了(),本质就是仿函数, 当成函数一样用，只不过套了一层壳
	std::cout << f2(1, 2) << std::endl;
	std::cout << f3(1, 2) << std::endl;
	std::cout << f4(1, 2) << std::endl;

	std::cout << "*********************************" << std::endl;

	// 包装器封装非成员函数
	std::function<int(int, int)> f5 = Plus::AddII;
	std::cout << f5(1, 2) << std::endl;

	std::function<double(Plus*, double, double)> f6 = &Plus::AddDD; // 非静态要加取地址,并且包含有this指针
	Plus plus;
	std::cout << f6(&plus, 1.1, 2) << std::endl; // 传左值

	std::function<double(Plus, double, double)> f7 = &Plus::AddDD;
	std::cout << f7(Plus(), 1.1, 2) << std::endl; // 传右值

}

// 14、包装器--bind
// 调整可调用对象的参数个数或者顺序
int Sub(int a, int b)
{
	return a - b;
}

class Mul
{
public:
	int mul(int a, int b)
	{
		return a * b;
	}
};

void PrintInfo(const std::string& name, int Health, int Mana)
{
	std::cout << name << " 血量：" << Health << " 法力：" << Mana << std::endl;
}

void test7()
{
	auto f1 = Sub;
	std::cout << f1(10, 5) << std::endl;

	// 1)调整参数顺序
	auto f2 = std::bind(Sub, std::placeholders::_2, std::placeholders::_1);
	std::cout << f2(10, 5) << std::endl;
	// bind返回值是一个Binder类，其实本质也是仿函数
	std::cout << typeid(f2).name() << std::endl << std::endl;


	// 2)调整参数个数
	auto f3 = std::bind(&Mul::mul, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	std::cout << f3(Mul(), 2, 5) << std::endl;

	Mul m;
	std::cout << f3(&m, 2, 5) << std::endl;

	// 第一个参数是this指针，我们可以直接绑死，那么参数个数就变为2
	auto f4 = std::bind(&Mul::mul, Mul(), std::placeholders::_1, std::placeholders::_2);
	std::cout << f4(2, 5) << std::endl;

	std::cout << "*****************************" << std::endl;
	PrintInfo("Jiasty", 100, 50);
	PrintInfo("Jiasty", 80, 40);
	PrintInfo("Jiasty", 66, 0);
	PrintInfo("Jiasty", 90, 80);
	auto f5 = std::bind(PrintInfo, "Jiasty", std::placeholders::_1, std::placeholders::_2);
	f5(100, 66);
	f5(88, 20);

	std::cout << std::endl;

	PrintInfo("Abs", 200, 20);
	PrintInfo("Abs", 90, 10);
	auto f6 = std::bind(PrintInfo, "Abs", std::placeholders::_1, std::placeholders::_2);
	f6(188, 10);
	f6(100, 30);
}


int main()
{
	// test1();
	// test2();
	// test3();
	// test4();
	// test5();
	// test6();
	test7();

	return 0;
}