#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

class Date
{};

class A
{
public:
	void func()
	{
		return;
	}
};

int main()
{
	std::cout << 1;
	std::cout << sizeof(Date) << std::endl;

	A* p = nullptr;
	//p->func(); //�������У�func()�ڹ�������û���������棬����ʱ���Ѿ�ȷ�ϵ�ַ��
	//vs�޷����гɹ�Ҳ����MSVC���������̫�ϸ�
	return 0;
}