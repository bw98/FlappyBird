/*
画面大小350*600
鸟的大小100*70
柱子宽处宽度140，窄处宽度100，宽处厚度30，颜色
*/
#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <time.h>
// 引用 Windows Multimedia API
#pragma comment(lib,"Winmm.lib")
void print();
void begin();
void printstone();//人家才不是作柱子的呢
void bird();//控制鸟的下降和上升
void judgement();//判断语句
void scoleprint();
void endorretry();
int bird_x=150,bird_y=300,i=0,k=0;//鸟的左上角坐标
int scole=0,t=0;
int stone_x1,stone_y1;//上截柱子左下坐标
int stone_x2,stone_y2;//上截柱子左下坐标
IMAGE backgrand,bird1[4],bird2[4],scole1[10],scole2[10],stone_up1,stone_up2,stone_down1,stone_down2
,stone_up3,stone_up4,stone_down3,stone_down4;//图片储存变量

MOUSEMSG m;		// 定义鼠标消息
int main()
{
	if(t==0)
	{
		begin();
		t++;
	}
	
	if(t)
		print();
	getch();//制造停顿
	bird_y=300;bird_x=150;i=0;k=0;scole=0;
	
	while(1)
	{
		bird();
		print();
		judgement();
	}
	closegraph();
	return 0;
}
void print()
{
	putimage(0, 0, &backgrand);//背景图像
	printstone();//画柱子
	putimage(bird_x, bird_y,&bird1[i%3],NOTSRCERASE);
	putimage(bird_x, bird_y,&bird2[i%3],SRCINVERT);
	if(k%5==0)
		i++;
	k++;
	scoleprint();
	FlushBatchDraw();		// 绘制	
}
void printstone()//柱子移动规律/哭
{
    Sleep(30);
	if(stone_x1>210)//此时画面存在两根柱子
	{
		
		putimage(stone_x1, stone_y1, &stone_up2,NOTSRCERASE);
		putimage(stone_x1, stone_y1, &stone_up1,SRCINVERT);
		putimage(stone_x1, stone_y1+750, &stone_down2,NOTSRCERASE);
		putimage(stone_x1, stone_y1+750, &stone_down1,SRCINVERT);
		putimage(stone_x2, stone_y2, &stone_up4,NOTSRCERASE);
		putimage(stone_x2, stone_y2, &stone_up3,SRCINVERT);
		putimage(stone_x2, stone_y2+750, &stone_down4,NOTSRCERASE);
		putimage(stone_x2, stone_y2+750, &stone_down3,SRCINVERT);
		stone_x1--;stone_x2--;
	}
	else if(stone_x1==210)//左柱子消失，将stone_x2,stone_y2值归位
	{
		stone_x2=stone_x1;
		stone_y2=stone_y1;
		putimage(stone_x1, stone_y1, &stone_up2,NOTSRCERASE);
		putimage(stone_x1, stone_y1, &stone_up1,SRCINVERT);
		putimage(stone_x1, stone_y1+750, &stone_down2,NOTSRCERASE);
		putimage(stone_x1, stone_y1+750, &stone_down1,SRCINVERT);
		stone_x1--;
		stone_x2--;
	}
	else if(stone_x1<210&&stone_x1>0)//画面只存在一根柱子的情况
	{
		putimage(stone_x1, stone_y1, &stone_up2,NOTSRCERASE);
		putimage(stone_x1, stone_y1, &stone_up1,SRCINVERT);
		putimage(stone_x1, stone_y1+750, &stone_down2,NOTSRCERASE);
		putimage(stone_x1, stone_y1+750, &stone_down1,SRCINVERT);
		stone_x1--;
		stone_x2--;	 
	}
	if(stone_x1==0)//柱子左端到站，生成新柱子
	{	  
		stone_y1=rand()%310-555;
		stone_x1=350;
		putimage(stone_x1, stone_y1, &stone_up2,NOTSRCERASE);
		putimage(stone_x1, stone_y1, &stone_up1,SRCINVERT);
		putimage(stone_x1, stone_y1+750, &stone_down2,NOTSRCERASE);
		putimage(stone_x1, stone_y1+750, &stone_down1,SRCINVERT);
		stone_x1--;
		stone_x2--;
	}
}

void begin()
{
	mciSendString("open \"..\\..\\sounds\\background.mp3\" alias music ", NULL, 0, NULL);//背景音乐
	mciSendString("play music", NULL, 0, NULL);
	initgraph(350,600);
	// 获取窗口句柄
	HWND hwnd = GetHWnd();
	// 设置窗口标题文字
	SetWindowText(hwnd, "江超群制作");
	IMAGE beforegame;
	loadimage(&beforegame,"..\\..\\素材库\\beforegame.jpg");
	putimage(0,0,&beforegame);
	Sleep(1000);
	getch();
	BeginBatchDraw();// 开启批量绘图模式
	loadimage(&backgrand, "..\\..\\素材库\\backgroundfd.jpg");//载入背景图片
	//鸟
	loadimage(&bird2[0], "..\\..\\素材库\\bird1-2.gif");
	loadimage(&bird1[0], "..\\..\\素材库\\bird1-1.gif");
	loadimage(&bird2[1], "..\\..\\素材库\\bird2-2.gif");
	loadimage(&bird1[1], "..\\..\\素材库\\bird2-1.gif");
	loadimage(&bird2[2], "..\\..\\素材库\\bird3-2.gif");
	loadimage(&bird1[2], "..\\..\\素材库\\bird3-1.gif");
	loadimage(&bird2[3], "..\\..\\素材库\\bird4-2.gif");
	loadimage(&bird1[3], "..\\..\\素材库\\bird4-1.gif");
	//柱子
	loadimage(&stone_up1,"..\\..\\素材库\\stone_up1.gif");
	loadimage(&stone_up2,"..\\..\\素材库\\stone_up2.gif");
	loadimage(&stone_down1,"..\\..\\素材库\\stone_down1.gif");
	loadimage(&stone_down2,"..\\..\\素材库\\stone_down2.gif");
	loadimage(&stone_up3,"..\\..\\素材库\\stone_up1.gif");
	loadimage(&stone_up4,"..\\..\\素材库\\stone_up2.gif");
	loadimage(&stone_down3,"..\\..\\素材库\\stone_down1.gif");
	loadimage(&stone_down4,"..\\..\\素材库\\stone_down2.gif");
	//数字
	loadimage(&scole1[0],"..\\..\\素材库\\0_1.jpg");
	loadimage(&scole2[0],"..\\..\\素材库\\0_2.jpg");
	loadimage(&scole1[1],"..\\..\\素材库\\1_1.jpg");
	loadimage(&scole2[1],"..\\..\\素材库\\1_2.jpg");
	loadimage(&scole1[2],"..\\..\\素材库\\2_1.jpg");
	loadimage(&scole2[2],"..\\..\\素材库\\2_2.jpg");
	loadimage(&scole1[3],"..\\..\\素材库\\3_1.jpg");
	loadimage(&scole2[3],"..\\..\\素材库\\3_2.jpg");
	loadimage(&scole1[4],"..\\..\\素材库\\4_1.jpg");
	loadimage(&scole2[4],"..\\..\\素材库\\4_2.jpg");
	loadimage(&scole1[5],"..\\..\\素材库\\5_1.jpg");
	loadimage(&scole2[5],"..\\..\\素材库\\5_2.jpg");
	loadimage(&scole1[6],"..\\..\\素材库\\6_1.jpg");
	loadimage(&scole2[6],"..\\..\\素材库\\6_2.jpg");
	loadimage(&scole1[7],"..\\..\\素材库\\7_1.jpg");
	loadimage(&scole2[7],"..\\..\\素材库\\7_2.jpg");
	loadimage(&scole1[8],"..\\..\\素材库\\8_1.jpg");
	loadimage(&scole2[8],"..\\..\\素材库\\8_2.jpg");
	loadimage(&scole1[9],"..\\..\\素材库\\9_1.jpg");
	loadimage(&scole2[9],"..\\..\\素材库\\9_2.jpg");
	srand(time(0));//初始化种子
	print();
	//第一根柱子，初始化
	stone_y1=rand()%310-555;
	stone_x1=350;
	stone_x2=stone_y2=-9999;
}
void bird()
{
	char space;
	
	if(kbhit())//读取空格
	{
		space=getch();
		if(space==' ')
		{
			bird_y-=80;	
		}
		else if(space==27)
			getch();		
	}
	else
	{
		bird_y+=3;
	}
	while(MouseHit())
	{
		// 获取一条鼠标消息
		m = GetMouseMsg();
		switch(m.uMsg)
		{
		case WM_LBUTTONDOWN:
			bird_y-=80;
			break;
		case WM_RBUTTONDOWN:
			getch();
			break;
		}
	}
	
}
void judgement()
{
	if((stone_x1>10 && stone_x1<20)||(stone_x1>174&&stone_x1<184))
	{
		if((bird_y>(stone_y1+576)&&bird_y<(stone_y1+600))||((bird_y>(stone_y1+726))&&bird_y<(stone_y1+750)))
			endorretry();//结束游戏
	}
	else if(stone_x1>=20 && stone_x1<=174)
	{
		if(!(bird_y>(stone_y1+600)&&bird_y<(stone_y1+726)))
			endorretry();	//结束游戏
	}
	if(bird_y>576)
		endorretry();//结束游戏
	if(stone_x1==150)
		scole++;
}
void endorretry()
{
	if(bird_y<550 && stone_x1>160)
	{	
		while(bird_y<550)
		{
			putimage(0, 0, &backgrand);//背景图像
			putimage(stone_x1, stone_y1, &stone_up2,NOTSRCERASE);
			putimage(stone_x1, stone_y1, &stone_up1,SRCINVERT);
			putimage(stone_x1, stone_y1+750, &stone_down2,NOTSRCERASE);
			putimage(stone_x1, stone_y1+750, &stone_down1,SRCINVERT);
			putimage(stone_x2, stone_y2, &stone_up4,NOTSRCERASE);
			putimage(stone_x2, stone_y2, &stone_up3,SRCINVERT);
			putimage(stone_x2, stone_y2+750, &stone_down4,NOTSRCERASE);
			putimage(stone_x2, stone_y2+750, &stone_down3,SRCINVERT);
			putimage(bird_x, bird_y,&bird1[3],NOTSRCERASE);
			putimage(bird_x, bird_y,&bird2[3],SRCINVERT);
			FlushBatchDraw();
			bird_y++;
		}
	}
	IMAGE gameover1,gameover2,atlast;
	loadimage(&gameover1, "..\\..\\素材库\\gameover1.gif");
	loadimage(&gameover2, "..\\..\\素材库\\gameover2.gif");
	putimage(80, 200, &gameover1,NOTSRCERASE);
	putimage(80, 200, &gameover2,SRCINVERT);
	FlushBatchDraw();
	Sleep(1000);
	loadimage(&atlast, "..\\..\\素材库\\atlast.jpg");
	putimage(0,0,&atlast);
	scoleprint();
	FlushBatchDraw();
	getch();	
	//第一根柱子
	stone_y1=rand()%310-555;
	stone_x1=350;
	stone_x2=stone_y2=-9999;
	bird_y=300;
	scole=0;
	main();	
	
}
void scoleprint()
{
	IMAGE *fen1[6],*fen2[6];
	int he,weishu=1,i=0,sdsf=scole;
	if(sdsf==0)
	{
		putimage(250,50,&scole1[0],NOTSRCERASE);
		putimage(250,50,&scole2[0],SRCINVERT);
		
	}
	while(sdsf>0)
	{
		he=sdsf%10;
		fen1[i]=&scole1[he];
		fen2[i]=&scole2[he]; 
		putimage(300-50*weishu,50,fen1[i],NOTSRCERASE);
		putimage(300-50*weishu,50,fen2[i],SRCINVERT);
		sdsf/=10;
		i++;
		weishu++;
	}
	
}

