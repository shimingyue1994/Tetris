// ����һЩ����
/// <summary>
/// ������һЩ�����ƶ����Ƶĺ���
/// </summary>
int color(int c);
void gotoxy(int x, int y);//����ƶ���ָ��λ��
void DrwaGameframe();//���Ʊ߿�
void Flag(struct Tetris*);//��������ı�־
void MakeTetris(struct Tetris*);//��������ṹi
void PrintTetris(struct Tetris*);//���ݷ���ӿڽ������ӡ������̨
void CleanTetris(struct Tetris*);//�������
int ifMove(struct Tetris*);//�жϷ����Ƿ����ƶ�
void Del_Fullline(struct Tetris*);//�ж����Ƿ���������ɾ�����еķ���
/// <summary>
/// ������һЩ�򵥵Ĺ��ܺ���
/// </summary>
void Gameplay();//��ʼ��Ϸ
void regulation();//����
void explation();//��������
void welcome();//��ӭ����
void Replay(struct Tetris* tetris);//���¿�ʼ
void title();//����
void flower();//
void close();//�ر�