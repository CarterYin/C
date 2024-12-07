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
    char input[20];
    int turn = 1; // 玩家1先手

    initRecordBorard(); //初始化一个空棋盘
    innerLayoutToDisplayArray();
    displayBoard();  // 显示空棋盘

    while (1) {
        printf("玩家 %d 的回合 (输入 'quit' 退出): \n", turn);
        playerMove(turn);  // 提示玩家输入落子

        innerLayoutToDisplayArray();  // 更新棋盘显示
        displayBoard();  // 显示棋盘

        // 检查是否有玩家获胜
        if (checkWinner(1)) {
            printf("Player 1 wins!\n");
            break; // 退出游戏
        } else if (checkWinner(2)) {
            printf("Player 2 wins!\n");
            break; // 退出游戏
        }


        turn = (turn == 1) ? 2 : 1;  // 切换玩家
    }

    return 0;
}
//初始化一个空棋盘格局 
void initRecordBorard(void){
    //通过双重循环，将arrayForInnerBoardLayout清0
    int i,j;
    for(i=0;i<SIZE;i++){
        for (j=0;j<=SIZE;j++)
            arrayForInnerBoardLayout[i][j]=0;
    }
}

//将arrayForInnerBoardLayout中记录的棋子位置，转化到arrayForDisplayBoard中
void innerLayoutToDisplayArray(void){
    //第一步：将arrayForEmptyBoard中记录的空棋盘，复制到arrayForDisplayBoard中
    int i,j;
    for(i=0;i<SIZE;i++){
        for (j=0;j<=SIZE*CHARSIZE+1;j++)
            arrayForDisplayBoard[i][j]=arrayForEmptyBoard[i][j];
}
        

    //第二步：扫描arrayForInnerBoardLayout，当遇到非0的元素，将●或者◎复制到arrayForDisplayBoard的相应位置上
    //注意：arrayForDisplayBoard所记录的字符是中文字符，每个字符占2个字节。●和◎也是中文字符，每个也占2个字节。
        for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++)
            if(arrayForInnerBoardLayout[i][j]==1){
                arrayForDisplayBoard[i][CHARSIZE*j]=play1Pic[0];
                arrayForDisplayBoard[i][CHARSIZE*j+1]=play1Pic[1];
                if(CHARSIZE==3)
                    arrayForDisplayBoard[i][CHARSIZE*j+2]=play1Pic[2];
            }else if (arrayForInnerBoardLayout[i][j] ==2){
                arrayForDisplayBoard[i] [CHARSIZE*j]=play2Pic[0];
                arrayForDisplayBoard[i] [CHARSIZE*j+1]=play2Pic[1];
                if(CHARSIZE==3)
                    arrayForDisplayBoard[i] [CHARSIZE*j+2]=play2Pic[2];
            }
    }
}

//显示棋盘格局 
void displayBoard(void){
    int i;
    //第一步：清屏
    system("clear");   //清屏  
    //第二步：将arrayForDisplayBoard输出到屏幕上
    for(i=0;i<SIZE;i++){
        printf("%3d %s\n",SIZE-i,arrayForDisplayBoard[i]);
    
    }
    

    //第三步：输出最下面的一行字母A B .... 
    printf("   ");
    for(i=0;i<SIZE;i++)
        printf("%2c",'A'+i);
    printf("\n");
}
// 判断输入的坐标是否有效
int isValidPosition(int row, int col) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        return 0; // 超出棋盘范围
    }
    if (arrayForInnerBoardLayout[row][col] != 0) {
        return 0; // 该位置已被占用
    }
    return 1; // 合法位置
}

// 处理玩家输入并落子
void playerMove(int player) {
    char input[20];
    int row, col;
    char colChar;
    int validMove = 0;

    while (!validMove) {
        printf("请输入落子位置 (如:12h 或 h12)，输入 'quit' 退出: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';  // 去除换行符

        // 退出游戏判断
        if (strcmp(input, "quit") == 0) {
            exit(0);
        }

        // 解析输入
        if (sscanf(input, "%d%c", &row, &colChar) == 2 || sscanf(input, "%c%d", &colChar, &row) == 2) {
            colChar = tolower(colChar); // 处理大小写

            col = colChar - 'a'; // 转换列字母到列索引

            row = SIZE - row; // 转换行号，行号从下往上数

            if (col < 0 || col >= SIZE || row < 0 || row >= SIZE) {
                printf("输入的位置超出棋盘范围，请重新输入。\n");
            } else if (!isValidPosition(row, col)) {
                printf("该位置已被占用，请选择其他位置。\n");
            } else {
                arrayForInnerBoardLayout[row][col] = player; // 落子
                validMove = 1; // 合法输入，退出循环
            }
        } else {
            printf("输入无效,请使用正确格式,12h 或 h12。\n");
        }
    }
}

// 检查是否有玩家获胜（五子连珠）
// 检查玩家是否获胜
int checkWinner(int player) {
    // 遍历每个位置
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (arrayForInnerBoardLayout[row][col] == player) {
                // 检查水平五子连珠
                if (col + 4 < SIZE &&
                    arrayForInnerBoardLayout[row][col] == player &&
                    arrayForInnerBoardLayout[row][col + 1] == player &&
                    arrayForInnerBoardLayout[row][col + 2] == player &&
                    arrayForInnerBoardLayout[row][col + 3] == player &&
                    arrayForInnerBoardLayout[row][col + 4] == player) {
                    return 1; // 水平连珠，玩家获胜
                }

                // 检查垂直五子连珠
                if (row + 4 < SIZE &&
                    arrayForInnerBoardLayout[row][col] == player &&
                    arrayForInnerBoardLayout[row + 1][col] == player &&
                    arrayForInnerBoardLayout[row + 2][col] == player &&
                    arrayForInnerBoardLayout[row + 3][col] == player &&
                    arrayForInnerBoardLayout[row + 4][col] == player) {
                    return 1; // 垂直连珠，玩家获胜
                }

                // 检查左上到右下斜线五子连珠
                if (row + 4 < SIZE && col + 4 < SIZE &&
                    arrayForInnerBoardLayout[row][col] == player &&
                    arrayForInnerBoardLayout[row + 1][col + 1] == player &&
                    arrayForInnerBoardLayout[row + 2][col + 2] == player &&
                    arrayForInnerBoardLayout[row + 3][col + 3] == player &&
                    arrayForInnerBoardLayout[row + 4][col + 4] == player) {
                    return 1; // 左上到右下斜线连珠，玩家获胜
                }

                // 检查右上到左下斜线五子连珠
                if (row - 4 >= 0 && col + 4 < SIZE &&
                    arrayForInnerBoardLayout[row][col] == player &&
                    arrayForInnerBoardLayout[row - 1][col + 1] == player &&
                    arrayForInnerBoardLayout[row - 2][col + 2] == player &&
                    arrayForInnerBoardLayout[row - 3][col + 3] == player &&
                    arrayForInnerBoardLayout[row - 4][col + 4] == player) {
                    return 1; // 右上到左下斜线连珠，玩家获胜
                }
            }
        }
    }
    return 0; // 没有玩家获胜
}
