#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 15
#define CHARSIZE 2
void initRecordBorard(void);
void innerLayoutToDisplayArray(void);
void displayBoard(void);

//����ʹ�õ���GBK���룬ÿһ�������ַ�ռ��2���ֽڡ�

//������ģ�� 
char arrayForEmptyBoard[SIZE][SIZE*CHARSIZE+1] = 
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
 
char play1Pic[]="��";//������;
char play1CurrentPic[]="��"; 

char play2Pic[]="��";//������;
char play2CurrentPic[]="��";

//���������ڼ�¼��ǰ�����̵ĸ�� 
int arrayForInnerBoardLayout[SIZE][SIZE];

int main()

{

    initRecordBorard();    //��ʼ��һ��������

    arrayForInnerBoardLayout[0][0]=1;    //�����̵����Ͻ���һ����ɫ����
    innerLayoutToDisplayArray();  //�����е�����ת��������ʾ������
    displayBoard();          //��ʾ����
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

//��ʼ��һ�������̸�� 
void initRecordBorard(void){
	//ͨ��˫��ѭ������arrayForInnerBoardLayout��0
    int i, j;
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
			arrayForInnerBoardLayout[i][j] = 0;
}

//��arrayForInnerBoardLayout�м�¼������λ�ã�ת����arrayForDisplayBoard��
void innerLayoutToDisplayArray(void){
	//��һ������arrayForEmptyBoard�м�¼�Ŀ����̣����Ƶ�arrayForDisplayBoard��
        int i, j, k;
	for (i = 0; i < SIZE; i++)
		for (j = 0; j <= SIZE * CHARSIZE; j++)
			arrayForDisplayBoard[i][j] = arrayForEmptyBoard[i][j];



	//�ڶ�����ɨ��arrayForInnerBoardLayout����������0��Ԫ�أ�������ߡ��Ƶ�arrayForDisplayBoard����Ӧλ����
	//ע�⣺arrayForDisplayBoard����¼���ַ��������ַ���ÿ���ַ�ռ2���ֽڡ���͡�Ҳ�������ַ���ÿ��Ҳռ2���ֽڡ�
        for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
		{ // ��Ԫ��Ϊ������˵�����Ѿ���������ӣ���Բ�Σ���Ϊ�������������µ����ӣ���������
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


//��ʾ���̸�� 
void displayBoard(void){
	int i;
    int result;
	//��һ��������
	result=system("clear");   //����  
	//�ڶ�������arrayForDisplayBoard�������Ļ��
    for (i = 0; i < SIZE; i++)
	{
		printf("%2d %s\n", SIZE - i, arrayForDisplayBoard[i]);
	}
	

	//������������������һ����ĸA B .... 
    printf("  ");
	for (i = 0; i < SIZE; i++)
		printf(" %c", i + 'A');
	printf("\n");
} 

