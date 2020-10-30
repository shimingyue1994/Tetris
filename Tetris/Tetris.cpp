// Tetris.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//注意：一个■符号或汉字占两个字符，光标的x的单位是一个字符，所以要错开两个汉字或■要设置x=2的大小来错开，而y方向是两个字符，只需要y=1的大小即可错开,
//y方向是换行

//#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

#define FrameX 13   //x y 窗口从那个位置开始绘制
#define FrameY 3
#define Frame_height 20 // 窗口
#define Frame_width 18


int i, j, Temp, Temp1, Temp2;
//屏幕图案数组，整个区域由80x80个块组成
int a[80][80];
int b[4];

// 方块结构体
struct Tetris
{
	int x;
	int y;
	int flag;
	int next;
	int speed;
	int number;
	int score;
	int level;
};
HANDLE hOut;//控制台句柄


// 声明一些函数
/// <summary>
/// 下面是一些方块移动绘制的函数
/// </summary>
int color(int c);
void gotoxy(int x, int y);//光标移动到指定位置
void DrwaGameframe();//绘制边框
void Flag(struct Tetris*);//产生方块的标志
void MakeTetris(struct Tetris*);//产生方块结构i
void PrintTetris(struct Tetris*);//根据方块接口将方块打印到控制台
void CleanTetris(struct Tetris*);//清除方块
void ifMove(struct Tetris*);//判断方块是否能移动
void Del_Fullline(struct Tetris*);//判断行是否填满，并删除满行的方块
/// <summary>
/// 下面是一些简单的功能函数
/// </summary>
void Gameplay();//开始游戏
void regulation();//规则
void explation();//案件规则
void welcome();//欢迎界面
void Replay(struct Tetris* tetris);//重新开始
void title();//标题
void flower();//
void close();//关闭

/// <summary>
/// 下面开始定义函数
/// </summary>
/// 控制台字体颜色的设置函数
int color(int c) {
	//设置控制台窗体字体的颜色，第一个参数是标准输出句柄，句柄指向一个“对象”，这个对象可以是文件、窗口等等，c++中可能是一个整数或指针等。
	//stdout stderr都对应于屏幕 ，stdin通常是键盘，也可能是鼠标
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
	return 0;
}


/*设置文字显示位置，文字会在光标位置处开始绘制，通过改变光标位置来控制文字位置*/
void gotoxy(int x, int y) {
	COORD pos;//coord结构体，通过它来控制控制台光标位置
	pos.X = x;
	pos.Y = y;
	//设置控制台光标位置,位置大小是一个字符
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

/*设置欢迎界面上方的标题 注意：一个■ 或汉字占两个字符，光标的x方向是一个字符大小（英文），y方向是第二行*/
void title() {
	color(15);//设置标题颜色
	gotoxy(24,3);//设置标题开始的显示位置
	printf("趣 味 俄 罗 斯 方 块\n");

	//第一个图形
	color(11);//亮蓝色
	gotoxy(18,5);
	printf("■");//■
	gotoxy(18, 6);
	printf("■■");//■■
	gotoxy(18, 7);
	printf("■");//■

	//第二个图形
	color(14);//黄色
	gotoxy(26,6);
	printf("■■");//■■
	gotoxy(28, 7);
	printf("■■");// ■■


	//第三个图形
	color(10);//绿色
	gotoxy(36,6);
	printf("■■");//■■
	gotoxy(36, 7);
	printf("■■");//■■


	//第四个图形
	color(13);//粉色
	gotoxy(45,5);
	printf("■");//■
	gotoxy(45, 6);
	printf("■");//■
	gotoxy(45, 7);
	printf("■");//■
	gotoxy(45, 8);
	printf("■");//■


	//第四个图形
	color(12);//红色
	gotoxy(56,6);
	printf("■");//■
	gotoxy(52, 7);
	printf("■■■");//■■■
}

/*绘制字符花,代码太多了 */
void flower() {
	gotoxy(66,11);
	color(12);
	printf("(_)");

	gotoxy(64,12);
	printf("(_)");

	gotoxy(68,12);
	printf("(_)");

	gotoxy(66,13);
	printf("(_)");

	gotoxy(67,12);
	color(6);
	printf("@");


}


/// <summary>
/// 欢迎边框
/// </summary>
void welcome() {
	int n;
	int i, j = 1;
	color(14);
	for ( i = 9; i <=20; i++) //此时y轴从9开始 边框在title()中绘制的图形下面,边框的高度是 20-9 = 11+1=12个字符 最后多一个20
	{
		for ( j = 15; j <= 60; j++)//x轴从15开始 宽度是60-15 = 45+1 = 46个字符，最后多一个60
		{
			gotoxy(j, i);
			if (i == 9 || i == 20) {
				printf("=");
			}
			if (j == 15 || j == 59) {
				printf("||");
			}
		}
	}
	/*菜单选项的文字 15,9*/
	color(12);
	gotoxy(25,12);
	printf("1.开始游戏");

	gotoxy(40, 12);
	printf("2.按键说明");

	gotoxy(25, 17);
	printf("3.游戏规则");

	gotoxy(40, 17);
	printf("4.退出");

	gotoxy(21,22);
	color(3);
	printf("请选择[1 2 3 4]:[ ]\b\b");//\b是退格，让输入光标向后退到[ ]里面去

	color(14);
	//标准输入系列的函数，将键盘的数字读出，并存入n变量的内存位置，这样我们读n就能够拿到键盘输入值了，
	//此时函数会等待键盘输入，并敲下回车键才继续往下执行
	scanf_s("%d", &n);

	switch (n)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:

		break;
	case 4:

		break;
	default:
		break;
	}

}



int main()
{
	title();
	flower();
	welcome();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
