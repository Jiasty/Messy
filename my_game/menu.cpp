#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>

void DisplayMenu()
{
	
	std::cout << "Game Menu:" << std::endl;
	std::cout << "1. Guess Number" << std::endl;
	std::cout << "2. Mine Sweeping" << std::endl;
	std::cout << "0. Exit" << std::endl;
}

int main()
{
	int choice = -1;
	while (true) //循环打印菜单
	{
		std::cout << "Please choose your want" << std::endl;
		DisplayMenu();
		std::cin >> choice;

		if (choice == 0) break; //设置出口
		else if (choice == 1)
		{

		}
	}
	return 0;
}