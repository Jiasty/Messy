#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

class A
{
public:
	A(const A& a)
	{}

private:
	int _id;
};

int main()
{
	std::cout << 1;
	//ֻ�п�������ʱ
	//A a1(); //�����ͨ��

	//A a2; //�޷�����

	return 0;
}



//�����С����ָ����������
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