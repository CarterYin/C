#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 15
#define CHARSIZE 2
void initRecordBorard(void);
void innerLayoutToDisplayArray(void);
void displayBoard(void);

//棋盘使用的是GBK编码，每一个中文字符占用2个字节。

//空棋盘模板 
char arrayForEmptyBoard[SIZE][SIZE*CHARSIZE+1] = 
{
		"┏┯┯┯┯┯┯┯┯┯┯┯┯┯┓",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┗┷┷┷┷┷┷┷┷┷┷┷┷┷┛"
};
//此数组存储用于显示的棋盘 
char arrayForDisplayBoard[SIZE][SIZE*CHARSIZE+1];
 
char play1Pic[]="●";//黑棋子;
char play1CurrentPic[]="▲"; 

char play2Pic[]="◎";//白棋子;
char play2CurrentPic[]="△";

//此数组用于记录当前的棋盘的格局 
int arrayForInnerBoardLayout[SIZE][SIZE];

int main()

{

    initRecordBorard();    //初始化一个空棋盘

    arrayForInnerBoardLayout[0][0]=1;    //在棋盘的左上角落一个黑色棋子
    innerLayoutToDisplayArray();  //将心中的棋盘转成用于显示的棋盘
    displayBoard();          //显示棋盘
    getchar();   

    arrayForInnerBoardLayout[5][9]=2;
    innerLayoutToDisplayArray();
    displayBoard();
    getchar();

    arrayForInnerBoardLayout[3][4]=2;
    innerLayoutToDisplayArray();
    displayBoard();
    getchar();

    arrayForInnerBoardLayout[6][1]=1;
    innerLayoutToDisplayArray();
    displayBoard();
    getchar();

    arrayForInnerBoardLayout[9][4]=2;
    innerLayoutToDisplayArray();
    displayBoard();
    getchar();
    return 0;
}

//初始化一个空棋盘格局 
void initRecordBorard(void){
	//通过双重循环，将arrayForInnerBoardLayout清0
    int i, j;
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
			arrayForInnerBoardLayout[i][j] = 0;
}

//将arrayForInnerBoardLayout中记录的棋子位置，转化到arrayForDisplayBoard中
void innerLayoutToDisplayArray(void){
	//第一步：将arrayForEmptyBoard中记录的空棋盘，复制到arrayForDisplayBoard中
        int i, j, k;
	for (i = 0; i < SIZE; i++)
		for (j = 0; j <= SIZE * CHARSIZE; j++)
			arrayForDisplayBoard[i][j] = arrayForEmptyBoard[i][j];



	//第二步：扫描arrayForInnerBoardLayout，当遇到非0的元素，将●或者◎复制到arrayForDisplayBoard的相应位置上
	//注意：arrayForDisplayBoard所记录的字符是中文字符，每个字符占2个字节。●和◎也是中文字符，每个也占2个字节。
        for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
		{ // 若元素为正数，说明是已经下完的棋子，用圆形；若为负数，是正在下的棋子，用三角形
			if (arrayForInnerBoardLayout[i][j] == 1)
			{
				for (k = 0; k < CHARSIZE; k++)
					arrayForDisplayBoard[SIZE - 1 - i][j * CHARSIZE + k] = play1Pic[k];
			}
			else if (arrayForInnerBoardLayout[i][j] == 2)
			{
				for (k = 0; k < CHARSIZE; k++)
					arrayForDisplayBoard[SIZE - 1 - i][j * CHARSIZE + k] = play2Pic[k];
			}
			else if (arrayForInnerBoardLayout[i][j] == -1)
			{
				for (k = 0; k < CHARSIZE; k++)
					arrayForDisplayBoard[SIZE - 1 - i][j * CHARSIZE + k] = play1CurrentPic[k];
				arrayForInnerBoardLayout[i][j] = 1;
			}
			else if (arrayForInnerBoardLayout[i][j] == -2)
			{
				for (k = 0; k < CHARSIZE; k++)
					arrayForDisplayBoard[SIZE - 1 - i][j * CHARSIZE + k] = play2CurrentPic[k];
				arrayForInnerBoardLayout[i][j] = 2;
			}
		}
}


//显示棋盘格局 
void displayBoard(void){
	int i;
    int result;
	//第一步：清屏
	result=system("clear");   //清屏  
	//第二步：将arrayForDisplayBoard输出到屏幕上
    for (i = 0; i < SIZE; i++)
	{
		printf("%2d %s\n", SIZE - i, arrayForDisplayBoard[i]);
	}
	

	//第三步：输出最下面的一行字母A B .... 
    printf("  ");
	for (i = 0; i < SIZE; i++)
		printf(" %c", i + 'A');
	printf("\n");
} 

