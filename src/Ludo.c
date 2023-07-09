#include "../include/Ludo.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_PLAYERS 4
#define NUM_PIECES 4
#define START_POSITION -1



void build_board(Board* board) {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        for (int j = 0; j < NUM_PIECES; j++) {
            board->pieces[i][j].position = START_POSITION;
            board->pieces[i][j].safe = false;
        }
    }
}

void print_board(const Board* board) {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("Player %d:\n", i + 1);
        for (int j = 0; j < NUM_PIECES; j++) {
            printf("Piece %d: Position: %d\n", j + 1, board->pieces[i][j].position);
        }
        printf("\n");
    }
    printf("\n");
}

int roll_dice() {
    return rand() % 6 + 1;
}

bool valid_move(Board* board, Color player, int piece, int steps) {
    int currentPosition = board->pieces[player][piece].position;
    int newPosition = currentPosition + steps;

    // Se ele ganhou retorna true
    if (newPosition == 58)
        return true;

    //Se ele sair do tabuleiro retorna false
    if (newPosition > 58)
        return false;

    // Se for para um dos blocos de segurança retorna true
    if ((newPosition >= 52 && newPosition <= 57) || newPosition == 8 || newPosition == 21 || newPosition == 34 || newPosition == 47)
        return true;

    //Não pode estar em um local igual ao de outro jogador
    for (int i = 0; i < NUM_PLAYERS; i++) {
        for (int j = 0; j < NUM_PIECES; j++) {
            if (i != player && board->pieces[i][j].position == newPosition)
                return false;
        }
    }

    return true;
}

void move_piece(Board* board, Color player, int piece, int steps) {
    int currentPosition = board->pieces[player][piece].position;
    int newPosition;
    if(currentPosition == START_POSITION && steps == 6){
        newPosition = 0;
        board->pieces[player][piece].position = 0;
    }else if(currentPosition == START_POSITION && steps != 6){
        newPosition = START_POSITION;
        printf("Player %d Piece %d is still in the start position untill it rolls a 6!\n", player + 1, piece + 1);
        return;
    }else{
        newPosition = currentPosition + steps;
    }

    if (newPosition == 58) {
        printf("Player %d Piece %d reached the goal!\n", player + 1, piece + 1);
    } else if(currentPosition >= 52 && currentPosition <= 57){
        if(newPosition - 58 == 0){
            printf("Player %d Piece %d reached the goal!\n", player + 1, piece + 1);
            board->pieces[player][piece].position = newPosition;
            board->pieces[player][piece].safe = true;
        }else{
            int newPiece;
            do{
                printf("Invalid number. You need the exact number to reach the goal!\n");
                printf("Choose another piece number (1-4): ");
                scanf("%d", &newPiece);
                newPiece--; 
            }while(piece < 0 || piece >= NUM_PIECES);
            move_piece(board, player, newPiece, steps);
        }
    }else if ((newPosition >= 52 && newPosition <= 57) || newPosition == 8 || newPosition == 21 || newPosition == 34 || newPosition == 47) {
        printf("Player %d Piece %d reached a safe position %d!\n", player + 1, piece + 1, newPosition);
        board->pieces[player][piece].position = newPosition;
        board->pieces[player][piece].safe = true;
    } else {
        printf("Player %d Piece %d moved from position %d to %d\n", player + 1, piece + 1, currentPosition, newPosition);
        board->pieces[player][piece].position = newPosition;
    }
}

bool is_winner(const Board* board, Color player) {
    for (int i = 0; i < NUM_PIECES; i++) {
        if (board->pieces[player][i].position != 58)
            return false;
    }
    return true;
}