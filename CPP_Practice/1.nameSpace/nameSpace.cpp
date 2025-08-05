#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using std::cout;  // 打开部分访问权限
using std::endl;

namespace Jiasty
{
	int a = 1;

	int add(int a, int b)
	{
		return a + b;
	}

	struct student
	{
		int age;
		char* name;
	};

	// 命名空间嵌套
	namespace sub
	{
		int b = 0;
	}
}

// 同名命名空间域，将合并。
namespace Jiasty
{
	int x = 111;
}

int main()
{
	std::cout << Jiasty::a << std::endl << Jiasty::sub::b << std::endl;
	cout << Jiasty::x << endl;
	struct Jiasty::student A; // 命名空间域中结构体的对象定义
	// Jiasty::struct student A; 错误写法

	return 0;
}


//int x = 1;
//
//int main()
//{
//	int x = 0;
//	printf("%d\n", x);
//	printf("%d\n", ::x);
//
//	return 0;
//}