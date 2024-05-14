#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>

using namespace std;

void test1()
{
	//����ʹ��
	string s1;  //�޲ι���
	string s2("hello world");  //�ַ���������������
	string s3(s2);  //��������
	string s4(s2, 4, 10);  //�ֲ�����
	string s5(s2, 4);
	const char* p = "xxxx";
	string s6(p);  //c-string����
	string s7(10, 'm');  //��n��char����
	string s8 = s2;  //��ֵ

	cout << s1 << endl;
	cout << s2 << endl;
	cout << s3 << endl;
	cout << s4 << endl;
	cout << s5 << endl;
	cout << s6 << endl;
	cout << s7 << endl;
	cout << s8 << endl;
}

void test2()
{
	//string����
	string s1("hello world");  //�ַ���������������

	//1.�±�ӷ�����
	for (int i = 0; i < s1.size(); i++)
	{
		cout << s1[i] << " ";
		s1[i]++;  //�����޸�
		//ʵ�����ǵ��ú��� s1.operator[](i) ����Ϊi
	}
	cout << endl;

	const string s2("hello world");
	//s2[0]++; const�����޷��޸�
	//����operator[]������һ��const�汾��ֻ�ṩ��

	//2.������(��Ϊ��ָ��һ���� ��)(������Ҳ��const�汾)
	string s3("hello world");
	string::iterator it = s3.begin();
	while (it != s3.end()) //end()Ϊ \0 ��λ��
	{
		cout << *it++ << " ";
	}
	cout << endl;

	//3.��Χfor�����ʻ��ڵ�������
	for (const auto& e : s2)
	{
		cout << e << " ";
	}
	cout << endl;
}

int main()
{
	//test1();

	test2();

	return 0;
}