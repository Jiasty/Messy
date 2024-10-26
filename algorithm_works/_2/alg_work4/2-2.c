#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 500

char elements[MAX_N];   // 存储输入的元素
int used[MAX_N];        // 记录元素是否被使用
int count = 0;          // 记录总排列数
char result[MAX_N];     // 存储当前排列

int compare(const void* a, const void* b) 
{
    return *(char*)a - *(char*)b;
}

// 递归生成不同的排列
void backtrack(int n, int depth, FILE* outputFile) 
{
    if (depth == n) 
    {
        fprintf(outputFile, "%s\n", result);
        count++;
        return;
    }

    for (int i = 0; i < n; i++) 
    {
        if (used[i]) continue;
        if (i > 0 && elements[i] == elements[i - 1] && !used[i - 1]) continue;

        used[i] = 1;  // 标记为使用
        result[depth] = elements[i];  // 记录当前元素
        backtrack(n, depth + 1, outputFile);
        used[i] = 0;
    }
}

int main() 
{
    FILE* inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) 
    {
        perror("无法打开输入文件");
        exit(EXIT_FAILURE);
    }

    int n;
    fscanf(inputFile, "%d", &n);
    fscanf(inputFile, "%s", elements);
    fclose(inputFile);

    qsort(elements, n, sizeof(char), compare);

    FILE* outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) 
    {
        perror("无法打开输出文件");
        exit(EXIT_FAILURE);
    }

    backtrack(n, 0, outputFile);

    fprintf(outputFile, "%d\n", count);
    fclose(outputFile);

    return 0;
}