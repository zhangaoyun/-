#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define Height 50  // 游戏画面尺寸
#define Width 103

void initGame(); 

void show();
void key();
void key0();

int moveDirection; // 小蛇移动位置，上下左右分别用1，2，3，4表示
int food_x,food_y; // 食物的位置
int grass_x,grass_y; 
int map[Height][Width] = {0};

int point = 0;	//记分 




int main()
{
	time_t start ,end ;
	int cost;
	time(&start);


	system("color 0B");
	initGame();  // 数据初始化	
	while (cost<=20) //  游戏循环执行
	{
		show();  // 显示画面
		key0(); 
		key();  // 与用户输入有关的更新
		time(&end);
		cost=difftime(end,start);
	}
	return 0;
}

void gotoxy(int x,int y)  //光标移动到(x,y)位置
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

	if (moveDirection==1) // 向上移动
	{
		newHead_i = oldHead_i-1;
		newHead_j = oldHead_j;
	}
	if (moveDirection==2) // 向下移动
	{
		newHead_i = oldHead_i+1;
		newHead_j = oldHead_j;
	}
	if (moveDirection==3) // 向左移动
	{
		newHead_i = oldHead_i;
		newHead_j = oldHead_j-1;
	}
	if (moveDirection==4) // 向右移动
	{
		newHead_i = oldHead_i;
		newHead_j = oldHead_j+1;
	}

	// 新蛇头如果吃到食物
	if (map[newHead_i][newHead_j]==-2)
	{
		map[food_x][food_y] = 0;
		// 产生一个新的食物
		food_x = rand()%(Height-5) + 2;
		food_y = rand()%(Width-5) + 2;
		map[food_x][food_y] = -2;
		
		point++; 

		// 原来的旧蛇尾留着，长度自动+1
	}
	else // 否则，原来的旧蛇尾减掉，保持长度不变
		map[oldTail_i][oldTail_j] = 0;
		
	// 新蛇头如果吃到毒草 
	if (map[newHead_i][newHead_j]==-3)
	{
		map[grass_x][grass_y] = 0;
		// 产生一个新的毒草 
		grass_x = rand()%(Height-5) + 2;
		grass_y = rand()%(Width-5) + 2;
		map[grass_x][grass_y] = -3;
		
		point--;

		// 原来的旧蛇头减掉，长度自动-1
		map[oldHead_i][oldHead_j] = 0;
	}


	// 是否小蛇和自身撞，或者和边框撞，游戏结束 
	if (map[newHead_i][newHead_j]>0 || map[newHead_i][newHead_j]==-1)
	{
		printf("游戏结束\n");
		Sleep(2000);
		system("pause");
		exit(0);
	}
	
/*	time(&end);
	cost=difftime(end,start);
	if (cost >=20)
	{	
		printf("游戏结束\n");
		Sleep(2000);
		system("pause");
		exit(0);
	}*/
	else
		map[newHead_i][newHead_j] = 1;
}

void initGame() // 游戏初始化
{
	int i,j;
	
	// 初始化边框
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

	
	// 初始化蛇头位置
	map[Height/2][Width/2] = 1;
	// 初始化蛇身，地图中元素值分别为2,3,4,5....
	
	
	for (i=1;i<=4;i++)
		map[Height/2][Width/2-i] = i+1;

	// 初始小蛇向右移动
	moveDirection = 4;
	
	food_x = rand()%(Height-5) + 2;
	food_y = rand()%(Width-5) + 2;
	
	map[food_x][food_y] = -2;
	
	grass_x = rand()%(Height-5) + 2;
	grass_y = rand()%(Width-5) + 2;
	
	map[grass_x][grass_y] = -3;
}

void show()  // 显示画面
{
	gotoxy(0,0);  // 光标移动到原点位置，以下重画清屏
	int i,j;
	for (i=0;i<Height;i++)
	{
		for (j=0;j<Width;j++)
		{
			if (map[i][j]==0)
				printf(" ");   //   打印空格
			else if (map[i][j]==-1)
				printf("#");   //   打印边框#
			else if (map[i][j]==1)
				printf("@");   //   打印蛇头@
			else if (map[i][j]>1)
				printf("*");   //   打印蛇身*
			else if (map[i][j]==-2)
				printf("$");   //   打印食物$
			else if (map[i][j]==-3) 
				printf("!");   //   打印毒草！ 
		}
		printf("\n");
	}
	printf("你的分数是%d",point*10); 
	Sleep(60);
}	

void key()  // 与用户输入有关的更新
{
	char input;
	if(kbhit())  // 判断是否有输入
	{
		input = getch();  // 根据用户的不同输入来移动，不必输入回车
		if (input == 'a'||input == 'A') 
		{
			moveDirection = 3;   // 位置左移
			moveSnakeByDirection();
		}
		else if (input == 'd'||input == 'D')
		{
			moveDirection = 4;  // 位置右移
			moveSnakeByDirection();
		}
		else if (input == 'w'||input == 'W')
		{
			moveDirection = 1;  // 位置上移
			moveSnakeByDirection();
		}
		else if (input == 's'||input == 'S')
		{
			moveDirection = 2;   // 位置下移
			moveSnakeByDirection();
		}
	}
}

void key0()  // 与用户输入无关的更新
{
	moveSnakeByDirection();
}

