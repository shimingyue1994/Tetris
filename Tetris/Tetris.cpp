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


int i, j, Temp, Temp1, Temp2;//temp,temp1,temp2用于记住和转换方块变量的值
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

/**
 * 绘制字符花
 */
void flower()
{
	gotoxy(66, 11);   	//确定屏幕上要输出的位置
	color(12);			//设置颜色
	printf("(_)");  		//红花上边花瓣

	gotoxy(64, 12);
	printf("(_)");      //红花左边花瓣

	gotoxy(68, 12);
	printf("(_)");      //红花右边花瓣

	gotoxy(66, 13);
	printf("(_)");      //红花下边花瓣

	gotoxy(67, 12);      //红花花蕊
	color(6);
	printf("@");

	gotoxy(72, 10);
	color(13);
	printf("(_)");      //粉花左边花瓣

	gotoxy(76, 10);
	printf("(_)");      //粉花右边花瓣

	gotoxy(74, 9);
	printf("(_)");      //粉花上边花瓣

	gotoxy(74, 11);
	printf("(_)");      //粉花下边花瓣

	gotoxy(75, 10);
	color(6);
	printf("@");        //粉花花蕊

	gotoxy(71, 12);
	printf("|");      	//两朵花之间的连接

	gotoxy(72, 11);
	printf("/");      	//两朵花之间的连接

	gotoxy(70, 13);
	printf("\\|");     //注意、\为转义字符。想要输入\，必须在前面需要转义

	gotoxy(70, 14);
	printf("`|/");

	gotoxy(70, 15);
	printf("\\|");

	gotoxy(71, 16);
	printf("| /");

	gotoxy(71, 17);
	printf("|");

	gotoxy(67, 17);
	color(10);
	printf("\\\\\\\\");      //草地
	gotoxy(73, 17);
	printf("//");

	gotoxy(67, 18);
	color(2);
	printf("^^^^^^^^");

	gotoxy(65, 19);
	color(5);
	printf("明 日  科 技");	//公司名称

	gotoxy(68, 20);
	printf("周小美");			//开发者的名字，读者练习时，可以换成自己的名字
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
		DrwaGameframe(); //绘制窗体
		Gameplay();//开始游戏
		break;
	case 2: //按键说明
		explation();
		break;
	case 3://规则
		regulation();
		break;
	case 4://退出
		close();
		break;
	default:
		break;
	}
}
void close() {
	exit(0);
}
/// <summary>
/// 游戏规则
/// </summary>
void regulation() {
	int i, j = 1;
	system("cls");
	color(13);
	gotoxy(34, 3);
	printf("游戏规则");
	color(2);
	for (i = 6; i <= 18; i++)   //输出上下边框===
	{
		for (j = 12; j <= 70; j++)  //输出左右边框||
		{
			gotoxy(j, i);
			if (i == 6 || i == 18) printf("=");
			else if (j == 12 || j == 69) printf("||");
		}
	}
	color(12);
	gotoxy(16, 7);
	printf("tip1: 不同形状的小方块从屏幕上方落下，玩家通过调整");
	gotoxy(22, 9);
	printf("方块的位置和方向，使他们在屏幕底部拼出完整的");
	gotoxy(22, 11);
	printf("一条或几条");
	color(14);
	gotoxy(16, 13);
	printf("tip2: 每消除一行，积分增加100");
	color(11);
	gotoxy(16, 15);
	printf("tip3: 每累计1000分，会提升一个等级");
	color(10);
	gotoxy(16, 17);
	printf("tip4: 提升等级会使方块下落速度加快，游戏难度加大");
	_getch();                //按任意键返回主界面
	system("cls");
	welcome();

}

/**
* 按键说明
*/
void explation()
{
	int i, j = 1;
	system("cls");
	color(13);
	gotoxy(32, 3);
	printf("按键说明");
	color(2);
	for (i = 6; i <= 16; i++)   //输出上下边框===
	{
		for (j = 15; j <= 60; j++)  //输出左右边框||
		{
			gotoxy(j, i);
			if (i == 6 || i == 16) printf("=");
			else if (j == 15 || j == 59) printf("||");
		}
	}
	color(3);
	gotoxy(18, 7);
	printf("tip1: 玩家可以通过 ← →方向键来移动方块");
	color(10);
	gotoxy(18, 9);
	printf("tip2: 通过 ↑使方块旋转");
	color(14);
	gotoxy(18, 11);
	printf("tip3: 通过 ↓加速方块下落");
	color(11);
	gotoxy(18, 13);
	printf("tip4: 按空格键暂停游戏，再按空格键继续");
	color(4);
	gotoxy(18, 15);
	printf("tip5: 按ESC退出游戏");
	_getch();                //按任意键返回主界面
	system("cls");
	welcome();
}

/*绘制主窗体，按键说明  方块的包裹区域*/
void DrwaGameframe() {
	gotoxy(FrameX + Frame_width - 5, FrameY - 2);   				//设置游戏名称的显示位置
	color(11);								//将字体颜色设置为亮蓝色
	printf("趣味俄罗斯方块");						//打印游戏名称
	gotoxy(FrameX + 2 * Frame_width + 3, FrameY + 7); 				//设置上边框的显示位置
	color(2);								//将字体颜色设置为深绿色
	printf("**********");							//打印下一个出现方块的上边框
	gotoxy(FrameX + 2 * Frame_width + 13, FrameY + 7);
	color(3);								//将字体颜色设置为深蓝绿色
	printf("下一出现方块：");
	gotoxy(FrameX + 2 * Frame_width + 3, FrameY + 13);
	color(2);
	printf("**********");							//打印下一个出现方块的下边框
	gotoxy(FrameX + 2 * Frame_width + 3, FrameY + 17);
	color(14);								//将字体颜色设置为黄色
	printf("↑键：旋转");
	gotoxy(FrameX + 2 * Frame_width + 3, FrameY + 19);
	printf("空格：暂停游戏");
	gotoxy(FrameX + 2 * Frame_width + 3, FrameY + 15);
	printf("Esc ：退出游戏");
	gotoxy(FrameX, FrameY);
	color(12);
	printf("╔");									//打印框角
	gotoxy(FrameX + 2 * Frame_width - 2, FrameY);
	printf("╗");
	gotoxy(FrameX, FrameY + Frame_height);
	printf("╚");
	gotoxy(FrameX + 2 * Frame_width - 2, FrameY + Frame_height);
	printf("╝");

	a[FrameX][FrameY + Frame_height] = 2;//边界标记 左下角: 向这个数组里放个标记，用来判断方块是否出界，如果数组中元素等于“2”就是出界了
	a[FrameX + 2 * Frame_width - 2][FrameY + Frame_height] = 2;//右下角

	for (i = 2; i < 2 * Frame_width - 2; i += 2)
	{
		gotoxy(FrameX + i, FrameY);
		printf("═");         						//打印上横框
	}
	for (i = 2; i < 2 * Frame_width - 2; i += 2)
	{
		gotoxy(FrameX + i, FrameY + Frame_height);
		printf("═");         						//打印下横框
		a[FrameX + i][FrameY + Frame_height] = 2;    	//标记下横框为游戏边框，防止方块出界
	}
	for (i = 1; i < Frame_height; i++)
	{
		gotoxy(FrameX, FrameY + i);
		printf("║");        	 					//打印左竖框
		a[FrameX][FrameY + i] = 2;       			//标记左竖框为游戏边框，防止方块出界
	}
	for (i = 1; i < Frame_height; i++)
	{
		gotoxy(FrameX + 2 * Frame_width - 2, FrameY + i);
		printf("║");         						 //打印右竖框
		a[FrameX + 2 * Frame_width - 2][FrameY + i] = 2;   //标记右竖框为游戏边框，防止方块出界	
	}
}

/// <summary>
///根据传进来的方块结构绘制方块,主要定义方块位置
/// </summary>
/// <param name=""></param>
/**
 * 制作俄罗斯方块
 */
void MakeTetris(struct Tetris* tetris)
{
	a[tetris->x][tetris->y] = b[0];    	//初始化中心方块位置的图形状态,就是第一个“■”的位置，然后根据它绘制其他三个
	switch (tetris->flag)      				//共7大类，19种类型
	{
	case 1:         /*田字方块 ■■
								■■  */
	{
		color(10);
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x + 2][tetris->y - 1] = b[2];
		a[tetris->x + 2][tetris->y] = b[3];
		break;
	}
	case 2:         /*直线方块 ■■■■*/
	{
		color(13);
		a[tetris->x - 2][tetris->y] = b[1];
		a[tetris->x + 2][tetris->y] = b[2];
		a[tetris->x + 4][tetris->y] = b[3];
		break;
	}
	case 3:         /*直线方块    ■
								 ■
								 ■
								 ■  */
	{
		color(13);
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x][tetris->y - 2] = b[2];
		a[tetris->x][tetris->y + 1] = b[3];
		break;
	}
	case 4:         /*T字方块 ■■■
							   ■  */
	{
		color(11);
		a[tetris->x - 2][tetris->y] = b[1];
		a[tetris->x + 2][tetris->y] = b[2];
		a[tetris->x][tetris->y + 1] = b[3];
		break;
	}
	case 5:         /* 顺时针90°T字方块   ■
										 ■■
										   ■*/
	{
		color(11);
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x][tetris->y + 1] = b[2];
		a[tetris->x - 2][tetris->y] = b[3];
		break;
	}
	case 6:         /* 顺时针180°T字方块   ■
										  ■■■*/
	{
		color(11);
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x - 2][tetris->y] = b[2];
		a[tetris->x + 2][tetris->y] = b[3];
		break;
	}
	case 7:         /* 顺时针270°T字方块 ■
										  ■■
										  ■  */
	{
		color(11);
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x][tetris->y + 1] = b[2];
		a[tetris->x + 2][tetris->y] = b[3];
		break;
	}
	case 8:         /* Z字方块  ■■
								   ■■*/
	{
		color(14);
		a[tetris->x][tetris->y + 1] = b[1];
		a[tetris->x - 2][tetris->y] = b[2];
		a[tetris->x + 2][tetris->y + 1] = b[3];
		break;
	}
	case 9:         /* 顺时针Z字方块   ■
									  ■■
									  ■  */
	{
		color(14);
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x - 2][tetris->y] = b[2];
		a[tetris->x - 2][tetris->y + 1] = b[3];
		break;
	}
	case 10:        /* 反转Z字方块    ■■
									 ■■  */
	{
		color(14);
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x - 2][tetris->y - 1] = b[2];
		a[tetris->x + 2][tetris->y] = b[3];
		break;
	}
	case 11:        /* 顺时针Z字方块 ■
									  ■■
										■  */
	{
		color(14);
		a[tetris->x][tetris->y + 1] = b[1];
		a[tetris->x - 2][tetris->y - 1] = b[2];
		a[tetris->x - 2][tetris->y] = b[3];
		break;
	}
	case 12:        /* 7字方块    ■■
									 ■
									 ■ */
	{
		color(12);
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x][tetris->y + 1] = b[2];
		a[tetris->x - 2][tetris->y - 1] = b[3];
		break;
	}
	case 13:        /* 顺时针90°7字方块      ■
										  ■■■  */
	{
		color(12);
		a[tetris->x - 2][tetris->y] = b[1];
		a[tetris->x + 2][tetris->y - 1] = b[2];
		a[tetris->x + 2][tetris->y] = b[3];
		break;
	}
	case 14:        /* 顺时针180°7字方块   ■
											■
											■■  */
	{
		color(12);
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x][tetris->y + 1] = b[2];
		a[tetris->x + 2][tetris->y + 1] = b[3];
		break;
	}
	case 15:        /* 顺时针270°7字方块   ■■■
											■    */
	{
		color(12);
		a[tetris->x - 2][tetris->y] = b[1];
		a[tetris->x - 2][tetris->y + 1] = b[2];
		a[tetris->x + 2][tetris->y] = b[3];
		break;
	}
	case 16:        /* 反转7字方块   ■■
									  ■
										 ■    */
	{
		color(12);
		a[tetris->x][tetris->y + 1] = b[1];
		a[tetris->x][tetris->y - 1] = b[2];
		a[tetris->x + 2][tetris->y - 1] = b[3];
		break;
	}
	case 17:        /* 顺时针转90°7字方块   ■■■
												 ■*/
	{
		color(12);
		a[tetris->x - 2][tetris->y] = b[1];
		a[tetris->x + 2][tetris->y + 1] = b[2];
		a[tetris->x + 2][tetris->y] = b[3];
		break;
	}
	case 18:        /* 顺时针转180°7字方块  ■
											  ■
											■■    */
	{
		color(12);
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x][tetris->y + 1] = b[2];
		a[tetris->x - 2][tetris->y + 1] = b[3];
		break;
	}
	case 19:        /* 顺指针转270°7字方块  ■
											 ■■■*/
	{
		color(12);
		a[tetris->x - 2][tetris->y] = b[1];
		a[tetris->x - 2][tetris->y - 1] = b[2];
		a[tetris->x + 2][tetris->y] = b[3];
		break;
	}
	}
}

/// <summary>
/// 将方块打印在屏幕上
/// </summary>
/// <param name="tetris"></param>

void PrintTetris(struct Tetris* tetris)
{
	for (i = 0; i < 4; i++)					//数组b[4]中有4个元素，循环这4个元素，让每个元素的值都为
	{
		b[i] = 1;         				//数组b[4]的每个元素的值都为1
	}
	MakeTetris(tetris);      			//制作游戏窗口
	for (i = tetris->x - 2; i <= tetris->x + 4; i += 2)
	{
		for (j = tetris->y - 2; j <= tetris->y + 1; j++)	//循环方块所有可能出现的位置
		{
			if (a[i][j] == 1 && j > FrameY) 		//如果这个位置上有方块
			{
				gotoxy(i, j);
				printf("■");     					//打印边框内的方块
			}
		}
	}
	//打印菜单信息
	gotoxy(FrameX + 2 * Frame_width + 3, FrameY + 1); 	//设置打印位置
	color(4);
	printf("level : ");
	color(12);
	printf(" %d", tetris->level); 					//输出等级
	gotoxy(FrameX + 2 * Frame_width + 3, FrameY + 3);
	color(4);
	printf("score : ");
	color(12);
	printf(" %d", tetris->score); 					//输出分数
	gotoxy(FrameX + 2 * Frame_width + 3, FrameY + 5);
	color(4);
	printf("speed : ");
	color(12);
	printf(" %dms", tetris->speed); 			//输出速度
}
/// <summary>
/// 判断方块是否可以移动，判断周围是否是墙壁或者有其他方块
/// </summary>
/// <param name=""></param>
int ifMove(struct Tetris* tetris) {
	//中心的方块上在方格纸上已经有方块了，此时下落的方块不可移动
	if (a[tetris->x][tetris->y] != 0)
	{
		return 0;
	}
	else
	{
		//符合条件 可以移动
		if (
			/*田字格:当田字图案要放置的4个方块的位置皆没有图案是则这个田字格图案可以移动*/
			(tetris->flag == 1 && (
				a[tetris->x][tetris->y - 1] == 0 &&
				a[tetris->x + 2][tetris->y - 1] == 0 &&
				a[tetris->x + 2][tetris->y] == 0)) ||
			/*直线方块：判断其余三个位置的是否有图案*/
			(tetris->flag == 2 && (
				a[tetris->x - 2][tetris->y] == 0 &&
				a[tetris->x + 2][tetris->y] == 0 &&
				a[tetris->x + 4][tetris->y] == 0)) ||
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
/// <summary>
/// 清除方块的痕迹
/// </summary>
/// <param name="tetris"></param>
void CleanTetris(struct Tetris* tetris) {
	for (i = 0; i < 4; i++)
	{
		b[i] = 0;//0表示没有方块
	}
	MakeTetris(tetris);//重置数组b中方块元素的值为0，以便下面的代码执行清除操作
	//循环方块可能出现的所有位置并绘制出来，MakeTetris可以看出方块的范围是 x-2 <= x <= x+4    y-2 <= y <= y+1
	for (i = tetris->x - 2; i <= tetris->x + 4; i += 2) {
		for (j = tetris->y - 2; j <= tetris->y + 1; j++) {
			if (a[i][j] == 0 && j > FrameY)
			{
				gotoxy(i, j);
				printf("  ");//2个空格相当于一个字符
			}
		}
	}
}

/// <summary>
/// 判断方块是否满行并删除满行的方块
/// </summary>
/// <param name="tetris"></param>
void Del_Fullline(struct Tetris* tetris) {
	int k, del_rows = 0;
	for (j = FrameY + Frame_height - 1; j >= FrameY + 1; j--)//纵（y）轴，从下往上
	{
		k = 0;
		//横轴 从左往右 宽度 布局2 是因为在横轴上 方块字符占2个字符
		for (i = FrameX + 2; i < FrameX + 2 * Frame_height - 2; i += 2)
		{
			if (a[i][j] == 1)//这一行有方块
			{
				k++;
				if (k == Frame_width - 2)//判断这一行是否填满
				{
					// 如果满行 开始删除这一行
					for (k = FrameX + 2; k < FrameX + 2 * Frame_height - 2; k += 2)
					{
						a[k][j] = 0;
						gotoxy(k, j);
						printf("  ");
					}

					//删除的这一行的上方有方块则执行方块下移操作
					for (k = j - 1; k > FrameY; k--)//y轴
					{
						for (i = FrameX + 2; i < FrameX + 2 * Frame_height - 2; i += 2)//x轴
						{
							if (a[i][k] == 1)
							{
								//删除方块
								a[i][k] = 0;
								gotoxy(i, k);
								printf("  ");
								//在下方重新绘制一个
								a[i][k + 1] = 1;
								gotoxy(i, k + 1);
								printf("■");
							}
						}
					}
					j++;//方块下移动后，重新判断删除的行是否满行
					del_rows++;//记录删除的行数，统计分数
				}
			}
		}
	}
	//打印分数
	tetris->score += 100 * del_rows;//每删除一行 加100
	if (del_rows > 0 && (tetris->score % 1000 == 0 || tetris->score / 1000 > tetris->level - 1))
	{//如果得分1000 速度加快20ms并升一级
		tetris->speed -= 20;
		tetris->level++;
	}
}
/// <summary>
/// 随机产生方块的序号
/// </summary>
/// <param name="tetris"></param>
void Flag(struct Tetris* tetris) {
	tetris->number++;//记住产生方块的个数
	srand(time(NULL));//初始化随机数
	//只有第一个方块才随机产生flag,后面来的都使用next 来赋值，然后再产生新的next,已达到和预览窗口相同
	if (tetris->number == 1) 
	{
		tetris->flag = rand() % 19 + 1;
	}
	tetris->next = rand() % 19 + 1;//记住下一个方块的序号
}
/// <summary>
/// 重新开始
/// </summary>
/// <param name="tetris"></param>
void Replay(struct Tetris*)
{
	system("cls");                  	//清屏
	memset(a, 0, 6400 * sizeof(int));       //初始化BOX数组，否则不会正常显示方块，导致游戏直接结束
	DrwaGameframe();       	//制作游戏窗口
	Gameplay(); 			//开始游戏
}
/**
 * 开始游戏
 */
void Gameplay()
{
	int n;
	struct Tetris t, * tetris = &t;       					//定义结构体的指针并指向结构体变量
	char ch;         									//定义接收键盘输入的变量
	tetris->number = 0;      								//初始化俄罗斯方块数为0个
	tetris->speed = 300;      							//初始移动速度为300ms
	tetris->score = 0;      								//初始游戏的分数为0分
	tetris->level = 1;      								//初始游戏为第1关
	while (1)											//循环产生方块，直至游戏结束
	{
		Flag(tetris);     								//得到产生俄罗斯方块类型的序号
		Temp = tetris->flag;     							//临时变量：记住当前俄罗斯方块序号，以便后面的还原
		tetris->x = FrameX + 2 * Frame_width + 6;				//获得预览界面方块的x坐标，预览界面就是右下角那个（*********下一个方块）的位置
		tetris->y = FrameY + 10;                            //获得预览界面方块的y坐标
		tetris->flag = tetris->next;                    //获得下一个俄罗斯方块的序号，现将下一个要显示的方块打印在预览窗口
		PrintTetris(tetris);                           //调用打印俄罗斯方块方法 打印预览方块
		//开始打印此时下落的方块
		tetris->x = FrameX + Frame_width;  					//获得游戏窗口中心方块x坐标
		tetris->y = FrameY - 1;     						//获得游戏窗口中心方块y坐标
		tetris->flag = Temp;     							//取出当前的俄罗斯方块序号 将序号还原
		///方块下落的循环体
		while (1)  										//控制方块方向，直至方块不再下移
		{
		label:PrintTetris(tetris);					//打印俄罗斯方块
			Sleep(tetris->speed);   					//延缓时间
			CleanTetris(tetris);  						//清除痕迹，后面会在新的位置重新绘制
			Temp1 = tetris->x;    						//记住中心方块横坐标的值
			Temp2 = tetris->flag;    						//记住当前俄罗斯方块序号
			if (_kbhit())       				  	 		//判断是否有键盘输入，有则用ch↓接收
			{
				ch = _getch();
				if (ch == 75)     							//按 ←键则向左动，中心横坐标减2
				{
					tetris->x -= 2;
				}
				if (ch == 77)     							//按 →键则向右动，中心横坐标加2
				{
					tetris->x += 2;
				}
				if (ch == 80)     							//按 ↓键则加速下落
				{
					if (ifMove(tetris) != 0)//可以向下移动
					{
						tetris->y += 2;
					}
					if (ifMove(tetris) == 0)//不可以向下移动了
					{
						tetris->y = FrameY + Frame_height - 2;
					}
				}
				if (ch == 72)     						//按 ↑键则变体,即当前方块顺时针转90度
				{
					if (tetris->flag >= 2 && tetris->flag <= 3)
					{
						tetris->flag++;
						tetris->flag %= 2;
						tetris->flag += 2;
					}
					if (tetris->flag >= 4 && tetris->flag <= 7)
					{
						tetris->flag++;
						tetris->flag %= 4;
						tetris->flag += 4;
					}
					if (tetris->flag >= 8 && tetris->flag <= 11)
					{
						tetris->flag++;
						tetris->flag %= 4;
						tetris->flag += 8;
					}
					if (tetris->flag >= 12 && tetris->flag <= 15)
					{
						tetris->flag++;
						tetris->flag %= 4;
						tetris->flag += 12;
					}
					if (tetris->flag >= 16 && tetris->flag <= 19)
					{
						tetris->flag++;
						tetris->flag %= 4;
						tetris->flag += 16;
					}
				}
				if (ch == 32)     					//按空格键，暂停
				{
					PrintTetris(tetris);
					while (1)
					{
						if (_kbhit())   			//再按空格键，继续游戏
						{
							ch = _getch();
							if (ch == 32)
							{
								goto label;
							}
						}
					}
				}
				if (ch == 27) //esc 退出游戏，返回欢迎页，在这里重置变量
				{
					system("cls");
					memset(a, 0, 6400 * sizeof(int));       //初始化BOX数组
					welcome();
				}
				if (ifMove(tetris) == 0) 			//如果不可动，上面操作无效
				{
					tetris->x = Temp1;
					tetris->flag = Temp2;
				}
				else      						//如果可动，执行操作 又一次重新绘制
				{
					goto label;
				}
			}//按键逻辑 end

			//如果没有操作指令，方块自动向下移动
			tetris->y++;     					
			//如果向下移动且不可动，方块放在此处，并调用break 结束下落循环体,开始下一个方块的下落
			if (ifMove(tetris) == 0)  				
			{
				tetris->y--;
				PrintTetris(tetris);
				Del_Fullline(tetris);//判断满行，然后删除
				break;//结束下落的循环体
			}
		}//方块下落循环逻辑end
		//游戏结束条件：方块触到框顶位置
		for (i = tetris->y - 2; i < tetris->y + 2; i++)	
		{
			if (i == FrameY)
			{
				system("cls");
				gotoxy(29, 7);
				printf("   \n");
				color(12);
				printf("\t\t\t■■■■   ■     ■   ■■     \n");
				printf("\t\t\t■         ■■   ■   ■  ■   \n");
				printf("\t\t\t■■■     ■  ■ ■   ■   ■  \n");
				printf("\t\t\t■         ■   ■■   ■  ■   \n");
				printf("\t\t\t■■■■   ■     ■   ■■     \n");
				gotoxy(17, 18);
				color(14);
				printf("我要重新玩一局-------1");
				gotoxy(44, 18);
				printf("不玩了，退出吧-------2\n");
				gotoxy(32, 20);
				printf("选择【1/2】：");
				color(11);
				scanf_s("%d", &n);
				switch (n)
				{
				case 1:
					system("cls");
					//Replay(tetris);       	//重新开始游戏
					break;
				case 2:
					exit(0);
					break;
				}
			}
		}
		//清除下一个俄罗斯方块的图形(右边窗口),并将flag赋值为下一个方块的序号
		tetris->flag = tetris->next;  			
		tetris->x = FrameX + 2 * Frame_width + 6;
		tetris->y = FrameY + 10;
		CleanTetris(tetris);
	}
}
int main()
{
	//for (;;) 
	//{
	//	if (_kbhit()) 
	//	{
	//		//getch()获取键盘输入，并将ascii码的值返回,当没有键盘输入时，代码不会往后执行，读取到键盘输入，则继续往下执行
	//		char ch = _getch();
	//		printf("%c\n",ch);//输出按键
	//		printf("%d",ch);//输出按键对应的ascii码
	//	}
	//}

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
