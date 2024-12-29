#include<iostream>
#include<map>

using namespace std;

void map_test1()
{
	map<string, string> dict;
	//��������
	pair<string, string> kv1("sort", "����");
	dict.insert(kv1);
	//��������
	dict.insert(pair<string, string>("left", "���"));
	//����ģ�壬���ù���
	dict.insert(make_pair("right", "�ұ�"));
	//��ʽ����ת��
	dict.insert({ "right", "�ұ�" });
	dict.insert({ "Jiasty", "��˹��" });


	//map�� initializer_list �ڹ��캯��
	map<string, string> dict2 = { kv1, {"sort", "����"}, {"left", "���"}, {"right", "�ұ�"} };

	//ɾ��
	//ɾ���ᵼ�µ�����ʧЧ
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
	string arr[] = { "ƻ��", "�㽶", "����", "����","�㽶", "����", "����", "ƻ��", "�㽶", "����", "����" };

	map<string, int> countMap;
	for (auto& e : arr)
	{
		//������ʱ��key,���ض�Ӧvalue
		//return (*((this->insert(make_pair(k,mapped_type()))).first)).second ������������
		countMap[e]++;  //������޸ģ�ĳkey���ں�����޸ģ�

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
	dict.insert({ "string", "�ַ���" });

	//����
	dict["right"];
	//������޸�
	dict["left"] = "���";
	//����
	cout << dict["left"];
	//�޸�
	dict["right"] = "�ұ�";

	//ע����vector�ɲ�ͬ��vector�������±꣬�˴�������key

	//count��ʹ�ã�����key�ڲ���
	string str;
	while (cin >> str)
	{
		if (dict.count(str))
		{
			cout << "��" << endl;
		}
		else
		{
			cout << "����" << endl;
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