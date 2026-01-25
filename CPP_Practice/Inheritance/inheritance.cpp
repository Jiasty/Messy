#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>

class Person
{
public:
	void Print()
	{
		std::cout << "name:" << _name << std::endl;
		std::cout << "age:" << _age << std::endl;
	}

	void Print_a()
	{
		std::cout << a << std::endl;
	}
protected:
	void test()
	{
		std::cout << "This is a func of protected." << std::endl;
	}
protected:
	std::string _name = "peter"; // 姓名
	int _age = 18; // 年龄
private:
	int a = 10;
};
// 继承后父类的Person的成员（成员函数+成员变量）都会变成子类的一部分。
// 这里体现出了Student和Teacher复用了Person的成员。
// 下面我们使用监视窗口查看Student和Teacher对象可以看到变量的复用。调用Print可以看到成员函数的复用。
class Student : public Person
{
public:
	void f()
	{
		// std::cout << this->a; 不可直接访问基类的private变量

		// 间接使用
		// 调用基类的访问或修改private变量的公有成员函数
		Print_a();
	}
protected:
	int _stuid; // 学号
};

// class Teacher : public Person
class Teacher : protected Person
{
public:
	void func()
	{
		test();
	}
protected:
	int _jobid; // 工号
};

void test1()
{
	Student s;
	//s._name += 'x';
	//s._age = 20;
	s.f();
	Teacher t;
	//t._name += 'y';
	//t._age = 18;

	s.Print();
	// t.Print();
	// t.test(); test()和Print()都变成了protected的，只能在类内访问
	t.func(); // 间接访问test()
}

// 切割/切片
class Animal
{
public:
	int _height = 1;
	int _weight = 2;
};

class Dog : public Animal
{
public:
	Dog(int tailLength)
		:_tailLength(tailLength)
	{}
private:
	int _tailLength;
};

class Bird : public Animal
{
private:
	int _wingLength;
};

void test2()
{
	Dog d1(10);
	Animal a1 = d1;
	Animal& a2 = d1;
	Animal* a3 = &d1;

	// Dog d2 = a1;  基类对象不能赋值给派生类对象

	a2._height++;
	a3->_weight++;
}

// 继承作用域
class Person2
{
protected:
	std::string name = "Peter";
	int age = 18;
	int _num = 0;
};

class Student2 : public Person2
{
public:
	void func()
	{
		// Student2中有两个_num，就近原则访问派生类自己的
		std::cout << _num << std::endl;
		std::cout << Person2::_num << std::endl; // 显示访问基类成员
	}

protected:
	int _No; // 学号
	int _num = 1;
};


// B中的fun和A中的fun不是构成重载，因为不是在同一作用域
// B中的fun和A中的fun构成隐藏，成员函数满足函数名相同就构成隐藏。
class A
{
public:
	void fun()
	{
		std::cout << "func()" << std::endl;
	}
};
class B : public A
{
public:
	void fun(int i)
	{
		A::fun();
		std::cout << "func(int i)->" << i << std::endl;
	}
};


void test3()
{
	Student2 st;
	st.func();

	/////////////////
	// 隐藏
	B b;
	b.fun(10);
	b.A::fun(); // 外面调用基类的成员函数
}


// 派生类的默认成员函数
class Person3
{
public:
	Person3(std::string name = "Peter")
		:_name(name)
	{}

	Person3(const Person3& p)
		:_name(p._name)
		,_age(p._age)
	{
		std::cout << "Person3(const Person3& p)" << std::endl;
	}

	Person3& operator=(const Person3& p)
	{
		std::cout << "Person3 & operator=(const Person3 & p)" << std::endl;
		if (this != &p)
			_name = p._name;
		return *this;
	}

	~Person3()
	{
		std::cout << "~Person3()" << std::endl;
	}

protected:
	std::string _name;
	int _age = 18;
};

class Student3 : public Person3
{
public:
	// 基类当做一个整体，不可单独对其成员变量进行初始化
	// 派生类 = 基类 + 派生类成员
	//Student3(std::string name, int age, int NO) // 编译报错
	//	:_name(name)
	//	, _age(age)
	//	, _NO(NO)
	//{}

	Student3(std::string name, int NO) // 编译报错
		:Person3(name)
		, _NO(NO)
	{}

	Student3(const Student3& s)
		:Person3(s) // 切片，直接给s即可
		,_NO(s._NO)
	{
		std::cout << "Student3(const Student3& s)" << std::endl;
	}

	Student3& operator=(const Student3& s)
	{
		std::cout << "Student3& operator=(const Student3& s)" << std::endl;
		if (this != &s)
		{
			Person3::operator=(s); // 切片 显示调用.此处构成隐藏，一定要指定作用域
			_NO = s._NO;
		}
		return *this;
	}

	// 子类的析构也会隐藏父类
	// 由于多态的需要，析构函数的名字会被统一处理成destructor(析构函数)，就会构成隐藏
	~Student3()
	{
		// ~Person3();
		Person3::~Person3(); // 显示调用 隐藏要制定作用域

		std::cout << "~Student3()" << std::endl;
	}
protected:
	// Person3 _p; 继承后类似于有一个Person3成员，一个整体
	int _NO;

	// 父类成员当做一个整体自定义类型成员
	// 子类的成员(同以往一样)：a、内置类型 b、自定义类型
};

void test4()
{
	/*Student3 st("Jiasty", 1);
	Student3 st2(st);

	Student3 st3("XXXXX", 2);
	st = st3;*/

	Student3 st("Jiasty", 1);
}


// 继承与友元
class Student4; // Student4的定义在下面。声明防止友元声明失效
class Person4
{
public:
	friend void Display(const Person4& p, const Student4& s);
protected:
	std::string _name; // 姓名
};

class Student4 : public Person4
{
protected:
	int _stuNum; // 学号
};

void Display(const Person4& p, const Student4& s)
{
	std::cout << p._name << std::endl;
	// std::cout << s._stuNum << std::endl; // 无法访问
}

void test5()
{
	Person4 p;
	Student4 s;
	Display(p, s);
}


// 继承与静态成员
class Person5
{
public:
	Person5()
	{ 
		++_count; 
	}
protected:
	std::string _name; // 姓名
public:
	static int _count; // 统计人的个数。
};

int Person5::_count = 0; // 静态成员变量，类内声明，类外定义
class Student5 : public Person5
{
protected:
	int _stuNum; // 学号
};

class Graduate : public Student5
{
protected:
	std::string _seminarCourse; // 研究科目
};

void test6()
{
	Person5 p1;
	Student5 s1;
	Graduate g1;

	std::cout << &p1._count << " " << &s1._count << " " << &g1._count << std::endl << std::endl;

	Student5 s2;
	Student5 s3;

	// 同一个_count
	std::cout << " 人数 :" << Person5::_count << " " << Student5::_count << std::endl;
	Student5::_count = 0;
	std::cout << " 人数 :" << Person5::_count << std::endl;
}


// 复杂的菱形继承
class Person6
{
public:
	std::string _name; // 姓名
};
class Student6 : public Person6
{
protected:
	int _num; //学号
};
class Teacher6 : public Person6
{
protected:
	int _id; // 职工编号
};
class Assistant : public Student6, public Teacher6
{
protected:
	std::string _majorCourse; // 主修课程
};

void test7()
{
	Assistant a;
	// a._name = "peter"; // 有二义性无法明确知道访问的是哪一个_name
	
	// 需要显示指定访问哪个父类的成员可以解决二义性问题，但是数据冗余问题无法解决
	a.Student6::_name = "xxx";
	a.Teacher6::_name = "yyy";
	std::cout << a.Student6::_name << " " << a.Teacher6::_name << std::endl;
}

// 菱形虚拟继承
class AA
{
public:
	int _a;
};
//class BB : public AA
class BB : virtual public AA
{
public:
	int _b;
};
//class CC : public AA
class CC : virtual public AA
{
public:
	int _c;
};
class DD : public BB, public CC
{
public:
	int _d;
};
int test8()
{
	DD d;
	d.BB::_a = 1;
	d.CC::_a = 2;
	d._a = 0;
	d._b = 3;
	d._c = 4;
	d._d = 5;
	return 0;
}


// 组合
class Door
{
private:
	int _weight = 10;
};

class Car
{
private:
	std::string _colour = "黑色";
	std::string _num = "渝A88888";

	Door _door;
};




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