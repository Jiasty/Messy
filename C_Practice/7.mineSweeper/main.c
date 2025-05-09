#define _CRT_SECURE_NO_WARNINGS 1
#include "Game.h"

int main()
{
	int input = -1;

	do
	{
		Menu();
		printf("Choose >");
		(void)scanf("%d", &input);

		switch (input)
		{
		case 0:
			printf("Quit the game.\n");
			break;
		case 1:
			Game();
			break;
		case 2:
			break;
		default:
			printf("Enter error! More.\n");
			break;
		}
	} while (input);

	return 0;
}