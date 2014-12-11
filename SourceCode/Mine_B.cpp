//此文件是主要運行文件，內含main()
#include <iostream>
#include <string>
#include <cstdlib>
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
		Player.erase();
		int *temp = new int(Player.gameplay());
		while (*temp != LMB)
			*temp = Player.gameplay();
		Player.settype(1);
		Player.create();
		Player.display();
		*temp = Player.gameplay();
		while (*temp != Lose && *temp != Win)
			*temp = Player.gameplay();
		delete temp;
		Player.settype(Lose);							//不用在意這些細節
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
	std::cout << "Bye!\n";
	system("pause");
	return 0;
}