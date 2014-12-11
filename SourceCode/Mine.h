//這個程序主要試一下類的用法，暫且有點閃爍，以後用UI解決它
#ifndef MINE_H_
#define MINE_H_
#include <iostream>
#include <string>

struct pos
{
	int x;
	int y;
};

void Clear();

class game
{
private:
	pos A;
	int Type;										//結果的繪畫需要用到
	int Count;										//輸贏判斷
public:
	void gotoxy(int x, int y);
	void color(int a);
	void create();									//地圖生成
	void erase();									//地圖清空
	void paint();									//地圖繪製
	void hidden();									//隱藏光標
	int gameplay();									//操作相關
	int get_key();									//接收按鍵
	int lmb();										//左鍵
	void rmb();										//右鍵
	void display();									//安全塊的數字顯示
	int select(std::string c);						//用於判斷是否選擇
	int count();									//判斷輸贏
	void settype(int a);
	game();
};

#endif
