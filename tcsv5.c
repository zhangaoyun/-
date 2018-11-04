// 0为空格0，-1为边框#，-2为食物!，-3为毒草，1为蛇头@，大于1的正数为蛇身*
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define Height 50  // 游戏画面尺寸
#define Width 103

void initGame(); // 初始化函数 

void show();// 界面函数 
void key();// 按键函数 
void key0();// 无按键函数 

int moveDirection; // 蛇移动位置，上下左右分别用1，2，3，4表示
int food_x,food_y; // 食物的位置
int grass0_x,grass0_y; // 毒草的位置 
int grass1_x,grass1_y; // 毒草的位置 
int grass2_x,grass2_y; // 毒草的位置 
int map[Height][Width] = {0};// 先初始化地图为空白 

int point = 0;	//计分 

int main()
{
	system("color 0B");// 设置游戏前景为蓝色，背景为黑色 
	initGame();  // 数据初始化	
	while (1) //  游戏循环执行
	{
		show();  // 显示画面
		key0();  // 无按键时 
		key();  // 按键时 
	}
	return 0;
}

void gotoxy(int x,int y)  // 光标函数？光标移动到(x,y)位置
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

void moveSnakeByDirection()// 蛇根据方向移动 
{
	int i,j;
	for (i=1;i<Height-1;i++)
		for (j=1;j<Width-1;j++)
			if (map[i][j]>0)
				map[i][j]++;// 大于0的都为蛇的一部分，都加1 

	int oldTail_i,oldTail_j,oldHead_i,oldHead_j;
	int max = 0;// 定义一个最大数字 

	for (i=1;i<Height-1;i++)
		for (j=1;j<Width-1;j++)
			if (map[i][j]>0)
			{
				if (max<map[i][j])
				{
					max = map[i][j];
					oldTail_i = i;
					oldTail_j = j;
				}// 遍历数组，找出最大数字，此即为旧蛇尾 
				if (map[i][j]==2)
				{
					oldHead_i = i;
					oldHead_j = j;
				}// 旧蛇头加1成了2 
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
		map[grass0_x][grass0_y] = 0;
		// 产生一个新的毒草 
		grass0_x = rand()%(Height-5) + 2;
		grass0_y = rand()%(Width-5) + 2;
		map[grass0_x][grass0_y] = -3;
		
		point--;

		// 原来的旧蛇头减掉，长度自动-1
		map[oldHead_i][oldHead_j] = 0;
	}
	
	if (map[newHead_i][newHead_j]==-3)
	{
		map[grass1_x][grass1_y] = 0;
		// 产生一个新的毒草 
		grass1_x = rand()%(Height-5) + 2;
		grass1_y = rand()%(Width-5) + 2;
		map[grass1_x][grass1_y] = -3;
		
		point--;

		// 原来的旧蛇头减掉，长度自动-1
		map[oldHead_i][oldHead_j] = 0;
	}

	if (map[newHead_i][newHead_j]==-3)
	{
		map[grass2_x][grass2_y] = 0;
		// 产生一个新的毒草 
		grass2_x = rand()%(Height-5) + 2;
		grass2_y = rand()%(Width-5) + 2;
		map[grass2_x][grass2_y] = -3;
		
		point--;

		// 原来的旧蛇头减掉，长度自动-1
		map[oldHead_i][oldHead_j] = 0;
	}


	// 判断蛇是否和自身撞，或者和边框撞，游戏结束 
	if (map[newHead_i][newHead_j]>0 || map[newHead_i][newHead_j]==-1)
	{
		printf("游戏结束\a\n");
		Sleep(2000);
		system("pause");
		exit(0);
	}
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
	// 初始化蛇身.	
	for (i=1;i<=4;i++)
		map[Height/2][Width/2-i] = i+1;

	// 初始蛇向右移动
	moveDirection = 4;
	// 1 上 2 下 3 左 4 右 
	
	// 产生随机数
	food_x = rand()%(Height-5) + 2;
	food_y = rand()%(Width-5) + 2;
	
	map[food_x][food_y] = -2;
	
	grass0_x = rand()%(Height-5) + 2;
	grass0_y = rand()%(Width-5) + 2;
	
	map[grass0_x][grass0_y] = -3;
}

void show()  // 显示画面
{
	gotoxy(0,0);  // 光标移动到原点位置，以下清屏重新打印 
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

	printf("你的分数是%d\n",point*10); //打印分数 
	Sleep(60);
}	

void key()  // 按键时
{
	char input;
	if(kbhit())  // 判断是否有输入
	{
		input = getch();  // 根据输入来移动
		if (input == 'a') 
		{
			moveDirection = 3;   // 左移
			moveSnakeByDirection();
		}
		else if (input == 'd')
		{
			moveDirection = 4;  // 右移
			moveSnakeByDirection();
		}
		else if (input == 'w')
		{
			moveDirection = 1;  // 上移
			moveSnakeByDirection();
		}
		else if (input == 's')
		{
			moveDirection = 2;   // 下移
			moveSnakeByDirection();
		}
	}
}

void key0()  // 无按键时移动 
{
	moveSnakeByDirection();
}



