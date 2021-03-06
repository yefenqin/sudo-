// soduku.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm> 
#include<fstream>

using namespace std;
int a[9][9], row[9][10], col[9][10], g[10][10];
void creat(int n)
{
	ofstream output;
	output.open("../BIN/sudoku.txt");
	int shift[9] = { 0, 3, 6, 1, 4, 7, 5, 8, 2 };
	while (n != 0)
	{
		for (int i = 0; i < 6; i++)
		{
			if (n == 0) continue;
			if (i)
			{
				next_permutation(shift + 3, shift + 6); shift[6] = 5, shift[7] = 8, shift[8] = 2;//调换第4-6列位置 
			}
			for (int j = 0; j < 6; j++)
			{
				if (n == 0) continue;
				if (j) next_permutation(shift + 6, shift + 9);//调换第7-9列位置 
				char row[10] = "912345678";
				for (int k = 0; k < 40320; k++)
				{
					if (n == 0) continue;
					if (k) next_permutation(row + 1, row + 9);//调换第2-9行位置 
					for (int r = 0; r < 9; r++)
					{
						for (int c = 0; c < 9; c++) output << row[(c + shift[r]) % 9] << ' ';
						output << endl;
					}
					output << endl;
					n--;
				}
			}
		}
	}
	output.close();
}
int flag = 0;
void fun(int x, int y)
{
	ofstream output;
	output.open("../BIN/sudoku.txt", ios::app);
	if (flag) return;
	if (x == 9 && y == 0) {
		for (int i = 0; i<9; i++) {
			for (int j = 0; j<9; j++) {
				output << a[i][j] << " ";//输出解 
			}
			output << endl;
		}
		flag = 1;//输出完成 
	}
	if (a[x][y] != 0) {
		if (y == 8) {
			fun(x + 1, 0);
		}
		else
			fun(x, y + 1);
	}
	else
		for (int i = 1; i <= 9; i++) {
			if (row[x][i] == 1 || col[y][i] == 1 || g[(x) / 3 * 3 + (y) / 3][i] == 1)
				continue;
			a[x][y] = i;
			row[x][i] = 1;
			col[y][i] = 1;
			g[(x) / 3 * 3 + (y) / 3][i] = 1;
			if (y == 8)
				fun(x + 1, 0);//一行找完开始找下一行 
			else
				fun(x, y + 1);
			row[x][i] = 0;
			col[y][i] = 0;
			g[(x) / 3 * 3 + (y) / 3][i] = 0;
			a[x][y] = 0;
		}
}

void solve(char path[])
{
	ifstream input;
	input.open(path);
	ofstream output;
	output.open("../BIN/sudoku.txt");
	output.close();
	while (!input.eof())
	{
		flag = 0;
		for (int i = 0; i<9; i++) {
			for (int j = 0; j<9; j++) {
				input >> a[i][j];
				if (a[i][j] != 0) {
					row[i][a[i][j]] = 1;//每行已经有了的数字
					col[j][a[i][j]] = 1;//每列已经有了的数字 
					g[(i) / 3 * 3 + (j) / 3][a[i][j]] = 1;//每块已经有了的数字
				}//将已有的数字先标记 
			}
		}
		fun(0, 0);
	}
	input.close();
}

int main(int argc, char* argv[])
{
	int n;
	char c[5], path[200];
	if (argc>2)
	{
		strcpy_s(c, argv[1]);
		if (c[1] == 'c')
		{//检测命令行参数-c
			n = atoi(argv[2]);//生成终局数
			if (n)
			{
				creat(n);
			}
			else
				cout << "wrong" << endl;
		}
		else if (c[1] == 's')
		{//检测命令行参数-s
			strcpy_s(path, argv[2]);
			solve(path);
		}
		else
			cout << "wrong" << endl;
	}
	else
		cout << "wrong" << endl;
}


