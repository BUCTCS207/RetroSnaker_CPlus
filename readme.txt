解释

1.  COORD是Windows API中定义的一bai种结构，表示一个字符在控制台du屏幕上的坐标。
typedef struct _COORD {
	SHORT X; // horizontal coordinate
	SHORT Y; // vertical coordinate
} COORD;

且COORD申请的位置变量是按照行计算的


2. SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos)；//设置输出的位置(应该是先设置，再进行输出)


3. SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);//这是给输出设置颜色，其中a是颜色值，是一个int型变量


4. 这是一个由C++语言写成的简单的贪吃蛇游戏，其中贪吃蛇.exe是可执行的游戏程序