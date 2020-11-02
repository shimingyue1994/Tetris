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