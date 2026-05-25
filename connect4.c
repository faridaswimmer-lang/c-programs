#include <stdio.h>

// using function prototypes

#define ROWS 6
#define COLS 7
#define NAME_LEN 50


typedef struct {
    char name[NAME_LEN];
    char symbol;
} Player;


void initializeBoard(char board[ROWS][COLS]);
void printBoard(char board[ROWS][COLS]);
int dropDisc(char board[ROWS][COLS], int col, char symbol);
int isWinningMove(char board[ROWS][COLS], char symbol);
int isBoardFull(char board[ROWS][COLS]);
void switchPlayer(int *currentPlayer);


int main() {
    char board[ROWS][COLS];
    Player players[2];
    int currentPlayer = 0;
    int col;

    /* Player setup */
    printf("Enter Player 1 name: ");
    scanf("%s", players[0].name);
    players[0].symbol = 'X';

    printf("Enter Player 2 name: ");
    scanf("%s", players[1].name);
    players[1].symbol = 'O';

    initializeBoard(board);

    while (1) {
        printBoard(board);

        printf("%s (%c), choose column (1-7): ",
               players[currentPlayer].name,
               players[currentPlayer].symbol);

        if (scanf("%d", &col) != 1) {
            printf("Invalid input! Try again.\n");
            while (getchar() != '\n'); // clear buffer
            continue;
        }

        col--; // convert to 0-based

        if (col < 0 || col >= COLS || !dropDisc(board, col, players[currentPlayer].symbol)) {
            printf("Invalid move! Try again.\n");
            continue;
        }

        /* Check win */
        if (isWinningMove(board, players[currentPlayer].symbol)) {
            printBoard(board);
            printf("🎉 %s wins!\n", players[currentPlayer].name);
            break;
        }

        /* Check draw */
        if (isBoardFull(board)) {
            printBoard(board);
            printf("It's a draw!\n");
            break;
        }

        switchPlayer(&currentPlayer);
    }

    return 0;
}


void initializeBoard(char board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            board[i][j] = '.';
}


void printBoard(char board[ROWS][COLS]) {
    printf("\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("1 2 3 4 5 6 7\n\n");
}


int dropDisc(char board[ROWS][COLS], int col, char symbol) {
    for (int i = ROWS - 1; i >= 0; i--) {
        if (board[i][col] == '.') {
            board[i][col] = symbol;
            return 1;
        }
    }
    return 0; // column full
}


int isWinningMove(char board[ROWS][COLS], char symbol) {

    /* Horizontal */
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS - 3; j++)
            if (board[i][j] == symbol &&
                board[i][j+1] == symbol &&
                board[i][j+2] == symbol &&
                board[i][j+3] == symbol)
                return 1;

    /* Vertical */
    for (int i = 0; i < ROWS - 3; i++)
        for (int j = 0; j < COLS; j++)
            if (board[i][j] == symbol &&
                board[i+1][j] == symbol &&
                board[i+2][j] == symbol &&
                board[i+3][j] == symbol)
                return 1;

    /* Diagonal ↘️ */
    for (int i = 0; i < ROWS - 3; i++)
        for (int j = 0; j < COLS - 3; j++)
            if (board[i][j] == symbol &&
                board[i+1][j+1] == symbol &&
                board[i+2][j+2] == symbol &&
                board[i+3][j+3] == symbol)
                return 1;

    /* Diagonal ↗️ */
    for (int i = 3; i < ROWS; i++)
        for (int j = 0; j < COLS - 3; j++)
            if (board[i][j] == symbol &&
                board[i-1][j+1] == symbol &&
                board[i-2][j+2] == symbol &&
                board[i-3][j+3] == symbol)
                return 1;

    return 0;
}


int isBoardFull(char board[ROWS][COLS]) {
    for (int j = 0; j < COLS; j++)
        if (board[0][j] == '.')
            return 0;
    return 1;
}


void switchPlayer(int *currentPlayer) {
    *currentPlayer = 1 - *currentPlayer;
}