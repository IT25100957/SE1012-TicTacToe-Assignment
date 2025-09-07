#include <stdio.h>
#include <stdlib.h>

// Function declarations
void initializeBoard(char **board, int size);
void displayBoard(char **board, int size);

int main() {
    int size = 3;
    char **board;

    printf("Welcome to Tic-Tac-Toe!\n");
    printf("Board Size: %dx%d\n", size, size);

    // Allocate memory for the board
    board = malloc(size * sizeof(char *));
    for (int i = 0; i < size; i++) {
        board[i] = malloc(size * sizeof(char));
    }

    // Initialize board
    initializeBoard(board, size);

    // Simulate a move for testing
    board[0][1] = 'X'; // Place 'X' at row 0, column 1

    printf("\nPlayer 1 = X, Player 2 = O\n");
    printf("Game Board:\n");
    displayBoard(board, size);

    // Clean up memory
    for (int i = 0; i < size; i++) {
        free(board[i]);
    }
    free(board);

    printf("\nMemory cleaned up successfully.\n");

    return 0;
}

// Fill the board with spaces
void initializeBoard(char **board, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = ' ';
        }
    }
}

// Display the board in grid format
void displayBoard(char **board, int size) {
    // Column headers
    printf("  ");
    for (int col = 0; col < size; col++) {
        printf(" %d ", col);
    }
    printf("\n");

    for (int row = 0; row < size; row++) {
        printf("%d ", row);
        for (int col = 0; col < size; col++) {
            printf("|%c", board[row][col]);
        }
        printf("|\n");

        // Row separator (not after last row)
        if (row < size - 1) {
            printf("  ");
            for (int col = 0; col < size; col++) {
                printf("---");
            }
            printf("-\n");
        }
    }
}
