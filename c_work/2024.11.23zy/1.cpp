#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 15
#define CHARSIZE 2
void initRecordBorard(void); //��ʼ�����̵��ڲ���¼����arrayForInnerBoardLayout,
                            // ���������ڴ洢������ÿ��λ�õ�״̬���Ƿ������Ӻ�������ɫ�� 
void innerLayoutToDisplayArray(void); //���ڲ����̲���arrayForInnerBoardLayoutת��Ϊ��ʾ
                                      //�����̲���arrayForDispalyBoard.(�������̸��Ƶ�Displayed��
									  //�������ӵ�λ����Displayed��Ӧλ��������ӡ� 
void displayBoard(void); //������Ȼ���ӡ arrayForDisplayBoard �е����ݣ�
                        //����ӡ�������������ĸ�У�A��O����
void makeMove(int player, int x, int y);
int validateMove(int x, int y);
void getPlayerMove(int *x, int *y, int player);


//������ģ�� 
char arrayForEmptyBoard[SIZE][SIZE*CHARSIZE+1] = //ÿ��������Ҫ CHARSIZE��2���ֽڣ��Ŀռ䡣
                                                //ÿ���� SIZE �����ӣ�������Ҫ SIZE * CHARSIZE ���ֽڡ�
{
        "���өөөөөөөөөөөөө�",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "���۩۩۩۩۩۩۩۩۩۩۩۩۩�"
};
//������洢������ʾ������ 
char arrayForDisplayBoard[SIZE][SIZE*CHARSIZE+1];
//���������ڼ�¼��ǰ�����̵ĸ��
 
char play1Pic[]="��";  //������;
char play1CurrentPic[]="��";   // �����ӵ�ǰѡ��״̬

char play2Pic[]="��"; //������;
char play2CurrentPic[]="��";// �����ӵ�ǰѡ��״̬ //��ռ�����ֽ� 

//���������ڼ�¼��ǰ�����̵ĸ�� 
int arrayForInnerBoardLayout[SIZE][SIZE];//��������������λ�õ�״̬�� ���߷����µ����� 

int main()

{

    initRecordBorard();    //��ʼ��һ��������
    
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

//��ʼ��һ�������̸�� 
void initRecordBorard(void){
    int i, j;
    for(i = 0; i < SIZE; i++) {
        for(j = 0; j < SIZE; j++) {
            arrayForInnerBoardLayout[i][j] = 0;
        }
    }
}

//��arrayForInnerBoardLayout�м�¼������λ�ã�ת����arrayForDisplayBoard��
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

//��ʾ���̸�� 
void displayBoard(void){
    int i;
    //��һ��������
    system("clear");   //����  
    //�ڶ�������arrayForDisplayBoard�������Ļ��
    for(i = 0; i < SIZE; i++) {
        printf("%s\n", arrayForDisplayBoard[i]);
    }

    //������������������һ����ĸA B .... 
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
