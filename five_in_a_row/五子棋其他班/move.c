/**
* @file     move.c
* @brief    下棋文件
* @details  玩家在棋盘上下棋
*/

#include "move.h"

/**
 * @brief 玩家下棋
 * @param[in]  state     棋盘二级指针
 * @param[out] *x_row    落子的行坐标指针
 * @param[out] *y_column 落子的列坐标指针
 * @param[in]  order     下棋方
 * @retval 无
 */
void playermove(CHESSSTATE** state, char* x_row, char* y_column, CHESSSTATE order) {
	char x, y;
	char str[5] = { '\0' };
	printf("玩家%d-%s走，如H列8行,则输入H8:", order, order == black ? "黑方" : "白方");
	while (1) {
		//fflush(stdin);
		scanf("%s", &str);
		//scanf("%c%c", x_row, y_column);
		*y_column = str[0] - 'A';
		*x_row = atoi(str+1)-1;
		if (*x_row >= 0 && *x_row <= ROW - 1 && *y_column >= 0 && *y_column <= COLUMN - 1) {
			if (state[*x_row][*y_column]) {
				printf("该位置已经有棋子了，请下别的位置:");
				continue;
			}
			else {
				state[*x_row][*y_column] = order;
				break;
			}
		}
		else {
			printf("非法输入，请重新输入:");
			continue;
		}
	}
}