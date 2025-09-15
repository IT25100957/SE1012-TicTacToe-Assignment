#include <stdio.h>
#include <stdlib.h>

// Function declarations
void initializeBoard(char **board, int size);
void displayBoard(char **board, int size);
int BoardSize();
int MoveValidity(char **board, int size, int row, int col);
void makeMove(char **board, int size, int row, int col, char player);
int conditionWin(char **board, int size, char player);
int conditionDraw(char **board, int size);
void logMove(FILE *logFile, int moveNumber, int player, int row, int col);
void playGame(char **board, int size);
void instruct();

int main() {
    int n;
    char **board;
    int i;

    instruct();
    
    n = BoardSize();
    printf("Board Size: %dx%d\n", n, n);

    board = malloc(n * sizeof(char *));
    for (i = 0; i < n; i++) {
        board[i] = malloc(n * sizeof(char));
    }

    initializeBoard(board, n);
    playGame(board, n);

    for (i = 0; i < n; i++) {
        free(board[i]);
    }
    free(board);

    printf("\nDone.\n");
    return 0;
}

// initializing board
void initializeBoard(char **board, int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            board[i][j] = ' ';
        }
    }
}
// show board
void displayBoard(char **board, int size) {
    int i, j;
    printf("  ");
    for (j = 0; j < size; j++) {
        printf("%d ", j);
    }
    printf("\n");

    for (i = 0; i < size; i++) {
        printf("%d", i);
        for (j = 0; j < size; j++) {
            printf("|%c", board[i][j]);
        }
        printf("|\n");

        if (i < size - 1) {
        
            for (j = 0; j < size; j++) {
                printf("---");
            }
            printf("-\n");
        }
    }
}

// get board size
int BoardSize() {
    int n;
    printf("Enter board size (3-10): ");
    scanf("%d", &n);
    while(n < 3 || n > 10) {
        printf("Invalid! Enter 3-10: ");
        scanf("%d", &n);
    }
    return n;
}
// check move
int MoveValidity(char **board, int size, int row, int col) {
    if (row < 0 || row >= size || col < 0 || col >= size) {
        return 0;
    }
    if (board[row][col] != ' ') {
        return 0;
    }
    return 1;
}

// making move
void makeMove(char **board, int size, int row, int col, char player) {
    board[row][col] = player;
}

// check win
int conditionWin(char **board, int size, char player) {
    int i, j, count;
    
    // rows
    for (i = 0; i < size; i++) {
        count = 0;
        for (j = 0; j < size; j++) {
            if (board[i][j] == player) count++;
        }
        if (count == size) return 1;
    }
    
    // columns
    for (j = 0; j < size; j++) {
        count = 0;
        for (i = 0; i < size; i++) {
            if (board[i][j] == player) count++;
        }
        if (count == size) return 1;
    }
    
    // diagonal 1
    count = 0;
    for (i = 0; i < size; i++) {
        if (board[i][i] == player) count++;
    }
    if (count == size) return 1;
    
    // diagonal 2
    count = 0;
    for (i = 0; i < size; i++) {
        if (board[i][size-1-i] == player) count++;
    }
    if (count == size) return 1;
    
    return 0;
}

// check draw
int conditionDraw(char **board, int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (board[i][j] == ' ') return 0;
        }
    }
    return 1;
}

// log move
void logMove(FILE *logFile, int moveNumber, int player, int row, int col) {
    fprintf(logFile, "Move %d: Player %d (%c) at %d,%d\n", 
            moveNumber, player, (player == 1) ? 'X' : 'O', row, col);
}

// instructions
void instruct() {
    printf("========================================\n");
    printf("        WELCOME TO TIC-TAC-TOE!\n");
    printf("========================================\n");
    printf("HOW TO PLAY:\n");
    printf("- Player 1 = X, Player 2 = O\n");
    printf("- Take turns entering moves\n");
    printf("- Enter TWO numbers: row then column\n");
    printf("- Use 0-based indexing (0, 1, 2, etc.)\n");
    printf("- Example: Type '1 2' to place at row 1, column 2\n");
    printf("- First to get N in a row/column/diagonal wins!\n");
    printf("========================================\n\n");
}

// game loop
void playGame(char **board, int size) {
    FILE *fp = fopen("game_log.txt", "w");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    
    fprintf(fp, "Game Log\n");
    fprintf(fp, "Size: %dx%d\n", size, size);
    fprintf(fp, "P1=X, P2=O\n\n");
    
    int player = 1;
    int move = 1;
    int done = 0;
    int row, col;
    
    while (!done) {
        printf("\nBoard:\n");
        displayBoard(board, size);
        
        printf("\nPlayer %d (%c), enter your move (row column): ", player, (player == 1) ? 'X' : 'O');
        scanf("%d %d", &row, &col);
        
        if (MoveValidity(board, size, row, col)) {
            makeMove(board, size, row, col, (player == 1) ? 'X' : 'O');
            logMove(fp, move, player, row, col);
            
            if (conditionWin(board, size, (player == 1) ? 'X' : 'O')) {
                printf("\nFinal Board:\n");
                displayBoard(board, size);
                printf("\nPlayer %d wins!\n", player);
                fprintf(fp, "Player %d wins!\n", player);
                done = 1;
            }
            else if (conditionDraw(board, size)) {
                printf("\nFinal Board:\n");
                displayBoard(board, size);
                printf("\nDraw!\n");
                fprintf(fp, "Draw!\n");
                done = 1;
            }
            else {
                player = (player == 1) ? 2 : 1;
                move++;
            }
        }
        else {
            // Check what type of invalid move
            if (row < 0 || row >= size || col < 0 || col >= size) {
                printf("Error: Move out of bounds! Enter row and column between 0 and %d\n", size-1);
            }
            else if (board[row][col] != ' ') {
                printf("Error: Cell already occupied! Choose an empty cell\n");
            }
            
            printf("Try again!\n");
        }
    }
    
    fclose(fp);
    printf("\nGame saved to game_log.txt\n");
}
