/**
* @file     move.c
* @brief    �����ļ�
* @details  ���������������
*/

#include "move.h"

/**
 * @brief �������
 * @param[in]  state     ���̶���ָ��
 * @param[out] *x_row    ���ӵ�������ָ��
 * @param[out] *y_column ���ӵ�������ָ��
 * @param[in]  order     ���巽
 * @retval ��
 */
void playermove(CHESSSTATE** state, char* x_row, char* y_column, CHESSSTATE order) {
	char x, y;
	char str[5] = { '\0' };
	printf("���%d-%s�ߣ���H��8��,������H8:", order, order == black ? "�ڷ�" : "�׷�");
	while (1) {
		//fflush(stdin);
		scanf("%s", &str);
		//scanf("%c%c", x_row, y_column);
		*y_column = str[0] - 'A';
		*x_row = atoi(str+1)-1;
		if (*x_row >= 0 && *x_row <= ROW - 1 && *y_column >= 0 && *y_column <= COLUMN - 1) {
			if (state[*x_row][*y_column]) {
				printf("��λ���Ѿ��������ˣ����±��λ��:");
				continue;
			}
			else {
				state[*x_row][*y_column] = order;
				break;
			}
		}
		else {
			printf("�Ƿ����룬����������:");
			continue;
		}
	}
}