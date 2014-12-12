//此文件是主要運行文件，內含main()，有些C和C++的IO庫混用，懶得改了，別在意
#include <iostream>
#include <string>
#include <cstdlib>
#include <conio.h>
#include "Mine.h"										//錯誤提示很煩，所以這裏包涵了頭文件，注意用#ifndef
#define LMB 5
#define Lose 8
#define Win 99

int main()
{
	system("Title MineSweeper");
	for (;;)											//此處也是一個比較個人喜歡用的技巧，創建一個無任何參數的for（while不行）然後利用if去控制，新手不建議用
	{
		game Player;
		Player.hidden();
		system("cls");
		std::string str;
		std::cout << "開始遊戲？(Y/N)\n";				//注意Y/N千萬不要寫\號，是轉義序列
		str = std::cin.get();
		Clear();
		if (Player.select(str))
			system("cls");
		else
			break;
		Player.create();
		int *temp = new int(Player.gameplay());
		while (*temp != LMB && *temp != Win)
			*temp = Player.gameplay();
		Player.settype(1);
		Player.create();
		Player.display();
		Player.paint();
		if (*temp == LMB)
		{
			*temp = Player.gameplay();
			while (*temp != Lose && *temp != Win)
				*temp = Player.gameplay();
		}
		if (*temp == Lose)
		{
			Player.settype(Lose);
			system("cls");
			Player.paint();
		}
		else if (*temp == Win)
		{
			Player.settype(Win);
			system("cls");
			Player.paint();
		}
		delete temp;
		Clear();
		std::cin.get();
		Clear();
		system("cls");
		std::cout << "遊戲結束！再來一遍？(Y/N)\n";
		str = std::cin.get();
		Clear();
		if (Player.select(str))
			continue;
		else
			break;
	}
	system("cls");
	std::cout << "Bye!\n";
	system("pause");
	return 0;
}