//此文件是主要運行文件，內含main()
#include <iostream>
#include <string>
#include <cstdlib>
#include "Mine.h"										//錯誤提示很煩，所以這裏包涵了頭文件，注意用#ifndef
#define LMB 5
#define Lose 8

int main()
{
	system("Title MineSweeper");
	game Player;
	Player.hidden();
	for (;;)											//此處也是一個比較個人喜歡用的技巧，創建一個無任何參數的for（while不行）然後利用if去控制，新手不建議用
	{
		Player.settype(0);
		system("cls");
		std::string str;
		std::cout << "開始遊戲？(Y/N)\n";				//注意Y/N千萬不要寫\號，是轉義序列
		str = std::cin.get();
		Clear();
		if (Player.select(str))
			system("cls");
		else
			break;
		Player.erase();
		while (Player.gameplay() != LMB)
			continue;
		Player.settype(1);
		Player.create();
		Player.display();
		while (Player.gameplay() != Lose)
			continue;
		Player.settype(Lose);
		system("cls");
		Player.paint();
		std::cout << std::endl;
		std::cin.get();
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
	Player.~game();
	std::cout << "Bye!\n";
	system("pause");
	return 0;
}