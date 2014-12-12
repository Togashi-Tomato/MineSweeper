//這裏是函數定義，除了gotoxy()以外都是自己設計
#include "Mine.h"
#include <iostream>		//個人風格喜好，亦可用C語言標準輸入輸出庫
#include <stdio.h>
#include <conio.h>		//非標準庫，具體用法見內
#include <windows.h>	//雜七雜八
#include <time.h>		//見名字
#include <random>		//c++11新特性
#include <string>		//c++11
#define Height 10		//地圖高度
#define Width 10		//地圖寬度
#define Num 50			//雷的數量
#define Mine 11
#define Free 12
#define LMB 5
#define RMB 6
#define Safe 16
#define Flag 14
#define Esc 8
#define Up 1
#define Down 2
#define Left 3
#define Right 4
#define Lose 8
#define Win 99
#define Me 10

int map[Height][Width];
int temp[Height][Width];

void game::gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void game::create()
{
	std::random_device rd;
	if (Type != 0)
	{
		for (int count = 0; count < Num;)
		{
			int x = rd() % Height;
			int y = rd() % Width;
			if (map[x][y] > 10 && map[x][y] != Mine)
			{
				map[x][y] = Mine;
				++count;
			}
		}
	}
	else
	{
		for (int i = 0; i < Height; i++)
		{
			for (int j = 0; j < Width; j++)
				map[i][j] = Free;
		}
		A.x = 0;
		A.y = 0;
	}
}

void game::paint()
{
	system("cls");
	if (Type != Lose && Type != Win)
	{
		for (int i = 0; i < Height; i++)
		{
			for (int j = 0; j < Width; j++)
			{
				if (map[i][j] == Mine || map[i][j] == Free)
					printf("■");
				else if (map[i][j] == Flag)
					printf("〆");
				else if (map[i][j] == Me)
					printf("□");
				else if (map[i][j] < 9)
					printf("%d ", map[i][j]);
			}
			printf("\n");
		}
	}
	else
	{
		int count = 0;
		for (int i = 0; i < Height; i++)
		{
			for (int j = 0; j < Width; j++)
			{
				if (map[i][j] == Mine)
					printf("●");
				else if (map[i][j] == Flag && map[i][j] == Mine)
				{
					printf("★");
					++count;
				}
				else if (map[i][j] == Flag)
					printf("〆");
				else if (map[i][j] == Me)
					printf("□");
				else if (map[i][j] < 9)
					printf("%d ", map[i][j]);
				else
					printf("■");
			}
			printf("\n");
		}
		printf("\nYou score is %d.\n", count + (Height * Width - Num - Count));
	}
}

void game::hidden()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = 0;
	SetConsoleCursorInfo(hOut, &cci);
}

int game::get_key()
{
	char c;;
	c = _getch();
	if (c == VK_ESCAPE)
		return Esc;
	if (c == 72)
		return Up;
	if (c == 80)
		return Down;
	if (c == 75)
		return Left;
	if (c == 77)
		return Right;
	if (c == 'z')
		return LMB;
	if (c == 'x')
		return RMB;
	else
		return 0;
}

int game::gameplay()
{
	int T;
	int *temp = new int(0);
	*temp = map[A.x][A.y];
	map[A.x][A.y] = Me;
	paint();
	map[A.x][A.y] = *temp;
	delete temp;
	T = get_key();
	switch (T)
	{
	case Up:
		if ((A.x - 1) > -1)
		{
			--A.x;
		}
		break;
	case Down:
		if ((A.x + 1) < Height)
		{
			++A.x;
		}
		break;
	case Left:
		if ((A.y - 1) > -1)
		{
			--A.y;
		}
		break;
	case Right:
		if ((A.y + 1) < Height)
		{
			++A.y;
		}
		break;
	case LMB:
		if (lmb())
		{
			if (!Count)
				return Win;
			else
				return LMB;
		}
		else
			return Lose;
	case RMB:
		if (Type == 1)
			rmb();
		return RMB;
	case Esc:
		return Esc;
	}				//按鍵判斷，包括上下左右、左右鍵等
	return 0;
}

int game::lmb()
{
	if (map[A.x][A.y] == Free && Type != 0)
	{
		display();
		--Count;
		return 1;
	}
	else if (map[A.x][A.y] == Mine)
		return 0;
	else if (Type == 0)
	{
		--Count;
		map[A.x][A.y] = 0;
		return 1;
	}
	else
		return 1;
}

void game::rmb()
{
	if (map[A.x][A.y] == Flag)
		map[A.x][A.y] = temp[A.x][A.y];
	else if (map[A.x][A.y] > 10 && map[A.x][A.y] != Flag)
	{
		temp[A.x][A.y] = map[A.x][A.y];
		map[A.x][A.y] = Flag;
	}
	paint();
}

void game::display()
{
	int count = 0;
	if (A.x == 0 && A.y == 0)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (map[i][j] == Mine)
					++count;
			}
		}
	}
	else if (A.x == (Height - 1) && A.y == 0)
	{
		for (int i = (Height - 1); i >(Height - 3); i--)
		{
			for (int j = 0; j < 2; j++)
			{
				if (map[i][j] == Mine)
					++count;
			}
		}
	}
	else if (A.y == 0)
	{
		for (int i = (A.x - 1); i < (A.x + 2); i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (map[i][j] == Mine)
					++count;
			}
		}
	}
	else if (A.x == 0 && A.y == (Width - 1))
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = (Width - 1); j >(Width - 3); j--)
			{
				if (map[i][j] == Mine)
					++count;
			}
		}
	}
	else if (A.x == (Height - 1) && A.y == (Width - 1))
	{
		for (int i = (Height - 1); i > (Height - 3); i--)
		{
			for (int j = (Width - 1); j > (Width - 3); j--)
			{
				if (map[i][j] == Mine)
					++count;
			}
		}
	}
	else if (A.y == (Width - 1))
	{
		for (int i = (A.x - 1); i < (A.x + 2); i++)
		{
			for (int j = (Width - 1); j >(Width - 3); j--)
			{
				if (map[i][j] == Mine)
					++count;
			}
		}
	}
	else if (A.x == (Height - 1))
	{
		for (int i = (Height - 1); i > (Height - 3); i--)
		{
			for (int j = (A.y - 1); j < (A.y + 2); j++)
			{
				if (map[i][j] == Mine)
					++count;
			}
		}
	}
	else if (A.x == 0)
	{
		for (int j = (A.y - 1); j < (A.y + 2); j++)
		{
			for (int i = 0; i < 2; i++)
			{
				if (map[i][j] == Mine)
					++count;
			}
		}
	}
	else
	{
		for (int i = (A.x - 1); i < (A.x + 2); i++)
		{
			for (int j = (A.y - 1); j < (A.y + 2); j++)
			{
				if (map[i][j] == Mine)
					++count;
			}
		}
	}
	map[A.x][A.y] = count;
}

void game::settype(int a)
{
	Type = a;
}

int game::select(std::string c)
{
	if (c == "Y" || c == "y")
		return 1;
	else
		return 0;
}

game::game()
{
	A.x = 0;
	A.y = 0;
	Type = 0;
	Count = Height * Width - Num;
}

void Clear()
{
	std::cin.clear();
	std::cin.sync();
}