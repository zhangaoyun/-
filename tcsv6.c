#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define Height 50  // ��Ϸ����ߴ�
#define Width 103

void initGame(); 

void show();
void key();
void key0();

int moveDirection; // С���ƶ�λ�ã��������ҷֱ���1��2��3��4��ʾ
int food_x,food_y; // ʳ���λ��
int grass_x,grass_y; 
int map[Height][Width] = {0};

int point = 0;	//�Ƿ� 




int main()
{
	time_t start ,end ;
	int cost;
	time(&start);


	system("color 0B");
	initGame();  // ���ݳ�ʼ��	
	while (cost<=20) //  ��Ϸѭ��ִ��
	{
		show();  // ��ʾ����
		key0(); 
		key();  // ���û������йصĸ���
		time(&end);
		cost=difftime(end,start);
	}
	return 0;
}

void gotoxy(int x,int y)  //����ƶ���(x,y)λ��
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

void moveSnakeByDirection()
{
	int i,j;
	for (i=1;i<Height-1;i++)
		for (j=1;j<Width-1;j++)
			if (map[i][j]>0)
				map[i][j]++;

	int oldTail_i,oldTail_j,oldHead_i,oldHead_j;
	int max = 0;

	for (i=1;i<Height-1;i++)
		for (j=1;j<Width-1;j++)
			if (map[i][j]>0)
			{
				if (max<map[i][j])
				{
					max = map[i][j];
					oldTail_i = i;
					oldTail_j = j;
				}
				if (map[i][j]==2)
				{
					oldHead_i = i;
					oldHead_j = j;
				}
			}

	int newHead_i,newHead_j;

	if (moveDirection==1) // �����ƶ�
	{
		newHead_i = oldHead_i-1;
		newHead_j = oldHead_j;
	}
	if (moveDirection==2) // �����ƶ�
	{
		newHead_i = oldHead_i+1;
		newHead_j = oldHead_j;
	}
	if (moveDirection==3) // �����ƶ�
	{
		newHead_i = oldHead_i;
		newHead_j = oldHead_j-1;
	}
	if (moveDirection==4) // �����ƶ�
	{
		newHead_i = oldHead_i;
		newHead_j = oldHead_j+1;
	}

	// ����ͷ����Ե�ʳ��
	if (map[newHead_i][newHead_j]==-2)
	{
		map[food_x][food_y] = 0;
		// ����һ���µ�ʳ��
		food_x = rand()%(Height-5) + 2;
		food_y = rand()%(Width-5) + 2;
		map[food_x][food_y] = -2;
		
		point++; 

		// ԭ���ľ���β���ţ������Զ�+1
	}
	else // ����ԭ���ľ���β���������ֳ��Ȳ���
		map[oldTail_i][oldTail_j] = 0;
		
	// ����ͷ����Ե����� 
	if (map[newHead_i][newHead_j]==-3)
	{
		map[grass_x][grass_y] = 0;
		// ����һ���µĶ��� 
		grass_x = rand()%(Height-5) + 2;
		grass_y = rand()%(Width-5) + 2;
		map[grass_x][grass_y] = -3;
		
		point--;

		// ԭ���ľ���ͷ�����������Զ�-1
		map[oldHead_i][oldHead_j] = 0;
	}


	// �Ƿ�С�ߺ�����ײ�����ߺͱ߿�ײ����Ϸ���� 
	if (map[newHead_i][newHead_j]>0 || map[newHead_i][newHead_j]==-1)
	{
		printf("��Ϸ����\n");
		Sleep(2000);
		system("pause");
		exit(0);
	}
	
/*	time(&end);
	cost=difftime(end,start);
	if (cost >=20)
	{	
		printf("��Ϸ����\n");
		Sleep(2000);
		system("pause");
		exit(0);
	}*/
	else
		map[newHead_i][newHead_j] = 1;
}

void initGame() // ��Ϸ��ʼ��
{
	int i,j;
	
	// ��ʼ���߿�
	for (i=0;i<Height;i++)
	{
		map[i][0] = -1;
		map[i][Width-1] = -1;
	}
	for (j=0;j<Width;j++)
	{
		map[0][j] = -1;
		map[Height-1][j] = -1;
	}

	
	// ��ʼ����ͷλ��
	map[Height/2][Width/2] = 1;
	// ��ʼ��������ͼ��Ԫ��ֵ�ֱ�Ϊ2,3,4,5....
	
	
	for (i=1;i<=4;i++)
		map[Height/2][Width/2-i] = i+1;

	// ��ʼС�������ƶ�
	moveDirection = 4;
	
	food_x = rand()%(Height-5) + 2;
	food_y = rand()%(Width-5) + 2;
	
	map[food_x][food_y] = -2;
	
	grass_x = rand()%(Height-5) + 2;
	grass_y = rand()%(Width-5) + 2;
	
	map[grass_x][grass_y] = -3;
}

void show()  // ��ʾ����
{
	gotoxy(0,0);  // ����ƶ���ԭ��λ�ã������ػ�����
	int i,j;
	for (i=0;i<Height;i++)
	{
		for (j=0;j<Width;j++)
		{
			if (map[i][j]==0)
				printf(" ");   //   ��ӡ�ո�
			else if (map[i][j]==-1)
				printf("#");   //   ��ӡ�߿�#
			else if (map[i][j]==1)
				printf("@");   //   ��ӡ��ͷ@
			else if (map[i][j]>1)
				printf("*");   //   ��ӡ����*
			else if (map[i][j]==-2)
				printf("$");   //   ��ӡʳ��$
			else if (map[i][j]==-3) 
				printf("!");   //   ��ӡ���ݣ� 
		}
		printf("\n");
	}
	printf("��ķ�����%d",point*10); 
	Sleep(60);
}	

void key()  // ���û������йصĸ���
{
	char input;
	if(kbhit())  // �ж��Ƿ�������
	{
		input = getch();  // �����û��Ĳ�ͬ�������ƶ�����������س�
		if (input == 'a'||input == 'A') 
		{
			moveDirection = 3;   // λ������
			moveSnakeByDirection();
		}
		else if (input == 'd'||input == 'D')
		{
			moveDirection = 4;  // λ������
			moveSnakeByDirection();
		}
		else if (input == 'w'||input == 'W')
		{
			moveDirection = 1;  // λ������
			moveSnakeByDirection();
		}
		else if (input == 's'||input == 'S')
		{
			moveDirection = 2;   // λ������
			moveSnakeByDirection();
		}
	}
}

void key0()  // ���û������޹صĸ���
{
	moveSnakeByDirection();
}

