#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<unordered_map>
#include<unordered_set>

using namespace std;

void test_set1()
{
	unordered_set<int> s = { 10, 7, 0, 1, 5, 2 };

	unordered_set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

void test_map1()
{
	unordered_map<int, char> m = { {1, 'c'}, {10, 'm'}, {0, 's'} };
	unordered_map<int, char>::iterator it = m.begin();
	while (it != m.end())
	{
		cout << it->first << "->" << it->second << " ";
		++it;
	}
	cout << endl;
}

int main()
{
	test_set1();
	test_map1();
	return 0;
}