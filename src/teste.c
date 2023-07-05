#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define NUM_PLAYERS 4
#define NUM_PIECES 4
#define BOARD_SIZE 52
#define START_POSITION -1
#define GOAL_POSITION (BOARD_SIZE - 1)
#define SAFE_POSITION_1 5
#define SAFE_POSITION_2 18
#define SAFE_POSITION_3 31
#define SAFE_POSITION_4 44

typedef enum { RED, YELLOW, GREEN, BLUE } Color;

typedef struct {
    int position;
    bool safe;
} Piece;

typedef struct {
    Piece pieces[NUM_PLAYERS][NUM_PIECES];
} Board;

void initializeBoard(Board* board) {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        for (int j = 0; j < NUM_PIECES; j++) {
            board->pieces[i][j].position = START_POSITION;
            board->pieces[i][j].safe = false;
        }
    }
}

void displayBoard(const Board* board) {
    printf("=======================\n");
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("Player %d:\n", i + 1);
        for (int j = 0; j < NUM_PIECES; j++) {
            printf("Piece %d: Position: %d\n", j + 1, board->pieces[i][j].position);
        }
        printf("-----------------------\n");
    }
    printf("=======================\n");
}

int rollDice() {
    return rand() % 6 + 1;
}

bool isValidMove(Board* board, Color player, int piece, int steps) {
    int currentPosition = board->pieces[player][piece].position;
    int newPosition;
    if(currentPosition == START_POSITION && steps != 6)
        return false;
    if(currentPosition == START_POSITION && steps == 6){
        int newPosition = 0;
        board->pieces[player][piece].position = 0;
    }else{
        int newPosition = currentPosition + steps;
    }

    if (newPosition == GOAL_POSITION)
        return true;

    if (newPosition > GOAL_POSITION)
        return false;

    if (currentPosition < START_POSITION && newPosition >= START_POSITION)
        return false;

    if (newPosition == SAFE_POSITION_1 || newPosition == SAFE_POSITION_2 || newPosition == SAFE_POSITION_3 || newPosition == SAFE_POSITION_4)
        return true;

    for (int i = 0; i < NUM_PLAYERS; i++) {
        for (int j = 0; j < NUM_PIECES; j++) {
            if (i != player && board->pieces[i][j].position == newPosition)
                return false;
        }
    }

    return true;
}

void movePiece(Board* board, Color player, int piece, int steps) {
    int currentPosition = board->pieces[player][piece].position;
    int newPosition;
    if(currentPosition == 0){
        newPosition = currentPosition + steps;
    }else{
        newPosition = 0;
    }

    if (newPosition == GOAL_POSITION) {
        printf("Player %d Piece %d reached the goal!\n", player + 1, piece + 1);
    } else if (newPosition == SAFE_POSITION_1 || newPosition == SAFE_POSITION_2 || newPosition == SAFE_POSITION_3 || newPosition == SAFE_POSITION_4) {
        printf("Player %d Piece %d reached a safe position %d!\n", player + 1, piece + 1, newPosition);
        board->pieces[player][piece].position = newPosition;
        board->pieces[player][piece].safe = true;
    } else {
        printf("Player %d Piece %d moved from position %d to %d\n", player + 1, piece + 1, currentPosition, newPosition);
        board->pieces[player][piece].position = newPosition;
    }
}

bool hasWon(const Board* board, Color player) {
    for (int i = 0; i < NUM_PIECES; i++) {
        if (board->pieces[player][i].position != GOAL_POSITION)
            return false;
    }
    return true;
}

int main() {
    srand(time(NULL));

    Board board;
    initializeBoard(&board);

    Color currentPlayer = RED;

    while (true) {
        displayBoard(&board);

        printf("Player %d's turn\n", currentPlayer + 1);

        int piece;
        do {
            printf("Enter piece number (1-4): ");
            scanf("%d", &piece);
            piece--; // Adjusting for zero-based indexing
        } while (piece < 0 || piece >= NUM_PIECES);

        int steps = rollDice();
        printf("You rolled a %d\n", steps);

        if (isValidMove(&board, currentPlayer, piece, steps)) {
            movePiece(&board, currentPlayer, piece, steps);

            if (hasWon(&board, currentPlayer)) {
                printf("Player %d has won the game!\n", currentPlayer + 1);
                break;
            }

            currentPlayer = (currentPlayer + 1) % NUM_PLAYERS;
        } else {
            printf("Invalid move, try again next time\n");
            currentPlayer = (currentPlayer + 1) % NUM_PLAYERS;
        }

        printf("\n");
    }

    return 0;
}
