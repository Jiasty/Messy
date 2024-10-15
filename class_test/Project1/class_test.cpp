#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>


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


//3、赋值运算符重载
//class MyMath
//{
//public:
//
//	MyMath(int x = 0, int y = 0, int z = 0)
//		:_x(x), _y(y), _z(z)
//	{}
//
//	//以一个已经存在的对象来覆盖另一个已存在的对象，不希望m被修改，所以要加const
//	MyMath& operator=(const MyMath& m)
//	{
//		//判断为不同对象才赋值
//		if (this != &m)
//		{
//			_x = m._x;
//			_y = m._y;
//			_z = m._z;
//		}
//
//		return *this;
//	}
//
//	//后置++重载
//	MyMath operator++(int)
//	{
//		MyMath temp(*this);
//		++_x;
//		++_y;
//		++_z;
//
//		return temp;
//	}
//	//前置++重载
//	MyMath& operator++()
//	{
//		_x++;
//		_y++;
//		_z++;
//		return *this;
//	}
//
//
//private:
//	int _x;
//	int _y;
//	int _z;
//};
//
//int main()
//{
//	MyMath m1, m2;
//	m1++;
//
//	m2 = m1;
//
//	return 0;
//}


//重载为类成员函数
//class Date
//{
//public:
//    Date(int year = 1900, int month = 1, int day = 1)
//    {
//        _year = year;
//        _month = month;
//        _day = day;
//    }
//    // bool operator==(Date* this, const Date& d2) 
//    // 这里需要注意的是，左操作数是this，指向调用该函数的对象 
//    bool operator==(const Date& d2)
//    {
//        return _year == d2._year
//            && _month == d2._month
//            && _day == d2._day;
//    }
//private:
//    int _year;
//    int _month;
//    int _day;
//};
//
//int main()
//{
//    Date dd1(2022, 1, 1), dd2(2023, 7, 1);
//    std::cout << (dd1 == dd2) << std::endl;
//    return 0;
//}

//重载为全局函数
//class Date
//{
//public:
//    Date(int x = 2024, int y = 1, int z = 1)
//        :_year(x)
//        , _month(y)
//        , _day(z)
//    {}
//
//    int _year;
//    int _month;
//    int _day;
//};
//
//bool operator==(const Date& d1, const Date& d2)
//{
//    return d1._year == d2._year
//        && d1._month == d2._month
//        && d1._day == d2._day;
//}
//
//int main()
//{
//    Date dd1, dd2;
//    std::cout << (dd1 == dd2) << std::endl; //运算符重载在此处使用时需要加括号，<<优先级高
//    return 0;
//}



//4、const成员函数
//class Date
//{
//public:
//	Date(int year = 1900, int month = 1, int day = 1)
//	{
//	    _year = year;
//	    _month = month;
//	    _day = day;
//	}
//	
//	void Other1()
//	{
//		std::cout << "Other1()" << std::endl;
//	}
//	void Other2() const
//	{
//		std::cout << "Other2() const" << std::endl;
//	}
//
//	void Test2()
//	{
//		std::cout << "Test2() const" << std::endl;
//		Other1();
//		Other2();
//	}
//	void Test1() const
//	{
//		std::cout << "Test1() const" << std::endl;
//		//Other1(); const函数无法调用非const函数
//		Other2();
//	}
//	/*void Change() const
//	{
//		_year++; //此时_year不允许被修改
//	}*/
//
//
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//int main()
//{
//	const Date d1(2024, 1, 1);
//	Date d2(2022, 12, 31);
//
//	//d1.Other1(); //const对象无法调用非const函数
//	d1.Other2();
//	d2.Other1();
//	d2.Other2();
//	return 0;
//}


//初始化列表:类对象真正初始化的地方
//class Aa
//{
//public:
//    Aa()
//    {
//        //函数体赋值并非初始化，初始化只能执行一次
//        _id = 0;
//        _id = 1;
//    }
//private:
//    int _id;
//};
//
//class A
//{
//public:
//    A(int a)
//        :_a1(a)
//        , _a2(_a1) //先声明，先初始化，_a1为随机值
//    {}
//    void Print()
//    {
//        std::cout << _a1 << " " << _a2 << std::endl;
//    }
//private:
//    //初始化列表初始顺序按声明顺序
//    int _a2;
//    int _a1;
//};
//int main()
//{
//    A aa(1);
//    aa.Print();  // 1 和 随机值
//}


//隐式类型转换与explicit关键字
//class Date
//{
//public:
//    // 1. 单参构造函数，没有使用explicit修饰，具有类型转换作用
//    // explicit修饰构造函数，禁止类型转换---explicit去掉之后，代码可以通过编译
//    explicit Date(int year)
//        :_year(year)
//    {}
//    // 2. 虽然有多个参数，但是创建对象时后两个参数可以不传递，没有使用explicit修饰，具有类型转换作用
//    // explicit修饰构造函数，禁止类型转换
//    explicit Date(int year, int month = 1, int day = 1)
//        : _year(year)
//        , _month(month)
//        , _day(day)
//    {}
//    Date& operator=(const Date& d)
//    {
//        if (this != &d)
//        {
//            _year = d._year;
//            _month = d._month;
//            _day = d._day;
//        }
//        return *this;
//    }
//private:
//    int _year;
//    int _month;
//    int _day;
//};
//void Test()
//{
//    Date d1(2022);
//
//    // 用一个整形变量给日期类型对象赋值
//    // 实际编译器背后会用2023构造一个无名对象，最后用无名对象给d1对象进行赋值
//    d1 = 2023;
//    // 将1屏蔽掉，2放开时则编译失败，因为explicit修饰构造函数，禁止了单参构造函数类型转换的作用
//}


//static成员
//class Eg
//{
//public:
//	Eg(int id, int num)
//		:_id(id)
//		//,_num(num) //static成员只能在类外初始化，why?
//	{
//		_num = num;
//	}
//
//	int _id;
//	static int _num;
//};
//
//int main()
//{
//	//无法编译
//	//Eg e1(01, 5);
//	//std::cout << e1._id << e1._num << std::endl;
//
//	return 0;
//}


//inheritance继承
//class Person
//{
//public:
//	void Print()
//	{
//		std::cout << "name:" << _name << std::endl;
//		std::cout << "age:" << _age << std::endl;
//	}
//protected:
//	std::string _name = "Jiasty"; // 姓名
//	int _age = 18;  // 年龄
//};
////继承后父类的Person的成员（成员函数+成员变量）都会变成子类的一部分。
////这里体现出了Student和Teacher复用了Person的成员。
//class Student : public Person
//{
//protected:
//	int _stuid; // 学号
//};
//
//class Teacher : public Person
//{
//protected:
//	int _jobid; // 工号
//};
//int main()
//{
//	Student s;
//	Teacher t;
//	s.Print();
//
//	t.Print();
//	return 0;
//}


//切片
//class Person
//{
//protected:
//	std::string _name;
//	std::string _sex;
//	int _age; // 年龄
//};
//
//class Student : public Person
//{
//public:
//	int _id; // 学号
//};
//
//int main()
//{
//	Student sobj;
//	// 1.子类对象可以赋值给父类对象/指针/引用
//	Person pobj = sobj;
//	Person* pp = &sobj;
//	Person& rp = sobj;
//
//	//2.基类对象不能赋值给派生类对象
//	//sobj = pobj;
//
//	//3.基类的指针可以通过强制类型转换赋值给派生类的指针
//	pp = &sobj;
//	Student* ps1 = (Student*)pp; // 这种情况转换时可以的。
//	ps1->_id = 10;
//
//	//pp = &pobj;
//	//Student* ps2 = (Student*)pp; // 这种情况转换时虽然可以，但是会存在越界访问的问题
//	//ps2->_id = 10;
//
//	return 0;
//}

