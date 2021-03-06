
#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include <tchar.h>
#include<Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

/*
贪吃蛇小游戏
基于vs2017
使用easyx图形库
来自http://www.easyx.cn/
制作人：1707004237  王眺
*/


//加分数显示

//用动态链表表示每一个小方块  10*10
typedef struct block {
	int x1;
	int x2;
	int y1;
	int y2;
	struct block * next;
}bl;

bl *h = NULL, *p = NULL, *pp = NULL, *q = NULL;

void createlist()
{
	int i;
	p = (bl*)malloc(sizeof(bl));
	p->x1 = 310;
	p->x2 = 320;
	p->y1 = 230;
	p->y2 = 240;
	h = p;
	p->next = NULL;
	for (i = 0; i < 4; i++)
	{
		pp = (bl*)malloc(sizeof(bl));
		p->next = pp;
		pp->x1 = p->x1 - 10;
		pp->x2 = p->x2 - 10;
		pp->y1 = p->y1;
		pp->y2 = p->y2;
		pp->next = NULL;
		p = p->next;
	}
}

int isBorder()
{
	p = h;
	while(p->next)
	{p = p->next; }

	if (p->x1 == 110 || p->x2 == 530 || p->y1 == 80 || p->y2 == 400)
		return 1;
	else
		return 0;
}

int isTouch()
{
	p = h;
	int a,b;
	
	while (p->next)
	{
		p = p->next;
	}
	a = p->x1;
	b = p->y1;
	p = h;
	while (p->next->next)
	{
		if (a == p->x1 && b == p->y1)
			return 1;
		p = p->next;
	}
	return 0;
}

int main()
{
	initgraph(640, 480);

	//游戏开始界面
	settextstyle(50, 30, _T("SimHei"));
	settextcolor(RED);
	outtextxy(230, 200, _T("贪吃蛇"));
	settextstyle(20, 10, _T("SimHei"));
	outtextxy(250, 260, _T("作者：王眺"));
	outtextxy(250, 280, _T("按任意键开始"));
	_getch();
	cleardevice();

	//一只初始长度为5的贪吃蛇10*10
	createlist();
	p = h;
	pp = p->next;

	
	
	//一个随机点10*10
	int xb1, xb2, yb1, yb2;

	//边框为400*300  420*320   范围90-390  120-520
	setfillcolor(RED);
	solidrectangle(110, 80, 120, 390);
	solidrectangle(520, 80, 530, 390);
	solidrectangle(120, 80, 520, 90);
	solidrectangle(110, 390, 530, 400);


	while (pp)
	{
		setfillcolor(GREEN);
		solidrectangle(p->x1, p->y1, p->x2, p->y2);
		p = p->next;
		pp = p->next;
	}
	setfillcolor(BLUE);
	solidrectangle(p->x1, p->y1, p->x2, p->y2);

	TCHAR c = 0;
	//画出随机点
	srand((unsigned)time(NULL));
	xb1 = (rand() % 40 + 12) * 10;   //120-520
	xb2 = xb1 + 10;
	yb1 = (rand() % 30 + 9) * 10;    //90-390
	yb2 = yb1 + 10;
	setfillcolor(YELLOW);
	solidrectangle(xb1, yb1, xb2, yb2);
	c = 'a';
	int v = 500;
	int score = 0;
	char s[5];
	sprintf_s(s, "%d", score);

	//文字说明
	settextcolor(RED);
	outtextxy(280, 60, _T("贪吃蛇游戏"));



	while (1)
	{

		Sleep(v);

		if (_kbhit() != 0)    //用AI
		{
			c = _getch();
		}
		//		putchar(c);

		//擦掉上次的小蛇
		p = h;
		while (p)
		{
			setfillcolor(BLACK);
			solidrectangle(p->x1, p->y1, p->x2, p->y2);
			p = p->next;
		}
		setfillcolor(YELLOW);
		solidrectangle(xb1, yb1, xb2, yb2);
		//改变链表
		p = h;
		pp = p->next;
		while (pp)
		{
			p->x1 = pp->x1;
			p->x2 = pp->x2;
			p->y1 = pp->y1;
			p->y2 = pp->y2;
			p = p->next;
			pp = p->next;
		}

		//获取键盘信息
		switch (c)
		{
		case 'w':p->y1 -= 10, p->y2 -= 10;
			break;
		case 's':p->y1 += 10, p->y2 += 10;
			break;
		case 'a':p->x1 -= 10, p->x2 -= 10;
			break;
		case 'd':p->x1 += 10, p->x2 += 10;
			break;
		}

		//画出改变后的小蛇
		p = h;
		pp = p->next;
		while (pp)
		{
			setfillcolor(GREEN);
			solidrectangle(p->x1, p->y1, p->x2, p->y2);
			p = p->next;
			pp = p->next;
		}
		setfillcolor(BLUE);
		solidrectangle(p->x1, p->y1, p->x2, p->y2);

		setfillcolor(YELLOW);
		solidrectangle(xb1, yb1, xb2, yb2);


		//判断是否吃到
		if ((p->x1 == xb1) && (p->y1 == yb1))
		{
			score++;
			sprintf_s(s, "%d", score);

			q = (bl*)malloc(sizeof(bl));
			q->next = h;
			h = q;

			if(v>100)
			v -= 30;

			//画出随机点
			srand((unsigned)time(NULL));
			xb1 = (rand() % 40 + 12) * 10;   //120-520
			xb2 = xb1 + 10;
			yb1 = (rand() % 30 + 9) * 10;    //90-390
			yb2 = yb1 + 10;
			setfillcolor(YELLOW);
			solidrectangle(xb1, yb1, xb2, yb2);
		}

		//显示分数
		settextstyle(20, 10, _T("SimHei"));
		settextcolor(RED);
		outtextxy(0,0, _T("您的分数为："));
		outtextxy(120, 0, s[0]);
		if(score>=10)
			outtextxy(130, 0, s[1]);


		//判断有无死亡
		if (isBorder() == 1)
			break;
		if (isTouch() == 1)
			break;
	}

	//显示结束
		cleardevice();
		settextstyle(50, 30, _T("SimHei"));
		settextcolor(RED);
		outtextxy(200, 200, _T("Game Over!"));
		settextstyle(20, 10, _T("SimHei"));
		settextcolor(RED);
		outtextxy(240,250 , _T("您的分数为："));
		outtextxy(350, 250, s[0]);
		if (score >= 10)
			outtextxy(360, 250, s[1]);
	_getch();
	closegraph();
	return 0;
}

