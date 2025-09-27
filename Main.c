/*
 * Tic-Tac-Toe Game
 * Customizable board size (3x3 to 10x10)
 * Logs all moves to game_log.txt
 */

#include "tictactoe.h"

int main() {
    int n;
    char **board;
    int i;
    int gameMode;

    instruct();
    
    n = BoardSize();
    printf("Board Size: %dx%d\n", n, n);
    
    gameMode = selectGameMode();

    // Allocate memory for 2D board
    board = malloc(n * sizeof(char *));
    for (i = 0; i < n; i++) {
        board[i] = malloc(n * sizeof(char));
    }

    initializeBoard(board, n);
    playGame(board, n, gameMode);

    // Free memory
    for (i = 0; i < n; i++) {
        free(board[i]);
    }
    free(board);

    printf("\nDone.\n");
    return 0;
}

/*
 * Initialize board with empty spaces
 */
void initializeBoard(char **board, int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            board[i][j] = ' ';
        }
    }
}
/*
 * Display the current board state
 */
void displayBoard(char **board, int size) {
    int i, j;
    
    // Print column numbers
    printf("  ");
    for (j = 0; j < size; j++) {
        printf("%d ", j);
    }
    printf("\n");

    // Print rows with separators
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

/*
 * Get board size from user (3-10)
 */
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
/*
 * Check if move is valid (in bounds and empty)
 */
int MoveValidity(char **board, int size, int row, int col) {
    // Check bounds
    if (row < 0 || row >= size || col < 0 || col >= size) {
        return 0;
    }
    // Check if cell is empty
    if (board[row][col] != ' ') {
        return 0;
    }
    return 1;
}

/*
 * Place player's mark on the board
 */
void makeMove(char **board, int size, int row, int col, char player) {
    board[row][col] = player;
}

/*
 * Check if player has won (N in a row/column/diagonal)
 */
int conditionWin(char **board, int size, char player) {
    int i, j, count;
    
    // Check rows
    for (i = 0; i < size; i++) {
        count = 0;
        for (j = 0; j < size; j++) {
            if (board[i][j] == player) count++;
        }
        if (count == size) return 1;
    }
    
    // Check columns
    for (j = 0; j < size; j++) {
        count = 0;
        for (i = 0; i < size; i++) {
            if (board[i][j] == player) count++;
        }
        if (count == size) return 1;
    }
    
    // Check main diagonal
    count = 0;
    for (i = 0; i < size; i++) {
        if (board[i][i] == player) count++;
    }
    if (count == size) return 1;
    
    // Check anti-diagonal
    count = 0;
    for (i = 0; i < size; i++) {
        if (board[i][size-1-i] == player) count++;
    }
    if (count == size) return 1;
    
    return 0;
}

/*
 * Check if game is a draw (board full)
 */
int conditionDraw(char **board, int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (board[i][j] == ' ') return 0;
        }
    }
    return 1;
}

/*
 * Log move and board state to file
 */
void logMove(FILE *logFile, int moveNumber, int player, int row, int col, char **board, int size) {
    fprintf(logFile, "Move %d: Player %d (%c) at %d,%d\n", 
            moveNumber, player, (player == 1) ? 'X' : 'O', row, col);
    
    // Print board state
    fprintf(logFile, "Board state:\n");
    fprintf(logFile, "  ");
    for (int j = 0; j < size; j++) {
        fprintf(logFile, "%d ", j);
    }
    fprintf(logFile, "\n");

    for (int i = 0; i < size; i++) {
        fprintf(logFile, "%d", i);
        for (int j = 0; j < size; j++) {
            fprintf(logFile, "|%c", board[i][j]);
        }
        fprintf(logFile, "|\n");

        if (i < size - 1) {
            for (int j = 0; j < size; j++) {
                fprintf(logFile, "---");
            }
            fprintf(logFile, "-\n");
        }
    }
    fprintf(logFile, "\n");
}

/*
 * Display game instructions
 */
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

/*
 * Select game mode (Two Players or User vs Computer)
 */
int selectGameMode() {
    int choice;
    printf("Select Game Mode:\n");
    printf("1. Two Players (User vs User)\n");
    printf("2. User vs Computer\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);
    
    while (choice != 1 && choice != 2) {
        printf("Invalid choice! Please enter 1 or 2: ");
        scanf("%d", &choice);
    }
    
    if (choice == 1) {
        printf("Selected: Two Players (User vs User)\n");
    } else {
        printf("Selected: User vs Computer\n");
    }
    
    return choice;
}

/*
 * Generate random computer move
 */
void generateComputerMove(char **board, int size, int *row, int *col) {
    int validMoves = 0;
    int i, j;
    
    // Count valid moves
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (board[i][j] == ' ') {
                validMoves++;
            }
        }
    }
    
    if (validMoves == 0) {
        *row = -1;
        *col = -1;
        return;
    }
    
    // Generate random number between 1 and validMoves
    int randomMove = (rand() % validMoves) + 1;
    
    // Find the randomMove-th valid position
    int currentMove = 0;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (board[i][j] == ' ') {
                currentMove++;
                if (currentMove == randomMove) {
                    *row = i;
                    *col = j;
                    return;
                }
            }
        }
    }
}

/*
 * Main game loop
 */
void playGame(char **board, int size, int gameMode) {
    FILE *fp = fopen("game_log.txt", "w");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    
    fprintf(fp, "Game Log\n");
    fprintf(fp, "Size: %dx%d\n", size, size);
    if (gameMode == 1) {
        fprintf(fp, "Mode: Two Players (User vs User)\n");
        fprintf(fp, "P1=X, P2=O\n\n");
    } else {
        fprintf(fp, "Mode: User vs Computer\n");
        fprintf(fp, "User=X, Computer=O\n\n");
    }
    
    int player = 1;
    int move = 1;
    int done = 0;
    int row, col;
    
    // Initialize random seed for computer moves
    srand(time(NULL));
    
    while (!done) {
        printf("\nBoard:\n");
        displayBoard(board, size);
        
        if (gameMode == 1 || player == 1) {
            // Human player move
            printf("\nPlayer %d (%c), enter your move (row column): ", player, (player == 1) ? 'X' : 'O');
            scanf("%d %d", &row, &col);
        } else {
            // Computer move
            printf("\nComputer (%c) is thinking...\n", 'O');
            generateComputerMove(board, size, &row, &col);
            printf("Computer chooses: %d %d\n", row, col);
        }
        
        if (MoveValidity(board, size, row, col)) {
            makeMove(board, size, row, col, (player == 1) ? 'X' : 'O');
            logMove(fp, move, player, row, col, board, size);
            
            if (conditionWin(board, size, (player == 1) ? 'X' : 'O')) {
                printf("\nFinal Board:\n");
                displayBoard(board, size);
                if (gameMode == 1) {
                    printf("\nPlayer %d wins!\n", player);
                    fprintf(fp, "Player %d wins!\n", player);
                } else {
                    if (player == 1) {
                        printf("\nYou win!\n");
                        fprintf(fp, "User wins!\n");
                    } else {
                        printf("\nComputer wins!\n");
                        fprintf(fp, "Computer wins!\n");
                    }
                }
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
            // Handle invalid moves (only for human players)
            if (gameMode == 1 || player == 1) {
                if (row < 0 || row >= size || col < 0 || col >= size) {
                    printf("Error: Move out of bounds! Enter row and column between 0 and %d\n", size-1);
                }
                else if (board[row][col] != ' ') {
                    printf("Error: Cell already occupied! Choose an empty cell\n");
                }
                
                printf("Try again!\n");
            }
        }
    }
    
    fclose(fp);
    printf("\nGame saved to game_log.txt\n");
}
