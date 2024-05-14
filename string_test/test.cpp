#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>

using namespace std;

void test1()
{
	//构造使用
	string s1;  //无参构造
	string s2("hello world");  //字符串做参数做构造
	string s3(s2);  //拷贝构造
	string s4(s2, 4, 10);  //局部构造
	string s5(s2, 4);
	const char* p = "xxxx";
	string s6(p);  //c-string构造
	string s7(10, 'm');  //用n个char构造
	string s8 = s2;  //赋值

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
	//string遍历
	string s1("hello world");  //字符串做参数做构造

	//1.下标加方括号
	for (int i = 0; i < s1.size(); i++)
	{
		cout << s1[i] << " ";
		s1[i]++;  //还能修改
		//实际上是调用函数 s1.operator[](i) 参数为i
	}
	cout << endl;

	const string s2("hello world");
	//s2[0]++; const对象无法修改
	//所以operator[]会重载一个const版本，只提供读

	//2.迭代器(行为像指针一样的 类)(迭代器也有const版本)
	string s3("hello world");
	string::iterator it = s3.begin();
	while (it != s3.end()) //end()为 \0 的位置
	{
		cout << *it++ << " ";
	}
	cout << endl;

	//3.范围for（本质基于迭代器）
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