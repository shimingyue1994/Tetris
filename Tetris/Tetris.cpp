// Tetris.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//注意：一个■符号或汉字横向占两个字符，竖着的方向占一个字符，所以要错开两个汉字或■要设置x=2的大小来错开，而y方向是两个字符，只需要y=1的大小即可错开,
//y方向是换行

//#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

#define FrameX 13   //x y 窗口从那个位置开始绘制
#define FrameY 3
#define Frame_height 20 // 窗口的尺寸（宽 高）
#define Frame_width 18


int i, j, Temp, Temp1, Temp2;
//屏幕图案数组，整个区域被分割成80*80的分割块，下面的逻辑就是向这个方格纸里填充方块
int a[80][80];
int b[4];

// 方块结构体
struct Tetris
{
	int x; //中心方块的x坐标
	int y;//中心方块的y坐标
	int flag;//方块的类型
	int next;//下一个方块的类型
	int speed;//方块的移动速度
	int number;//方块的个数
	int score;//分数
	int level;//级别
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
int ifMove(struct Tetris*);//判断方块是否能移动
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
	return 0;
}


/*设置文字显示位置，文字会在光标位置处开始绘制，通过改变光标位置来控制文字位置*/
void gotoxy(int x, int y) {
	COORD pos;//coord结构体，通过它来控制控制台光标位置
	pos.X = x;
	pos.Y = y;
	//设置控制台光标位置,位置大小是一个字符
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/*设置欢迎界面上方的标题 注意：一个■ 或汉字占两个字符，光标的x方向是一个字符大小（英文），y方向是第二行*/
void title() {
	color(15);//设置标题颜色
	gotoxy(24, 3);//设置标题开始的显示位置
	printf("趣 味 俄 罗 斯 方 块\n");

	//第一个图形
	color(11);//亮蓝色
	gotoxy(18, 5);
	printf("■");//■
	gotoxy(18, 6);
	printf("■■");//■■
	gotoxy(18, 7);
	printf("■");//■

	//第二个图形
	color(14);//黄色
	gotoxy(26, 6);
	printf("■■");//■■
	gotoxy(28, 7);
	printf("■■");// ■■


	//第三个图形
	color(10);//绿色
	gotoxy(36, 6);
	printf("■■");//■■
	gotoxy(36, 7);
	printf("■■");//■■


	//第四个图形
	color(13);//粉色
	gotoxy(45, 5);
	printf("■");//■
	gotoxy(45, 6);
	printf("■");//■
	gotoxy(45, 7);
	printf("■");//■
	gotoxy(45, 8);
	printf("■");//■


	//第四个图形
	color(12);//红色
	gotoxy(56, 6);
	printf("■");//■
	gotoxy(52, 7);
	printf("■■■");//■■■
}

/*绘制字符花,代码太多了 */
void flower() {
	gotoxy(66, 11);
	color(12);
	printf("(_)");

	gotoxy(64, 12);
	printf("(_)");

	gotoxy(68, 12);
	printf("(_)");

	gotoxy(66, 13);
	printf("(_)");

	gotoxy(67, 12);
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
	for (i = 9; i <= 20; i++) //此时y轴从9开始 边框在title()中绘制的图形下面,边框的高度是 20-9 = 11+1=12个字符 最后多一个20
	{
		for (j = 15; j <= 60; j++)//x轴从15开始 宽度是60-15 = 45+1 = 46个字符，最后多一个60
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
	gotoxy(25, 12);
	printf("1.开始游戏");

	gotoxy(40, 12);
	printf("2.按键说明");

	gotoxy(25, 17);
	printf("3.游戏规则");

	gotoxy(40, 17);
	printf("4.退出");

	gotoxy(21, 22);
	color(3);
	printf("请选择[1 2 3 4]:[ ]\b\b");//\b是退格，让输入光标向后退到[ ]里面去

	color(14);
	//标准输入系列的函数，将键盘的数字读出，并存入n变量的内存位置，这样我们读n就能够拿到键盘输入值了，
	//此时函数会等待键盘输入，并敲下回车键才继续往下执行
	scanf_s("%d", &n);
	//判断键盘的输入，执行相关的操作
	switch (n)
	{
	case 1://开始
		system("cls");//这句代码用来清屏幕
		DrwaGameframe();
		break;
	case 2: //按键说明

		break;
	case 3://规则

		break;
	case 4://退出

		break;
	default:
		break;
	}

}

/*绘制主窗体，按键说明  方块的包裹区域*/
void DrwaGameframe() {
	/*标题*/
	gotoxy(FrameX + Frame_width - 7, FrameY - 2);
	color(11);//亮蓝
	printf("趣味俄罗斯方块");

	/*下一个方块出现的位置*/
	gotoxy(FrameX + Frame_width * 2 + 3, FrameY + 7);
	color(2);//深绿
	printf("**********");
	color(3);
	printf("下一个方块：");

	gotoxy(FrameX + Frame_width * 2 + 3, FrameY + 13);
	color(2);//深绿
	printf("**********");

	/*主窗体按键说明*/
	gotoxy(FrameX + Frame_width * 2 + 3, FrameY + 17);
	color(14);//黄色
	printf("↑键：旋转");

	gotoxy(FrameX + Frame_width * 2 + 3, FrameY + 19);
	color(14);
	printf("空格：暂停游戏");

	gotoxy(FrameX + Frame_width * 2 + 3, FrameY + 15);
	color(14);
	printf("Esc：退出游戏");


	gotoxy(FrameX - 13, FrameY + Frame_height / 2);
	color(6);
	printf("边界区域→");
	gotoxy(FrameX - 13, FrameY + Frame_height / 2 + 1);
	printf("0：无方块");
	gotoxy(FrameX - 13, FrameY + Frame_height / 2 + 2);
	printf("1：有方块");
	gotoxy(FrameX - 13, FrameY + Frame_height / 2 + 3);
	printf("2：边界区域");
	//开始绘制包含方块的边框
	gotoxy(FrameX, FrameY);
	color(12);//红色
	printf(" ╭"); //打印框角
	gotoxy(FrameX + Frame_width * 2 - 2, FrameY);
	printf("╮ "); //打印框角
	gotoxy(FrameX, FrameY + Frame_height);
	printf(" ╰"); //打印框角
	gotoxy(FrameX + Frame_width * 2 - 2, FrameY + Frame_height);
	printf("╯ "); //打印框角

	a[FrameX][FrameY + Frame_height] = 2;//边界标记 左下角: 向这个数组里放个标记，用来判断方块是否出界，如果数组中元素等于“2”就是出界了
	a[FrameX + 2 * Frame_width - 2][FrameY + Frame_height] = 2;//右下角

	///上
	for (i = 2; i < Frame_width * 2 - 2; i += 2)//打印上边框 每个制表符占两个字符
	{
		gotoxy(FrameX + i, FrameY);
		printf("─");
	}
	//下
	for (i = 2; i < Frame_width * 2 - 2; i += 2) //打印下边框
	{
		gotoxy(FrameX + i, FrameY + Frame_height);
		printf("─");
		a[FrameX + i][FrameY + Frame_height] = 2;//打上边界标记
	}

	//左
	for (i = 1; i < Frame_height; i++) //打印左边框 竖着的方向无论中英文都是2个字符大小的距离
	{

		gotoxy(FrameX, FrameY + i);
		printf(" |");
		a[FrameX][FrameY + i] = 2;//打上左边界标记
	}

	//右
	for (i = 1; i < Frame_height; i++) //打印右边框 竖着的方向无论中英文都是2个字符大小的距离
	{
		gotoxy(FrameX + 2 * Frame_width - 2, FrameY + i);
		printf(" |");
		a[FrameX + 2 * Frame_width - 2][FrameY + i] = 2;//打上右边界标记
	}


	printf("\n\n");
}

/// <summary>
///根据传进来的方块结构绘制方块,主要定义方块位置
/// </summary>
/// <param name=""></param>
void MakeTetris(struct Tetris* tetris) {
	a[tetris->x][tetris->y] = b[0];//中心方块的图形状态，就是第一个“■”的位置，根据他的位置绘制其他方块的位置
	switch (tetris->flag)//根据类型返回不同的方块
	{
	case 1: {/*田字方块 ■■
					   ■■*/
		color(10);//黄色
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x + 2][tetris->y - 1] = b[2];
		a[tetris->x + 2][tetris->y] = b[3];
		break;
	}
	case 2: {/*直线方块 横着的*/
		color(13);//粉色
		a[tetris->x - 2][tetris->y] = b[1];
		a[tetris->x + 2][tetris->y] = b[2];
		a[tetris->x + 4][tetris->y] = b[3];
		break;
	}
	case 3: {/*直线方块 竖着的*/
		color(13);//粉色
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x][tetris->y - 2] = b[2];
		a[tetris->x][tetris->y + 1] = b[3];
		break;
	}
	case 4: {/*T字方块*/
		color(11);//白色
		a[tetris->x - 2][tetris->y] = b[1];
		a[tetris->x + 2][tetris->y] = b[2];
		a[tetris->x][tetris->y + 1] = b[3];
		break;
	}
	case 5: {/*T字方块 顺时针90度*/
		color(11);//白色
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x][tetris->y + 1] = b[2];
		a[tetris->x - 2][tetris->y] = b[3];
		break;
	}
	case 6: {/*T字方块 顺时针180度*/
		color(11);//白色
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x - 2][tetris->y] = b[2];
		a[tetris->x + 2][tetris->y] = b[3];
		break;
	}
	case 7: {/*T字方块 顺时针270度*/
		color(11);//白色
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x][tetris->y + 1] = b[2];
		a[tetris->x + 2][tetris->y] = b[3];
		break;
	}
	case 8: {/*z字方块*/
		color(14);//另一种黄色
		a[tetris->x][tetris->y + 1] = b[1];
		a[tetris->x - 2][tetris->y] = b[2];
		a[tetris->x + 2][tetris->y + 1] = b[3];
		break;
	}
	case 9: {/*z字方块 顺时针*/
		color(14);//另一种黄色
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x - 2][tetris->y] = b[2];
		a[tetris->x - 2][tetris->y + 1] = b[3];
		break;
	}

	case 10: {/*反z字方块*/
		color(14);//另一种黄色
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x - 2][tetris->y - 1] = b[2];
		a[tetris->x + 2][tetris->y] = b[3];
		break;
	}

	case 11: {/*反z字方块 顺时针*/
		color(14);//另一种黄色
		a[tetris->x][tetris->y + 1] = b[1];
		a[tetris->x - 2][tetris->y - 1] = b[2];
		a[tetris->x - 2][tetris->y] = b[3];
		break;
	}
	case 12: {/*7字形方块*/
		color(12);//另一种红色
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x][tetris->y + 1] = b[2];
		a[tetris->x - 2][tetris->y - 1] = b[3];
		break;
	}
	case 13: {/*7字形方块 顺时针90度*/
		color(12);//另一种红色
		a[tetris->x - 2][tetris->y] = b[1];
		a[tetris->x + 2][tetris->y - 1] = b[2];
		a[tetris->x + 2][tetris->y] = b[3];
		break;
	}
	case 14: {/*7字形方块 顺时针180度*/
		color(12);//另一种红色
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x][tetris->y + 1] = b[2];
		a[tetris->x + 2][tetris->y + 1] = b[3];
		break;
	}
	case 15: {/*7字形方块 顺时针270度*/
		color(12);//另一种红色
		a[tetris->x - 2][tetris->y] = b[1];
		a[tetris->x - 2][tetris->y + 1] = b[2];
		a[tetris->x + 2][tetris->y] = b[3];
		break;
	}
	case 16: {/*反7字方块*/
		color(12);//另一种红色
		a[tetris->x][tetris->y + 1] = b[1];
		a[tetris->x][tetris->y - 1] = b[2];
		a[tetris->x + 2][tetris->y - 1] = b[3];
		break;
	}
	case 17: {/*反7字方块 顺时针90度*/
		color(12);//另一种红色
		a[tetris->x - 2][tetris->y] = b[1];
		a[tetris->x + 2][tetris->y + 1] = b[2];
		a[tetris->x + 2][tetris->y] = b[3];
		break;
	}
	case 18: {/*反7字方块 顺时针180度*/
		color(12);//另一种红色
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x][tetris->y + 1] = b[2];
		a[tetris->x - 2][tetris->y + 1] = b[3];
		break;
	}
	case 19: {
		color(12);//另一种红色
		a[tetris->x - 2][tetris->y] = b[1];
		a[tetris->x - 2][tetris->y - 1] = b[2];
		a[tetris->x + 2][tetris->y] = b[3];
		break;
	}

	default:
		break;
	}
}
/// <summary>
/// 将方块打印在屏幕上
/// </summary>
/// <param name="tetris"></param>
void PrintTetris(struct Tetris* tetris) {
	for (i = 0; i < 4; i++)
	{
		b[i] = 1;//1表示有方块
	}
	MakeTetris(tetris);
	//循环方块可能出现的所有位置并绘制出来，MakeTetris可以看出方块的范围是 x-2 <= x <= x+4    y-2 <= y <= y+1
	for (i = tetris->x - 2; i <= tetris->x + 4; i += 2) {
		for (j = tetris->y - 2; j <= tetris->y + 1; j++) {
			if (a[i][j] == 1 && j > FrameY)
			{
				gotoxy(i, j);
				printf("■");
			}
		}
	}

	//打印菜单信息
	gotoxy(FrameX + FrameX * 2 + 3, FrameY + 1);
	color(4);//暗红色
	printf("level：");
	color(12);//亮红色
	printf("%d", tetris->level);

	//打印分数
	gotoxy(FrameX + FrameX * 2 + 3, FrameY + 3);
	color(4);//暗红色
	printf("score：");
	color(12);//亮红色
	printf("%d", tetris->score);

	//打印速度
	gotoxy(FrameX + FrameX * 2 + 3, FrameY + 5);
	color(4);//暗红色
	printf("speed：");
	color(12);//亮红色
	printf("%d", tetris->speed);
}
/// <summary>
/// 判断方块是否可以移动，判断周围是否是墙壁或者有其他方块
/// </summary>
/// <param name=""></param>
int ifMove(struct Tetris* tetris) {
	if (a[tetris->x][tetris->y] != 0)//中心的方块上在方格纸上已经有方块了，此时下落的方块不可移动
	{
		return 0;
	}
	else
	{
		//符合条件 可以移动
		if (
			/*田字格:当田字图案要放置的4个方块的位置皆没有图案是则这个田字格图案可以移动*/
			(tetris->flag == 1 && (a[tetris->x][tetris->y - 1] == 0 &&
				a[tetris->x + 2][tetris->y - 1] == 0 && a[tetris->x + 2][tetris->y] == 0)) ||
			/*直线方块：判断其余三个位置的是否有图案*/
			(tetris->flag == 2 && (a[tetris->x - 2][tetris->y] == 0 &&
				a[tetris->x + 2][tetris->y] == 0 && a[tetris->x + 4][tetris->y] == 0)) ||
			/*直线方块 竖着的*/
			(tetris->flag == 3 && (
				a[tetris->x][tetris->y - 1] == 0 &&
				a[tetris->x][tetris->y - 2] == 0 &&
				a[tetris->x][tetris->y + 1] == 0)) ||
			/*T字方块 竖着的*/
			(tetris->flag == 4 && (
				a[tetris->x - 2][tetris->y] == 0 &&
				a[tetris->x + 2][tetris->y] == 0 &&
				a[tetris->x][tetris->y + 1] == 0)) ||
			/*T字方块 顺时针90度*/
			(tetris->flag == 5 && (
				a[tetris->x][tetris->y - 1] == 0 &&
				a[tetris->x][tetris->y + 1] == 0 &&
				a[tetris->x - 2][tetris->y] == 0)) ||
			/*T字方块 顺时针180度*/
			(tetris->flag == 6 && (
				a[tetris->x][tetris->y - 1] == 0 &&
				a[tetris->x - 2][tetris->y] == 0 &&
				a[tetris->x + 2][tetris->y] == 0)) ||
			/*T字方块 顺时针270度*/
			(tetris->flag == 7 && (
				a[tetris->x][tetris->y - 1] == 0 &&
				a[tetris->x][tetris->y + 1] == 0 &&
				a[tetris->x + 2][tetris->y] == 0)) ||
			/*z字方块*/
			(tetris->flag == 8 && (
				a[tetris->x][tetris->y + 1] == 0 &&
				a[tetris->x - 2][tetris->y] == 0 &&
				a[tetris->x + 2][tetris->y + 1] == 0)) ||
			/*z字方块 顺时针*/
			(tetris->flag == 9 && (
				a[tetris->x][tetris->y - 1] == 0 &&
				a[tetris->x - 2][tetris->y] == 0 &&
				a[tetris->x - 2][tetris->y + 1] == 0)) ||
			/*反z字方块*/
			(tetris->flag == 10 && (
				a[tetris->x][tetris->y - 1] == 0 &&
				a[tetris->x - 2][tetris->y - 1] == 0 &&
				a[tetris->x + 2][tetris->y] == 0)) ||
			/*反z字方块 顺时针*/
			(tetris->flag == 11 && (
				a[tetris->x][tetris->y + 1] == 0 &&
				a[tetris->x - 2][tetris->y - 1] == 0 &&
				a[tetris->x - 2][tetris->y] == 0)) ||
			/*7字形方块*/
			(tetris->flag == 12 && (
				a[tetris->x][tetris->y - 1] == 0 &&
				a[tetris->x][tetris->y + 1] == 0 &&
				a[tetris->x - 2][tetris->y - 1] == 0)) ||
			/*7字形方块 顺时针90度*/
			(tetris->flag == 13 && (
				a[tetris->x - 2][tetris->y] == 0 &&
				a[tetris->x + 2][tetris->y - 1] == 0 &&
				a[tetris->x + 2][tetris->y] == 0)) ||
			/*7字形方块 顺时针180度*/
			(tetris->flag == 14 && (
				a[tetris->x][tetris->y - 1] == 0 &&
				a[tetris->x][tetris->y + 1] == 0 &&
				a[tetris->x + 2][tetris->y + 1] == 0)) ||
			/*7字形方块 顺时针270度*/
			(tetris->flag == 15 && (
				a[tetris->x - 2][tetris->y] == 0 &&
				a[tetris->x - 2][tetris->y + 1] == 0 &&
				a[tetris->x + 2][tetris->y] == 0)) ||
			/*反7字方块*/
			(tetris->flag == 16 && (
				a[tetris->x][tetris->y + 1] == 0 &&
				a[tetris->x][tetris->y - 1] == 0 &&
				a[tetris->x + 2][tetris->y - 1] == 0)) ||
			/*反7字方块 顺时针90度*/
			(tetris->flag == 17 && (
				a[tetris->x - 2][tetris->y] == 0 &&
				a[tetris->x + 2][tetris->y + 1] == 0 &&
				a[tetris->x + 2][tetris->y] == 0)) ||
			/*反7字方块 顺时针180度*/
			(tetris->flag == 18 && (
				a[tetris->x][tetris->y - 1] == 0 &&
				a[tetris->x][tetris->y + 1] == 0 &&
				a[tetris->x - 2][tetris->y + 1] == 0)) ||
			/*反7字方块 顺时针270度*/
			(tetris->flag == 19 && (
				a[tetris->x - 2][tetris->y] == 0 &&
				a[tetris->x - 2][tetris->y - 1] == 0 &&
				a[tetris->x + 2][tetris->y] == 0))
			)
		{
			return 1;
		}
	}
	return 0;
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
