#include<iostream>
#include<windows.h>
#include<time.h>
#include<conio.h> 
#include<stdlib.h>
#define N 21
using namespace  std;

void gotoxy(int x,int y){//位置函数 
	COORD pos;//解释1 
	pos.X = 2 * x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);//解释2 
}

void color(int a){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a); //解释3 
}

void init(int apple[2]){
	int i, j;
	int wall[N+2][N+2] = {{0}};
	//游戏区域就是在左上角开始，所以没必要重新定位 
	for (i = 1; i <= N; i++)
		for (j = 1; j <= N; j++)
			wall[i][j] = 1;
	
	color(11);//设置输出颜色 
	
	for (i = 0; i < N+2; i++){
		for (j = 0; j < N+2; j++){
			if (wall[i][j])
				cout << "■";
			else
				cout << "□";
		}
		cout << endl;
	} 
	
	//设置提示位置
	//游戏方法 
	gotoxy(N+3, 1);
	color(20);
	cout << "按 W A S D 进行上下左右移动" << endl;
	
	//暂停 
	gotoxy(N+3, 2);
	color(20);
	cout << "按任意键暂停" << endl; 
	
	//得分 
	gotoxy(N+3, 3);
	color(20);
	cout << "得分：" << endl;
	
	//随机产生苹果的位置 
	apple[0] = rand()%N+1;
	apple[1] = rand()%N+1;
	gotoxy(apple[0], apple[1]);
	color(12);
	cout << "●" << endl;
}


int main(){
	int i, j;
	int** snake = NULL;  //存储蛇所有节点的位置 
	int apple[2];  //生成的苹果的位置 
	int score = 0;//记录分数
	int tail[2];
	int len = 3;
	char ch = 'p';
	
	srand((unsigned)time(NULL));//随机种子
	init(apple) ;
	
	snake = (int**)realloc(snake, sizeof(int*)*len);
	for (i = 0; i < len; i++)
		snake[i] = (int*)malloc(sizeof(int)*2);

	for(i=0;i<len;i++){
		snake[i][0]=N/2;
		snake[i][1]=N/2+i;
		gotoxy(snake[i][0],snake[i][1]);
		color(14);
		cout<<"★"<<endl;
	}
	
	while(1)//进入消息循环
	{
		//为什么要在这里输出一个 "■"， 是因为只要开始移动，产生的 "★"就没有消失， 只是不断地往上添加 
		//因此需要将最后一个设置为 "■"， 使得看起来像是移动了 
		tail[0]=snake[len-1][0];
		tail[1]=snake[len-1][1];
		gotoxy(tail[0],tail[1]);
		color(11);
		cout<<"■"<<endl;

		for(i=len-1;i>0;i--){
			//其实只用控制蛇的第一个节点的移动，后面的节点就设置为前面的节点的上次的位置即可 
			snake[i][0]=snake[i-1][0];
			snake[i][1]=snake[i-1][1];
			gotoxy(snake[i][0],snake[i][1]);
			color(14);
			cout<<"★"<<endl;
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
		cout<<"★"<<endl;
		Sleep(abs(200-0.5*score)); // 随着分数的增加，速度将越来越快 
		
		if(snake[0][0]==apple[0]&&snake[0][1]==apple[1])//吃掉苹果后蛇分数加1，蛇长加1
		{
			score++;
			len++;
			snake=(int**)realloc(snake,sizeof(int*)*len);
			snake[len-1]=(int*)malloc(sizeof(int)*2);
			
			apple[0]=rand()%N+1;
			apple[1]=rand()%N+1;
			gotoxy(apple[0],apple[1]);
			color(12);
			cout<<"●"<<endl;
			
			gotoxy(N+5,3);
			color(20);
			cout<<score<<endl;
		}
		
		if(snake[0][1]==0||snake[0][1]==N||snake[0][0]==0||snake[0][0]==N)//撞到围墙后失败
		{
			gotoxy(N/2,N/2);
			color(30);
			cout<<"失败！！！"<<endl;
			
			for(i=0;i<len;i++)
				free(snake[i]);
			
			Sleep(INFINITE);
			exit(0);
			}
		}
	return 0;
} 
