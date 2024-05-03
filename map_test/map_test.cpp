#include<iostream>
#include<map>

using namespace std;

void map_test1()
{
	map<string, string> dict;
	//有名对象
	pair<string, string> kv1("sort", "排序");
	dict.insert(kv1);
	//匿名对象
	dict.insert(pair<string, string>("left", "左边"));
	//函数模板，调用构造
	dict.insert(make_pair("right", "右边"));
	//隐式类型转换
	dict.insert({ "right", "右边" });
	dict.insert({ "Jiasty", "贾斯提" });


	//map的 initializer_list 在构造函数
	map<string, string> dict2 = { kv1, {"sort", "排序"}, {"left", "左边"}, {"right", "右边"} };

	//删除
	//删除会导致迭代器失效
	dict.erase("right");

	auto it = dict.begin();
	while (it != dict.end())
	{
		cout << it->first << ":" << it->second << endl;
		++it;
	}
}

void map_test2()
{
	string arr[] = { "苹果", "香蕉", "西瓜", "栗子","香蕉", "西瓜", "栗子", "苹果", "香蕉", "西瓜", "栗子" };

	map<string, int> countMap;
	for (auto& e : arr)
	{
		//参数此时是key,返回对应value
		//return (*((this->insert(make_pair(k,mapped_type()))).first)).second ！！！！！！
		countMap[e]++;  //插入加修改（某key存在后就是修改）

		/*auto it = countMap.find(e);
		if (it != countMap.end())
		{
			it->second++;
		}
		else
		{
			countMap.insert({ e,1 });
		}*/
	}
	for (auto& kv : countMap)
	{
		cout << kv.first << kv.second << endl;
	}

	//multimap
	multimap<int, string> sortMap;
	for (auto& kv : countMap)
	{
		sortMap.insert({ kv.second, kv.first });
	}
	cout << endl;
	for (auto& kv : sortMap)
	{
		cout << kv.first << kv.second << endl;
	}


}

void map_test3()
{
	map<string, string> dict;
	dict.insert({ "string", "字符串" });

	//插入
	dict["right"];
	//插入加修改
	dict["left"] = "左边";
	//查找
	cout << dict["left"];
	//修改
	dict["right"] = "右边";

	//注意与vector可不同，vector传的是下标，此处传的是key

	//count的使用，查找key在不在
	string str;
	while (cin >> str)
	{
		if (dict.count(str))
		{
			cout << "在" << endl;
		}
		else
		{
			cout << "不在" << endl;
		}
	}
}


int main()
{
	//map_test1();
	map_test2();
	//map_test3();
	return 0;
}