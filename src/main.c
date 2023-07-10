#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "Ludo.h"

#define NUM_PLAYERS 4
#define NUM_PIECES 4
#define START_POSITION -1

int main(){
    srand(time(NULL));

    Board board;
    build_board(&board);

    Color currentPlayer = RED;

    // Game loop
    while (true) {
        print_board(&board);

        printf("Player %d's turn\n", currentPlayer + 1);

        int piece;
        do {
            printf("Enter piece number (1-4): ");
            scanf("%d", &piece);
            piece--; // Adjusting for zero-based indexing
        } while (piece < 0 || piece >= NUM_PIECES);

        int steps = roll_dice();
        printf("You rolled a %d\n", steps);
        int current6 = 0;

        if (valid_move(&board, currentPlayer, piece, steps)) {
            //Se o jogador tirar 6, ele joga novamente
            if(steps == 6){
                current6++;
            }
            move_piece(&board, currentPlayer, piece, steps);

            //Se o jogador ganhar, o jogo acaba
            if (is_winner(&board, currentPlayer)) {
                printf("Player %d has won the game!\n", currentPlayer + 1);
                break;
            }
            //Se o jogador tirar 6, ele joga novamente, porém no máximo 2 vezes.
            //O 3º 6 não é válido
            while(current6 > 0){
                if(current6 == 3)
                    break;
                
                printf("Player %d rolled a 6, roll again!\n", currentPlayer + 1);
                int piece;
                do {
                    printf("Enter piece number (1-4): ");
                    scanf("%d", &piece);
                    piece--; // Adjusting for zero-based indexing
                } while (piece < 0 || piece >= NUM_PIECES);

                int steps = roll_dice();
                printf("You rolled a %d\n", steps);
                if (valid_move(&board, currentPlayer, piece, steps)) {
                    if(steps == 6){
                        current6++;
                    }
                    move_piece(&board, currentPlayer, piece, steps);

                    if (is_winner(&board, currentPlayer)) {
                        printf("Player %d has won the game!\n", currentPlayer + 1);
                        break;
                    }
                } else {
                    printf("Invalid move, try again next time\n");
                }
                current6--;
            }
        //Passa a vez do jogador
        currentPlayer = (currentPlayer + 1) % NUM_PLAYERS;   
        } else {
            //Caso o movimento não seja válido, apenas passa a vez
            printf("Invalid move, try again next time\n");
            currentPlayer = (currentPlayer + 1) % NUM_PLAYERS;
        }
    

        printf("\n");
    }

    return 0;
}