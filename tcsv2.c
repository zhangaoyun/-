
#include <stdio.h>
#include <windows.h>

#define up 'w'

#define down 's'

#define left 'a'

#define right 'd'

#define stop 'p'


void map();
void newgame();
void creatsnake(); 
void gotoxy(int x, int y);
void gotoprint();
void food();
void move();
void key();


int i=0;
int j=0;

int snake[100][2];	//蛇身坐标数组 

int foodx;
int foody;



int main()
{
	map();
	while(1){
			creatsnake();
	} 

	food();


	
	int gameres=0;
	getchar();
	return 0;
 
} 


void map()
{
	for(i=0;i<103;i+=2){	//打印上下边框 
		gotoprint(i,0);
		gotoprint(i,50);		
	}
	for(j=0;j<50;j++){		//打印左右边框 
		gotoprint(0,j);
		gotoprint(102,j);

	}
	//system("cls");
}

void food()
{
	srand((unsigned)time(NULL)); 
	int a = rand()%100+1;//生成1-100的随机数
	int b =rand()%48+1;
	foodx = a;
	foody = b;
	gotoxy(foodx,foody);
	printf("$");
}

void gotoxy(int x, int y)

{

	COORD pos;

	HANDLE hOutput;

	pos.X = x;

	pos.Y = y;

	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(hOutput, pos);

}

void gotoprint(int x,int y)
{
	gotoxy(x,y);
	printf("■");
}

void creatsnake()
{
	gotoxy(4,25);
	printf("@");
	gotoxy(2,25);
	printf("@");
	gotoxy(3,25);
	printf("@");
}

