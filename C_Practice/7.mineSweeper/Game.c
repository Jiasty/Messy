#define _CRT_SECURE_NO_WARNINGS 1
#include "Game.h"

void InitBoard(char board[ROWS][COLS], int rows, int cols, char set)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			board[i][j] = set;
		}
	}
}

void Display(char board[ROWS][COLS], int rows, int cols)
{
	printf("--------------------\n");
	printf(" ");
	for (int j = 1; j <= cols; j++)
	{
		printf(" %d", j);
	}
	printf("\n");
	for (int i = 1; i <= rows; i++)
	{
		printf("%d ", i);
		for (int j = 1; j <= cols; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
	printf("--------------------\n");
}

void Setmine(char mine[ROWS][COLS], int rows, int cols)
{
	int count = EASY;
	while (count--)
	{
		int x = rand() % rows + 1; // 1~9
		int y = rand() % cols + 1;
		if (mine[x][y] == '0')
			mine[x][y] = '1';
	}
}

static int GetMineCount(char mine[ROWS][COLS], int row, int col)
{
	int ret = 0;
	for (int i = row - 1; i <= row + 1; i++)
	{
		for (int j = col - 1; j <= col + 1; j++)
		{
			if (i != row && j != col && mine[i][j] == '1') ret++;
		}
	}
	return ret;
}

void Findmine(char mine[ROWS][COLS], char show[ROWS][COLS], int rows, int cols)
{
	int x = 0, y = 0, win = 0;
	while (win < rows * cols - EASY)
	{
		printf("输入要排查的坐标>");
		scanf("%d %d", &x, &y);
		if (x >= 1 && x <= rows || y >= 1 && y <= cols)
		{
			if (mine[x][y] == '1')
			{
				printf("炸死了\n");
				Display(mine, ROW, COL);
				break;
			}
			else
			{
				int count = GetMineCount(mine, x, y);
				show[x][y] = count + '0';
				// 根据一定算法展开周围没雷的情况。TODO
				// 标记雷。TODO
				Display(show, ROW, COL);
				win++;
			}
		}
		else
		{
			printf("输入错误");
		}
	}

	if (win == rows * cols - EASY)
	{
		printf("游戏胜利!\n");
		Display(mine, ROW, COL);
	}
}

void Menu()
{
	printf("1.扫雷游戏\n");
	printf("2.猜数游戏\n");
	printf("0.退出游玩\n");
}
void Game()
{
	// 1.创建数组并初始化
	char mine[ROWS][COLS]; //'0'
	char show[ROWS][COLS]; //'*'
	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');

	// 2.打印棋盘
	Display(show, ROW, COL);
	//Display(mine, ROW, COL);
	
	// 3.设置雷
	Setmine(mine, ROW, COL);
	Display(mine, ROW, COL);

	// 4.排查雷
	Findmine(mine, show, ROW, COL);
}