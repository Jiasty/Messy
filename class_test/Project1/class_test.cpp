#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>


//3����ֵ���������
class MyMath
{
public:

	MyMath(int x = 0, int y = 0, int z = 0)
		:_x(x), _y(y), _z(z)
	{}

	//��һ���Ѿ����ڵĶ�����������һ���Ѵ��ڵĶ��󣬲�ϣ��m���޸ģ�����Ҫ��const
	MyMath& operator=(const MyMath& m)
	{
		//�ж�Ϊ��ͬ����Ÿ�ֵ
		if (this != &m)
		{
			_x = m._x;
			_y = m._y;
			_z = m._z;
		}

		return *this;
	}

	//����++����
	MyMath operator++(int)
	{
		MyMath temp(*this);
		++_x;
		++_y;
		++_z;

		return temp;
	}
	//ǰ��++����
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