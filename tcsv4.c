//��     ��������󳤶�Ϊ100��
//��ά���� snake[100][2]������
//(i��ʾĳһ��)
//snake[i][0] X���� ���� 
//snake[i][1] Y���� ���� 


#include <stdio.h>
#include <windows.h>

#define Height 50  // ��Ϸ����ߴ�
#define Width 103

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

int moveDirection;





int main()
{
	system("color 0W");
	printf("\a");
    initGraph();              //ͼ����ʾ��ʽ��ʼ��
//	Newgame();
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


