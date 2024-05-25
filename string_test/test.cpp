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
	for (size_t i = 0; i < s1.size(); i++)
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
		cout << *it++ << " "; //此处*也进行了操作符重载
	}
	cout << endl;

	//3.范围for（本质基于迭代器）
	for (const auto& e : s2)
	{
		cout << e << " ";
	}
	cout << endl;
}

void test3()
{
	//反向迭代器（不常用）
	string s1("hello world");
	string::reverse_iterator rit = s1.rbegin();
	while (rit != s1.rend())
	{
		cout << *rit++ << " ";//一定记得是++，且别忘了++
	}
	cout << endl;

	//const_迭代器(迭代器指向的类容不可修改，const iterator是指迭代器无法更改指向)
	const string s2("hello world");
	string::const_iterator cit = s2.begin();//C++新增了cbegin和cend其实没大区别
	while (cit != s2.end())
	{
		cout << *cit++ << " ";
		//(*cit)++;只读不可写
	}
	cout << endl;

	//还有const_reverse_iterator
}

void test4()
{
	//capacity相关

	string s1("hello world");
	cout << s1.size() << endl;
	cout << s1.length() << endl;
	//size和length其实功能一样都不记 \0，size为后加，为了和其他容器统一

	//最大长度（不同机器不同）
	cout << s1.max_size() << endl;

	//可存容量（不同平台扩容机制不同，linux下基本为2倍扩容）
	cout << s1.capacity() << endl;
	//windows平台下的扩容规律
	string s;
	s.reserve(50);//reserve请求一段空间，直接申请一段需要的空间来避免扩容耗费(常用！！！！！)
	//reserve(50)也不一定开50，可能更多（合理范围类）
	//如果reserve的空间比当前空间小就不动，是不会缩容的
	int sz = s.capacity();
	cout << sz << endl;
	for (int i = 0; i < 100; i++)
	{
		s.push_back('c');
		if (sz != s.capacity())
		{
			sz = s.capacity();
			cout << "capacity changed：" << sz << endl;
		}
	}

	cout << "---------" << endl;
	//clear清除数据，但不一定清空间（）
	cout << s1 << endl;
	cout << s1.capacity() << endl;
	s1.clear();
	cout << s1 << endl;
	cout << s1.capacity() << endl;

	cout << "---------------" << endl;
	//缩容
	string s2;
	for (int i = 0; i < 50; i++)
	{
		s2.push_back('a');
	}
	cout << s2.capacity() << endl;
	s2.clear();
	s2.shrink_to_fit(); //默认最小缩容到15
	cout << s2.capacity() << endl;

	cout << "---------------" << endl;
	//resize改变size
	//[0, size, ..., capacity]
	//比size小，删除多的部分
	//比size大，比capacity小，增加空字符
	//比capacity大扩容且加空字符
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
	//string访问
	
	string s1("hello world");
	//[] 和 at
	//功能没区别，区别在于[]对于越界检查为断言，而at是抛异常
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
	//front and back返回string的首或尾字符(C++11)
	string s2("apple");
	cout << s2.front() << " " << s2.back() << endl;

}

void test6()
{
	//Modifiers修改
	string s1("hello world");
	s1.push_back('a'); //push_back只能插入字符
	cout << s1 << endl;

	s1.append("pennnn"); //插入字符串，append函数还有很多重载版本
	cout << s1 << endl;

	// += 则可以插入字符和字符串（常用！！！）
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

	s1.assign("xxxxxxx"); //直接覆盖
	cout << s1 << endl;

	//insert（效率低）
	s2.insert(1, "xxx"); //在下标1之前插入
	cout << s2 << endl;

	//erase（效率低）
	s2.erase(1, 3); //从 下标位置 删除 几个
	cout << s2 << endl;
	s2.erase(2); // 从2位置开始删完
	cout << s2 << endl;
	cout << s2.capacity() << endl;
	
	//replace(还有很多重载版本，效率低，不常用)
	string s3("jks niko simple");
	s3.replace(5, 2, "aaa"); //从下标5开始将后两个字符替换成"aaa"，会挪动数据，效率也低
	cout << s3 << endl;

	cout << "-------------" << endl;
	string s4("qwerty");
	string s5("asdfghjklasdfghjkasd");
	cout << s4.capacity() << endl;
	cout << s5.capacity() << endl;

	s4.swap(s5); //非算法库里的swap
	cout << s4.capacity() << endl;
	cout << s5.capacity() << endl;

}

void test8()
{
	//String operations
	string s("abcde");
	const char* c = s.c_str();
	cout << c[2] << endl;

	//copy：拷贝某一部分到字符数组
	char buffer[20];
	string str("Test string...");
	size_t length = str.copy(buffer, 6, 5);//从下标5开始拷贝6个
	buffer[length] = '\0';
	cout << "buffer contains: " << buffer << '\n';
}

void test9()
{
	string s1("file.cpp");
	//取文件后缀
	size_t pos1 = s1.find('.');//If no matches were found, returns string::npos.
	if (pos1 != string::npos)
	{
		string temp1 = s1.substr(pos1);
		//string temp1 = s.substr(pos, s.size() - pos);
		cout << temp1 << endl;
	}

	//rfind：从后往前找
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
	cout << i3 << endl; //找到就返回字串首字母的下标

	//同c的strtok
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