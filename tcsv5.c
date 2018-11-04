// 0Ϊ�ո�0��-1Ϊ�߿�#��-2Ϊʳ��!��-3Ϊ���ݣ�1Ϊ��ͷ@������1������Ϊ����*
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define Height 50  // ��Ϸ����ߴ�
#define Width 103

void initGame(); // ��ʼ������ 

void show();// ���溯�� 
void key();// �������� 
void key0();// �ް������� 

int moveDirection; // ���ƶ�λ�ã��������ҷֱ���1��2��3��4��ʾ
int food_x,food_y; // ʳ���λ��
int grass0_x,grass0_y; // ���ݵ�λ�� 
int grass1_x,grass1_y; // ���ݵ�λ�� 
int grass2_x,grass2_y; // ���ݵ�λ�� 
int map[Height][Width] = {0};// �ȳ�ʼ����ͼΪ�հ� 

int point = 0;	//�Ʒ� 

int main()
{
	system("color 0B");// ������Ϸǰ��Ϊ��ɫ������Ϊ��ɫ 
	initGame();  // ���ݳ�ʼ��	
	while (1) //  ��Ϸѭ��ִ��
	{
		show();  // ��ʾ����
		key0();  // �ް���ʱ 
		key();  // ����ʱ 
	}
	return 0;
}

void gotoxy(int x,int y)  // ��꺯��������ƶ���(x,y)λ��
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

void moveSnakeByDirection()// �߸��ݷ����ƶ� 
{
	int i,j;
	for (i=1;i<Height-1;i++)
		for (j=1;j<Width-1;j++)
			if (map[i][j]>0)
				map[i][j]++;// ����0�Ķ�Ϊ�ߵ�һ���֣�����1 

	int oldTail_i,oldTail_j,oldHead_i,oldHead_j;
	int max = 0;// ����һ��������� 

	for (i=1;i<Height-1;i++)
		for (j=1;j<Width-1;j++)
			if (map[i][j]>0)
			{
				if (max<map[i][j])
				{
					max = map[i][j];
					oldTail_i = i;
					oldTail_j = j;
				}// �������飬�ҳ�������֣��˼�Ϊ����β 
				if (map[i][j]==2)
				{
					oldHead_i = i;
					oldHead_j = j;
				}// ����ͷ��1����2 
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
		map[grass0_x][grass0_y] = 0;
		// ����һ���µĶ��� 
		grass0_x = rand()%(Height-5) + 2;
		grass0_y = rand()%(Width-5) + 2;
		map[grass0_x][grass0_y] = -3;
		
		point--;

		// ԭ���ľ���ͷ�����������Զ�-1
		map[oldHead_i][oldHead_j] = 0;
	}
	
	if (map[newHead_i][newHead_j]==-3)
	{
		map[grass1_x][grass1_y] = 0;
		// ����һ���µĶ��� 
		grass1_x = rand()%(Height-5) + 2;
		grass1_y = rand()%(Width-5) + 2;
		map[grass1_x][grass1_y] = -3;
		
		point--;

		// ԭ���ľ���ͷ�����������Զ�-1
		map[oldHead_i][oldHead_j] = 0;
	}

	if (map[newHead_i][newHead_j]==-3)
	{
		map[grass2_x][grass2_y] = 0;
		// ����һ���µĶ��� 
		grass2_x = rand()%(Height-5) + 2;
		grass2_y = rand()%(Width-5) + 2;
		map[grass2_x][grass2_y] = -3;
		
		point--;

		// ԭ���ľ���ͷ�����������Զ�-1
		map[oldHead_i][oldHead_j] = 0;
	}


	// �ж����Ƿ������ײ�����ߺͱ߿�ײ����Ϸ���� 
	if (map[newHead_i][newHead_j]>0 || map[newHead_i][newHead_j]==-1)
	{
		printf("��Ϸ����\a\n");
		Sleep(2000);
		system("pause");
		exit(0);
	}
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
	// ��ʼ������.	
	for (i=1;i<=4;i++)
		map[Height/2][Width/2-i] = i+1;

	// ��ʼ�������ƶ�
	moveDirection = 4;
	// 1 �� 2 �� 3 �� 4 �� 
	
	// ���������
	food_x = rand()%(Height-5) + 2;
	food_y = rand()%(Width-5) + 2;
	
	map[food_x][food_y] = -2;
	
	grass0_x = rand()%(Height-5) + 2;
	grass0_y = rand()%(Width-5) + 2;
	
	map[grass0_x][grass0_y] = -3;
}

void show()  // ��ʾ����
{
	gotoxy(0,0);  // ����ƶ���ԭ��λ�ã������������´�ӡ 
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

	printf("��ķ�����%d\n",point*10); //��ӡ���� 
	Sleep(60);
}	

void key()  // ����ʱ
{
	char input;
	if(kbhit())  // �ж��Ƿ�������
	{
		input = getch();  // �����������ƶ�
		if (input == 'a') 
		{
			moveDirection = 3;   // ����
			moveSnakeByDirection();
		}
		else if (input == 'd')
		{
			moveDirection = 4;  // ����
			moveSnakeByDirection();
		}
		else if (input == 'w')
		{
			moveDirection = 1;  // ����
			moveSnakeByDirection();
		}
		else if (input == 's')
		{
			moveDirection = 2;   // ����
			moveSnakeByDirection();
		}
	}
}

void key0()  // �ް���ʱ�ƶ� 
{
	moveSnakeByDirection();
}



