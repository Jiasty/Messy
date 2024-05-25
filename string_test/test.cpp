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
	for (size_t i = 0; i < s1.size(); i++)
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
		cout << *it++ << " "; //�˴�*Ҳ�����˲���������
	}
	cout << endl;

	//3.��Χfor�����ʻ��ڵ�������
	for (const auto& e : s2)
	{
		cout << e << " ";
	}
	cout << endl;
}

void test3()
{
	//����������������ã�
	string s1("hello world");
	string::reverse_iterator rit = s1.rbegin();
	while (rit != s1.rend())
	{
		cout << *rit++ << " ";//һ���ǵ���++���ұ�����++
	}
	cout << endl;

	//const_������(������ָ������ݲ����޸ģ�const iterator��ָ�������޷�����ָ��)
	const string s2("hello world");
	string::const_iterator cit = s2.begin();//C++������cbegin��cend��ʵû������
	while (cit != s2.end())
	{
		cout << *cit++ << " ";
		//(*cit)++;ֻ������д
	}
	cout << endl;

	//����const_reverse_iterator
}

void test4()
{
	//capacity���

	string s1("hello world");
	cout << s1.size() << endl;
	cout << s1.length() << endl;
	//size��length��ʵ����һ�������� \0��sizeΪ��ӣ�Ϊ�˺���������ͳһ

	//��󳤶ȣ���ͬ������ͬ��
	cout << s1.max_size() << endl;

	//�ɴ���������ͬƽ̨���ݻ��Ʋ�ͬ��linux�»���Ϊ2�����ݣ�
	cout << s1.capacity() << endl;
	//windowsƽ̨�µ����ݹ���
	string s;
	s.reserve(50);//reserve����һ�οռ䣬ֱ������һ����Ҫ�Ŀռ����������ݺķ�(���ã���������)
	//reserve(50)Ҳ��һ����50�����ܸ��ࣨ����Χ�ࣩ
	//���reserve�Ŀռ�ȵ�ǰ�ռ�С�Ͳ������ǲ������ݵ�
	int sz = s.capacity();
	cout << sz << endl;
	for (int i = 0; i < 100; i++)
	{
		s.push_back('c');
		if (sz != s.capacity())
		{
			sz = s.capacity();
			cout << "capacity changed��" << sz << endl;
		}
	}

	cout << "---------" << endl;
	//clear������ݣ�����һ����ռ䣨��
	cout << s1 << endl;
	cout << s1.capacity() << endl;
	s1.clear();
	cout << s1 << endl;
	cout << s1.capacity() << endl;

	cout << "---------------" << endl;
	//����
	string s2;
	for (int i = 0; i < 50; i++)
	{
		s2.push_back('a');
	}
	cout << s2.capacity() << endl;
	s2.clear();
	s2.shrink_to_fit(); //Ĭ����С���ݵ�15
	cout << s2.capacity() << endl;

	cout << "---------------" << endl;
	//resize�ı�size
	//[0, size, ..., capacity]
	//��sizeС��ɾ����Ĳ���
	//��size�󣬱�capacityС�����ӿ��ַ�
	//��capacity�������Ҽӿ��ַ�
	string s3("aksfwijasofjopqjfo");
	cout << s3.capacity() << endl;
	s3.resize(50);
	cout << s3.capacity() << endl;
	for (auto& e : s3)
	{
		cout << e << endl;
	}
}

void test5()
{
	//string����
	
	string s1("hello world");
	//[] �� at
	//����û������������[]����Խ����Ϊ���ԣ���at�����쳣
	cout << s1[6] << endl;
	cout << s1.at(6) << endl;

	try
	{
		s1.at(20);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
	cout << endl;
	//front and back����string���׻�β�ַ�(C++11)
	string s2("apple");
	cout << s2.front() << " " << s2.back() << endl;

}

void test6()
{
	//Modifiers�޸�
	string s1("hello world");
	s1.push_back('a'); //push_backֻ�ܲ����ַ�
	cout << s1 << endl;

	s1.append("pennnn"); //�����ַ�����append�������кܶ����ذ汾
	cout << s1 << endl;

	// += ����Բ����ַ����ַ��������ã�������
	s1 += "cccc";
	s1 += 'x';
	cout << s1 << endl;

	
}

void test7()
{
	//assign
	string s1("hello world");
	string s2 = s1;
	cout << s1 << endl;

	s1.assign("xxxxxxx"); //ֱ�Ӹ���
	cout << s1 << endl;

	//insert��Ч�ʵͣ�
	s2.insert(1, "xxx"); //���±�1֮ǰ����
	cout << s2 << endl;

	//erase��Ч�ʵͣ�
	s2.erase(1, 3); //�� �±�λ�� ɾ�� ����
	cout << s2 << endl;
	s2.erase(2); // ��2λ�ÿ�ʼɾ��
	cout << s2 << endl;
	cout << s2.capacity() << endl;
	
	//replace(���кܶ����ذ汾��Ч�ʵͣ�������)
	string s3("jks niko simple");
	s3.replace(5, 2, "aaa"); //���±�5��ʼ���������ַ��滻��"aaa"����Ų�����ݣ�Ч��Ҳ��
	cout << s3 << endl;

	cout << "-------------" << endl;
	string s4("qwerty");
	string s5("asdfghjklasdfghjkasd");
	cout << s4.capacity() << endl;
	cout << s5.capacity() << endl;

	s4.swap(s5); //���㷨�����swap
	cout << s4.capacity() << endl;
	cout << s5.capacity() << endl;

}

void test8()
{
	//String operations
	string s("abcde");
	const char* c = s.c_str();
	cout << c[2] << endl;

	//copy������ĳһ���ֵ��ַ�����
	char buffer[20];
	string str("Test string...");
	size_t length = str.copy(buffer, 6, 5);//���±�5��ʼ����6��
	buffer[length] = '\0';
	cout << "buffer contains: " << buffer << '\n';
}

void test9()
{
	string s1("file.cpp");
	//ȡ�ļ���׺
	size_t pos1 = s1.find('.');//If no matches were found, returns string::npos.
	if (pos1 != string::npos)
	{
		string temp1 = s1.substr(pos1);
		//string temp1 = s.substr(pos, s.size() - pos);
		cout << temp1 << endl;
	}

	//rfind���Ӻ���ǰ��
	string s2("app.ac.tar");
	size_t pos2 = s2.rfind('.');
	if (pos2 != string::npos)
	{
		string temp2 = s2.substr(pos2);
		cout << temp2 << endl;
	}

	//string site("https://legacy.cplusplus.com/reference/string/string/?kw=string");
	string site("https://mp.weixin.qq.com/mp/appmsgalbum?action=getalbum&__biz=Mzg5MTY5NDUwMQ==&scene=1&album_id=3415392654954266631&count=3#wechat_redirect");
	string protocol, domain, uri;
	size_t i1 = site.find(':');
	if (i1 != string::npos)
	{
		protocol = site.substr(0, i1 - 0);
		cout << protocol << endl;
	}
	size_t i2 = site.find('/', i1 + 3);
	if (i2 != string::npos)
	{
		domain = site.substr(i1 + 3, i2 - (i1 + 3));
		cout << domain << endl;
		uri = site.substr(i2 + 1);
		cout << uri << endl;
	}

	//strstr
	size_t i3 = site.find("weixin");
	cout << i3 << endl; //�ҵ��ͷ����ִ�����ĸ���±�

	//ͬc��strtok
	//find_first_of(find_first_not_of)
	//find_last_of(find_last_not_of)

	//compare
}

void test10()
{
	string str;
	//cin >> str;
	getline(cin, str);

	size_t pos = str.rfind(' ');
	cout << str.size() - (pos + 1) << endl;
}


int main()
{
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();
	//test7();
	//test8();
	//test9();
	test10();
	return 0;
}