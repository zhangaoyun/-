//��     ��������󳤶�Ϊ100��
//��ά���� snake[100][2]������
//(i��ʾĳһ��)
//snake[i][0] X���� ���� 
//snake[i][1] Y���� ���� 


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

int snake[100][2];	//������������ 

int foodx;	//ʳ���x���� 
int foody;	//ʳ���y����

int sLength=4;

int direction;

int a;





int main()
{
	system("color 0W");
	printf("\a");
    initGraph();              //ͼ����ʾ��ʽ��ʼ��
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
	for(i=0;i<103;i+=2){	//��ӡ���±߿� 
		gotoprint(i,0);
		gotoprint(i,50);		
	}
	for(j=0;j<50;j++){		//��ӡ���ұ߿� 
		gotoprint(0,j);
		gotoprint(102,j);

	}
	//system("cls");
}

void food()
{
	srand((unsigned)time(NULL)); 
	int a = rand()%100+1;//����1-100�������
	int b =rand()%48+1;//����1-48������� 
	foodx = a;
	foody = b;
	gotoxy(foodx,foody);
	printf("$");
}


void Newgame()
{
	snake[0][0]=2;	//�߳�ʼx���� 
	snake[0][1]=25;	//�߳�ʼy���� 
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
    for(i=sLength-1;i>0;i--)    //��β�Ϳ�ʼ��ÿһ�����λ�õ�����ǰ��һ�����λ��
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



void gotoxy(int x, int y)//��꺯���� 

{

	COORD pos;

	HANDLE hOutput;

	pos.X = x;

	pos.Y = y;

	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(hOutput, pos);

}

void gotoprint(int x,int y)	//��ӡ���� 
{
	gotoxy(x,y);
	printf("��");
}




