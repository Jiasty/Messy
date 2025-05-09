#pragma once
#include <stdio.h>

#define ROW 9
#define COL 9
#define ROWS ROW + 2
#define COLS COL + 2

#define EASY 10
#define MEDI 20
#define HARD 30


void Menu(); // ´òÓ¡²Ëµ¥
void Game(); // É¨À×ÓÎÏ·

void InitBoard(char board[ROWS][COLS], int rows, int cols, char set);

void Display(char board[ROWS][COLS], int rows, int cols);

void Setmine(char mine[ROWS][COLS], int rows, int cols);

void Findmine(char mine[ROWS][COLS], char show[ROWS][COLS], int rows, int cols);

int GetMineCount(char mine[ROWS][COLS], int row, int col);