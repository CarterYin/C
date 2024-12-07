#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 15
#define CHARSIZE 2

// Game Modes
enum GameMode { PVP, PVE_HUMAN_FIRST, PVE_AI_FIRST };
enum GameMode currentMode = PVP;  // Default to Player vs Player
int currentPlayer = 1;  // Default to Player 1
int aiPlayer = 2;  // Player 2 is AI in PVE mode

// Declare the board arrays and other variables
char arrayForEmptyBoard[SIZE][SIZE * CHARSIZE + 1] = {
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

// Board arrays for display and internal state
char arrayForDisplayBoard[SIZE][SIZE * CHARSIZE + 1];
int arrayForInnerBoardLayout[SIZE][SIZE];

// Player pieces
char play1Pic[] = "●";  // Black piece
char play1CurrentPic[] = "▲";

char play2Pic[] = "◎";  // White piece (AI)
char play2CurrentPic[] = "△";

// Function declarations
void initRecordBorard(void);
void innerLayoutToDisplayArray(void);
void displayBoard(void);
void chooseGameMode(void);
int isValidPosition(int row, int col);
void playerMove(int player);
void aiMove(void);
int checkWinner(int player);

int main() {
    srand(time(NULL));  // Initialize random seed
    chooseGameMode();  // Choose game mode and who starts first

    initRecordBorard();  // Initialize an empty board
    innerLayoutToDisplayArray();
    displayBoard();  // Display empty board

    while (1) {
        if (currentMode == PVP || currentPlayer == 1) {
            printf("玩家 %d 的回合 (输入 'quit' 退出): \n", currentPlayer);
            playerMove(currentPlayer);  // Player move
        } else if (currentMode == PVE_HUMAN_FIRST || currentPlayer == aiPlayer) {
            aiMove();  // AI move
        }

        innerLayoutToDisplayArray();  // Update display board
        displayBoard();  // Display board

        // Check if there is a winner
        if (checkWinner(1)) {
            printf("玩家 1 获胜！\n");
            break;
        } else if (checkWinner(2)) {
            printf("玩家 2 获胜！\n");
            break;
        }

        // Switch players
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }

    return 0;
}

// Initialize an empty board layout
void initRecordBorard(void) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            arrayForInnerBoardLayout[i][j] = 0;
        }
    }
}

// Convert internal board layout to display board
void innerLayoutToDisplayArray(void) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE * CHARSIZE + 1; j++) {
            arrayForDisplayBoard[i][j] = arrayForEmptyBoard[i][j];
        }
    }

    // Place pieces on the board
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (arrayForInnerBoardLayout[i][j] == 1) {
                arrayForDisplayBoard[i][CHARSIZE * j] = play1Pic[0];
                arrayForDisplayBoard[i][CHARSIZE * j + 1] = play1Pic[1];
            } else if (arrayForInnerBoardLayout[i][j] == 2) {
                arrayForDisplayBoard[i][CHARSIZE * j] = play2Pic[0];
                arrayForDisplayBoard[i][CHARSIZE * j + 1] = play2Pic[1];
            }
        }
    }
}

// Display the board
void displayBoard(void) {
    system("clear");  // Clear screen

    for (int i = 0; i < SIZE; i++) {
        printf("%3d %s\n", SIZE - i, arrayForDisplayBoard[i]);
    }

    printf("   ");
    for (int i = 0; i < SIZE; i++) {
        printf("%2c", 'A' + i);
    }
    printf("\n");
}

// Choose the game mode and who plays first
void chooseGameMode(void) {
    int modeChoice;
    printf("请选择游戏模式: \n");
    printf("1. 玩家对战 (PVP)\n");
    printf("2. 玩家对战 AI (人先)\n");
    printf("3. 玩家对战 AI (机先)\n");
    printf("请输入模式编号: ");
    scanf("%d", &modeChoice);

    switch (modeChoice) {
        case 1:
            currentMode = PVP;
            break;
        case 2:
            currentMode = PVE_HUMAN_FIRST;
            break;
        case 3:
            currentMode = PVE_AI_FIRST;
            break;
        default:
            printf("无效选择，默认为玩家对战。\n");
            currentMode = PVP;
    }

    // Set starting player based on the mode
    if (currentMode == PVE_AI_FIRST) {
        currentPlayer = aiPlayer;  // AI goes first
    } else {
        currentPlayer = 1;  // Player 1 goes first
    }
}

// Check if the position is valid
int isValidPosition(int row, int col) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        return 0;
    }
    if (arrayForInnerBoardLayout[row][col] != 0) {
        return 0;
    }
    return 1;
}

// Handle player move
void playerMove(int player) {
    char input[20];
    int row, col;
    char colChar;
    int validMove = 0;

    while (!validMove) {
        printf("请输入落子位置 (如:12h 或 h12)，输入 'quit' 退出: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';  // Remove newline

        // Quit game check
        if (strcmp(input, "quit") == 0) {
            exit(0);
        }

        // Parse input
        if (sscanf(input, "%d%c", &row, &colChar) == 2 || sscanf(input, "%c%d", &colChar, &row) == 2) {
            colChar = tolower(colChar);  // Handle both cases

            col = colChar - 'a';  // Convert letter to column index
            row = SIZE - row;  // Convert row number (from bottom)

            if (col < 0 || col >= SIZE || row < 0 || row >= SIZE) {
                printf("输入位置无效，请重新输入!\n");
            } else {
                validMove = isValidPosition(row, col);
            }
        }

        if (validMove) {
            arrayForInnerBoardLayout[row][col] = player;
        }
    }
}

// AI move: random placement
void aiMove(void) {
    printf("AI的回合：\n");

    // For simplicity, using a random move for AI
    int row, col;
    do {
        row = rand() % SIZE;  // Random row
        col = rand() % SIZE;  // Random column
    } while (!isValidPosition(row, col));  // Ensure the move is valid

    arrayForInnerBoardLayout[row][col] = aiPlayer;  // AI move
    printf("AI落子: %d%c\n", SIZE - row, 'A' + col);
}

// Check for a winner
int checkWinner(int player) {
    // Check horizontal, vertical, and diagonal lines for 5-in-a-row
    int count;
    
    // Horizontal check
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE - 4; j++) {
            count = 0;
            for (int k = 0; k < 5; k++) {
                if (arrayForInnerBoardLayout[i][j + k] == player) {
                    count++;
                }
            }
            if (count == 5) return 1;
        }
    }
    
    // Vertical check
    for (int i = 0; i < SIZE - 4; i++) {
        for (int j = 0; j < SIZE; j++) {
            count = 0;
            for (int k = 0; k < 5; k++) {
                if (arrayForInnerBoardLayout[i + k][j] == player) {
                    count++;
                }
            }
            if (count == 5) return 1;
        }
    }
    
    // Diagonal checks
    for (int i = 0; i < SIZE - 4; i++) {
        for (int j = 0; j < SIZE - 4; j++) {
            count = 0;
            for (int k = 0; k < 5; k++) {
                if (arrayForInnerBoardLayout[i + k][j + k] == player) {
                    count++;
                }
            }
            if (count == 5) return 1;
        }
    }
    
    for (int i = 4; i < SIZE; i++) {
        for (int j = 0; j < SIZE - 4; j++) {
            count = 0;
            for (int k = 0; k < 5; k++) {
                if (arrayForInnerBoardLayout[i - k][j + k] == player) {
                    count++;
                }
            }
            if (count == 5) return 1;
        }
    }
    
    return 0;
}
