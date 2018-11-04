//蛇     （假设最大长度为100）
//二维数组 snake[100][2]来描述
//(i表示某一节)
//snake[i][0] X坐标 横着 
//snake[i][1] Y坐标 竖着 


#include <stdio.h>
#include <windows.h>

#define UP 'w'

#define DOWN 's'

#define LEFT 'a'

#define RIGHT 'd'

#define stop 'p'

void initGraph();
void map();
void Newgame();
void creatsnake(); 
void gotoxy(int x, int y);
void gotoprint();
void food();
void move();



int i=0;
int j=0;

int is;
int js;

int current;
int last;

int snake[100][2];	//蛇身坐标数组 

int foodx;	//食物的x坐标 
int foody;	//食物的y坐标

int sLength=4;

int direction;

int a;





int main()
{
	system("color 0W");
	printf("\a");
    initGraph();              //图形显示方式初始化
	Newgame();
	while(1){
		
	
	move();

	getchar();
	}
	
	return 0;

}


void initGraph()
{
	map();
	food(); 
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
	int b =rand()%48+1;//生成1-48的随机数 
	foodx = a;
	foody = b;
	gotoxy(foodx,foody);
	printf("$");
}


void Newgame()
{
	snake[0][0]=2;	//蛇初始x坐标 
	snake[0][1]=25;	//蛇初始y坐标 
	gotoxy(snake[0][0],snake[0][1]);
	printf("@"); 
	for (a=1;a<4;a++){
	snake[a][0]=snake[a-1][0]+1;
	snake[a][1]=snake[0][1];
	gotoxy(snake[a][0],snake[a][1]);
	printf("@"); 
	}
}
void move()
{
    int i;
    direction =RIGHT;
    for(i=sLength-1;i>0;i--)    //从尾巴开始，每一个点的位置等于它前面一个点的位置
    {
        snake[i][0]=snake[i-1][0];
        snake[i][1]=snake[i-1][1];
    }
    switch(direction)
    {
    case UP:
        snake[0][0]--;
        break;
    case DOWN:
        snake[0][0]++;
        break;
    case LEFT:
        snake[0][1]--;
        break;
    case RIGHT:
        snake[0][1]++;
        break;
    }

}



void gotoxy(int x, int y)//光标函数？ 

{

	COORD pos;

	HANDLE hOutput;

	pos.X = x;

	pos.Y = y;

	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(hOutput, pos);

}

void gotoprint(int x,int y)	//打印函数 
{
	gotoxy(x,y);
	printf("■");
}




