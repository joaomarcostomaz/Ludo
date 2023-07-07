#ifndef Ludo_H
#define Ludo_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_PLAYERS 4
#define NUM_PIECES 4
#define START_POSITION -1

typedef enum { RED, YELLOW, GREEN, BLUE } Color;

typedef struct {
    int position;
    bool safe;
} Piece;

typedef struct {
    Piece pieces[NUM_PLAYERS][NUM_PIECES];
} Board;

void build_board(Board *board);
void print_board(const Board *board);
int roll_dice();
void move_piece(Board *board, Color color, int piece, int roll);
bool is_winner(const Board *board, Color color);
bool valid_move(Board *board, Color color, int piece, int roll);




#endif // Ludo_H