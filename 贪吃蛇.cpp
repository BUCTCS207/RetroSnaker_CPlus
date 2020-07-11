#include<iostream>
#include<windows.h>
#include<time.h>
#include<conio.h> 
#include<stdlib.h>
#define N 21
using namespace  std;

void gotoxy(int x,int y){//λ�ú��� 
	COORD pos;//����1 
	pos.X = 2 * x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);//����2 
}

void color(int a){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a); //����3 
}

void init(int apple[2]){
	int i, j;
	int wall[N+2][N+2] = {{0}};
	//��Ϸ������������Ͻǿ�ʼ������û��Ҫ���¶�λ 
	for (i = 1; i <= N; i++)
		for (j = 1; j <= N; j++)
			wall[i][j] = 1;
	
	color(11);//���������ɫ 
	
	for (i = 0; i < N+2; i++){
		for (j = 0; j < N+2; j++){
			if (wall[i][j])
				cout << "��";
			else
				cout << "��";
		}
		cout << endl;
	} 
	
	//������ʾλ��
	//��Ϸ���� 
	gotoxy(N+3, 1);
	color(20);
	cout << "�� W A S D �������������ƶ�" << endl;
	
	//��ͣ 
	gotoxy(N+3, 2);
	color(20);
	cout << "���������ͣ" << endl; 
	
	//�÷� 
	gotoxy(N+3, 3);
	color(20);
	cout << "�÷֣�" << endl;
	
	//�������ƻ����λ�� 
	apple[0] = rand()%N+1;
	apple[1] = rand()%N+1;
	gotoxy(apple[0], apple[1]);
	color(12);
	cout << "��" << endl;
}


int main(){
	int i, j;
	int** snake = NULL;  //�洢�����нڵ��λ�� 
	int apple[2];  //���ɵ�ƻ����λ�� 
	int score = 0;//��¼����
	int tail[2];
	int len = 3;
	char ch = 'p';
	
	srand((unsigned)time(NULL));//�������
	init(apple) ;
	
	snake = (int**)realloc(snake, sizeof(int*)*len);
	for (i = 0; i < len; i++)
		snake[i] = (int*)malloc(sizeof(int)*2);

	for(i=0;i<len;i++){
		snake[i][0]=N/2;
		snake[i][1]=N/2+i;
		gotoxy(snake[i][0],snake[i][1]);
		color(14);
		cout<<"��"<<endl;
	}
	
	while(1)//������Ϣѭ��
	{
		//ΪʲôҪ���������һ�� "��"�� ����ΪֻҪ��ʼ�ƶ��������� "��"��û����ʧ�� ֻ�ǲ��ϵ�������� 
		//�����Ҫ�����һ������Ϊ "��"�� ʹ�ÿ����������ƶ��� 
		tail[0]=snake[len-1][0];
		tail[1]=snake[len-1][1];
		gotoxy(tail[0],tail[1]);
		color(11);
		cout<<"��"<<endl;

		for(i=len-1;i>0;i--){
			//��ʵֻ�ÿ����ߵĵ�һ���ڵ���ƶ�������Ľڵ������Ϊǰ��Ľڵ���ϴε�λ�ü��� 
			snake[i][0]=snake[i-1][0];
			snake[i][1]=snake[i-1][1];
			gotoxy(snake[i][0],snake[i][1]);
			color(14);
			cout<<"��"<<endl;
		}
		if(kbhit()){
			gotoxy(0,N+2);
			ch=getche();
		}
		
		switch(ch){
			case 'w':snake[0][1]--;break;
			case 's':snake[0][1]++;break;
			case 'a':snake[0][0]--;break;
			case 'd':snake[0][0]++;break;
			default: break;
		}
		gotoxy(snake[0][0],snake[0][1]);
		color(14);
		cout<<"��"<<endl;
		Sleep(abs(200-0.5*score)); // ���ŷ��������ӣ��ٶȽ�Խ��Խ�� 
		
		if(snake[0][0]==apple[0]&&snake[0][1]==apple[1])//�Ե�ƻ�����߷�����1���߳���1
		{
			score++;
			len++;
			snake=(int**)realloc(snake,sizeof(int*)*len);
			snake[len-1]=(int*)malloc(sizeof(int)*2);
			
			apple[0]=rand()%N+1;
			apple[1]=rand()%N+1;
			gotoxy(apple[0],apple[1]);
			color(12);
			cout<<"��"<<endl;
			
			gotoxy(N+5,3);
			color(20);
			cout<<score<<endl;
		}
		
		if(snake[0][1]==0||snake[0][1]==N||snake[0][0]==0||snake[0][0]==N)//ײ��Χǽ��ʧ��
		{
			gotoxy(N/2,N/2);
			color(30);
			cout<<"ʧ�ܣ�����"<<endl;
			
			for(i=0;i<len;i++)
				free(snake[i]);
			
			Sleep(INFINITE);
			exit(0);
			}
		}
	return 0;
} 
