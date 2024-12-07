#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 15
#define CHARSIZE 2
void initRecordBorard(void); //初始化棋盘的内部记录数组arrayForInnerBoardLayout,
                            // 该数组用于存储棋盘上每个位置的状态（是否有棋子和棋子颜色） 
void innerLayoutToDisplayArray(void); //将内部棋盘布局arrayForInnerBoardLayout转换为显示
                                      //的棋盘布局arrayForDispalyBoard.(将空棋盘复制到Displayed中
									  //根据棋子的位置在Displayed相应位置添加棋子。 
void displayBoard(void); //清屏，然后打印 arrayForDisplayBoard 中的内容，
                        //最后打印棋盘最下面的字母行（A到O）。
void makeMove(int player, int x, int y);
int validateMove(int x, int y);
void getPlayerMove(int *x, int *y, int player);


//空棋盘模板 
char arrayForEmptyBoard[SIZE][SIZE*CHARSIZE+1] = //每个格子需要 CHARSIZE（2个字节）的空间。
                                                //每行有 SIZE 个格子，所以需要 SIZE * CHARSIZE 个字节。
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
//此数组用于记录当前的棋盘的格局
 
char play1Pic[]="●";  //黑棋子;
char play1CurrentPic[]="▲";   // 黑棋子当前选择状态

char play2Pic[]="◎"; //白棋子;
char play2CurrentPic[]="△";// 白棋子当前选择状态 //均占两个字节 

//此数组用于记录当前的棋盘的格局 
int arrayForInnerBoardLayout[SIZE][SIZE];//检验棋盘上任意位置的状态， 或者放置新的棋子 

int main()

{

    initRecordBorard();    //初始化一个空棋盘
    
    int x , y;

    char player = 1;
    while (1) 
	{
    	innerLayoutToDisplayArray();
        displayBoard();
            getPlayerMove(&x, &y, player);
            if (!validateMove(x, y)) {
                printf("Invalid move. Try again.\n");
            continue;
        }
        makeMove(player, x, y);
        player = 3 - player;
    }
    
    return 0;
}

//初始化一个空棋盘格局 
void initRecordBorard(void){
    int i, j;
    for(i = 0; i < SIZE; i++) {
        for(j = 0; j < SIZE; j++) {
            arrayForInnerBoardLayout[i][j] = 0;
        }
    }
}

//将arrayForInnerBoardLayout中记录的棋子位置，转化到arrayForDisplayBoard中
void innerLayoutToDisplayArray(void){
    int i, j;
    memcpy(arrayForDisplayBoard, arrayForEmptyBoard, sizeof(arrayForEmptyBoard));
    for(i = 0; i < SIZE; i++) {
        for(j = 0; j < SIZE; j++) {
            if(arrayForInnerBoardLayout[i][j] == 1) {
                memcpy(arrayForDisplayBoard[i] + j * CHARSIZE * 2, play1Pic, strlen(play1Pic));
            } else if(arrayForInnerBoardLayout[i][j] == 2) {
                memcpy(arrayForDisplayBoard[i] + j * CHARSIZE * 2, play2Pic, strlen(play2Pic));
            }
        }
    }
}

//显示棋盘格局 
void displayBoard(void){
    int i;
    //第一步：清屏
    system("clear");   //清屏  
    //第二步：将arrayForDisplayBoard输出到屏幕上
    for(i = 0; i < SIZE; i++) {
        printf("%s\n", arrayForDisplayBoard[i]);
    }

    //第三步：输出最下面的一行字母A B .... 
    for(i = 0; i < SIZE; i++) {
        printf("%c ", 'A' + i);
    }
    printf("\n");
}

void makeMove(int player, int x, int y){
	
	arrayForInnerBoardLayout[y][x]=player;

}

int validateMove(int x, int y){
	return x >=0 && x < SIZE && y >= 0 && y < SIZE && arrayForInnerBoardLayout[y][x]==0;
}

void getPlayerMove(int *x, int *y, int player){
	char input[5];
	printf("Player %d, enter your move(e.g., H12):",player);
	scanf("%s",input);
	*y=input[0]-'A';
	*x=atoi(input +1)-1;
	
}
