#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>


//1�������С����ָ����������
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
//	std::cout << "����Ĵ�СΪ" << sizeof(Date) << std::endl;
//
//	A* p = nullptr;
//	p->func(); //�������У�func()�ڹ�������û���������棬����ʱ���Ѿ�ȷ�ϵ�ַ��
//	return 0;
//}
 
 
//2������������ʾ�����󣬱�����������Ĭ�Ϲ��캯����
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
//	//ֻ�п�������ʱ
//	//A a1(); //�����ͨ��,��һ�����������������Ƕ���ʵ��������
//
//	//A a2; //�޷�����
//
//	return 0;
//}


//3����ֵ���������
//class MyMath
//{
//public:
//
//	MyMath(int x = 0, int y = 0, int z = 0)
//		:_x(x), _y(y), _z(z)
//	{}
//
//	//��һ���Ѿ����ڵĶ�����������һ���Ѵ��ڵĶ��󣬲�ϣ��m���޸ģ�����Ҫ��const
//	MyMath& operator=(const MyMath& m)
//	{
//		//�ж�Ϊ��ͬ����Ÿ�ֵ
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
//	//����++����
//	MyMath operator++(int)
//	{
//		MyMath temp(*this);
//		++_x;
//		++_y;
//		++_z;
//
//		return temp;
//	}
//	//ǰ��++����
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


//����Ϊ���Ա����
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
//    // ������Ҫע����ǣ����������this��ָ����øú����Ķ��� 
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

//����Ϊȫ�ֺ���
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
//    std::cout << (dd1 == dd2) << std::endl; //����������ڴ˴�ʹ��ʱ��Ҫ�����ţ�<<���ȼ���
//    return 0;
//}



//4��const��Ա����
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
//		//Other1(); const�����޷����÷�const����
//		Other2();
//	}
//	/*void Change() const
//	{
//		_year++; //��ʱ_year�������޸�
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
//	//d1.Other1(); //const�����޷����÷�const����
//	d1.Other2();
//	d2.Other1();
//	d2.Other2();
//	return 0;
//}


//��ʼ���б�:�����������ʼ���ĵط�
//class Aa
//{
//public:
//    Aa()
//    {
//        //�����帳ֵ���ǳ�ʼ������ʼ��ֻ��ִ��һ��
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
//        , _a2(_a1) //���������ȳ�ʼ����_a1Ϊ���ֵ
//    {}
//    void Print()
//    {
//        std::cout << _a1 << " " << _a2 << std::endl;
//    }
//private:
//    //��ʼ���б��ʼ˳������˳��
//    int _a2;
//    int _a1;
//};
//int main()
//{
//    A aa(1);
//    aa.Print();  // 1 �� ���ֵ
//}


//��ʽ����ת����explicit�ؼ���
//class Date
//{
//public:
//    // 1. ���ι��캯����û��ʹ��explicit���Σ���������ת������
//    // explicit���ι��캯������ֹ����ת��---explicitȥ��֮�󣬴������ͨ������
//    explicit Date(int year)
//        :_year(year)
//    {}
//    // 2. ��Ȼ�ж�����������Ǵ�������ʱ�������������Բ����ݣ�û��ʹ��explicit���Σ���������ת������
//    // explicit���ι��캯������ֹ����ת��
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
//    // ��һ�����α������������Ͷ���ֵ
//    // ʵ�ʱ������������2023����һ������������������������d1������и�ֵ
//    d1 = 2023;
//    // ��1���ε���2�ſ�ʱ�����ʧ�ܣ���Ϊexplicit���ι��캯������ֹ�˵��ι��캯������ת��������
//}