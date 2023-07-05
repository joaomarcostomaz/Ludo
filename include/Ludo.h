#ifndef Ludo_H
#define Ludo_H


#include <stdio.h>
#include <stdlib.h>

typedef struct casa {
    int x;
    int y;
    int valor;
    int color;
    int ocupado;
}casa;

typedef struct base{
    int posicion_x, position_y;
}base;

typedef struct position{
    int posicion_x, position_y;
}position;

typedef struct Pawn{
    position init, chegada,current;
    base b;
    int color;
}Pawn;

typedef struct Player{
    Pawn pawns[4];
    int color;
}Player;

typedef struct Game{
    Player players[4];
    int dice;
    int turn;
    int winner;
    casa** board;
}Game;

casa** build_board();
void setbases(Pawn* pawns, int& j, int&);
void rollDice(int& dice);
int get max(int* vector);
int star_game(int numPlayers);
int play_turn(Game* game, int player, int pawn, int dice);
void play_game(Game* game, int numPlayers);




#endif // Ludo_H