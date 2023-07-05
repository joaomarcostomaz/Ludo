#include "../include/Ludo.h"
#include <stdio.h>

casa** build_board(){
    int i, j;
    casa** vector = (casa**)malloc(15*sizeof(casa*));
    for(i = 0; i < 15; i++){
        vector[i] = (casa*)malloc(15*sizeof(casa));
        for(j = 0; j < 15; j++){
            if(((i == 6)|| (j == 6))||((i == 7) || (j == 7)) || ((i == 8) || (j == 8))){
                vector[i][j].x = i;
                vector[i][j].y = j;
                vector[i][j].valor = 1;
                vector[i][j].ocupado = 0;
            } else {
                if(((i < 7)&&(j < 7))){
                    vector[i][j].color = 1;
                } else if(((i < 7)&&(j > 9))){
                    vector[i][j].color = 2;
                } else if(((i > 9)&&(j < 7))){
                    vector[i][j].color = 3;
                } else if(((i > 9)&&(j > 9))){
                    vector[i][j].color = 4;
                } else {
                    vector[i][j].color = 0;
                }
                vector[i][j].x = i;
                vector[i][j].y = j;
                vector[i][j].valor = 0;
                vector[i][j].ocupado = 1;
            }
        }
    }
    return vector;
}
void setbases(Pawn* pawns, int& j, int& k){
    for(int i = 0; i < 4; i++){
        pawns[i].b.posicion_x = j;
        pawns[i].b.posicion_y = k;
        pawns[i].b.color = i+1;
        
    }
}

void rollDice(int& dice){
    dice = rand()%6 + 1;
}

int get_max(int* vector){
    int max = 0;
    for(int i = 0; i < 4; i++){
        if(vector[i] > max){
            max = vector[i];
        }
    }
    return max;
}

int start_game(int numPlayers){
    int vector[4] = {0, 0, 0, 0};
    int dice = 0;
    for(int i = 0; i < numPlayers; i++){
        rollDice(dice);
        vector[i] = dice;
    }
    int max = get_max(vector);
    for(int i = 0; i < numPlayers; i++){
        if(vector[i] == max){
            return i;
        }
    }
}

int play_turn(Game* Game,int player, int pawn, int dice){
    if(dice == 6 && Game->players[player].pawns[pawn].current.posicion_x == Game->players[player].pawns[pawn].position.init.position_x){
        switch(Game->players[player].pawns[pawn].color){
            case 1:
                Game->players[player].pawns[pawn].current.posicion_x = 2;
                Game->players[player].pawns[pawn].current.position_y = 6;
                break;
            case 2:
                Game->players[player].pawns[pawn].current.posicion_x = 8;
                Game->players[player].pawns[pawn].current.position_y = 2;
                break;
            case 3:
                Game->players[player].pawns[pawn].current.posicion_x = 12;
                Game->players[player].pawns[pawn].current.position_y = 8;
                break;
            case 4:
                Game->players[player].pawns[pawn].current.posicion_x = 5;
                Game->players[player].pawns[pawn].current.position_y = 12;
                break;
        }
    }else if(dice == 6 && Game->players[player].pawns[pawn].current.posicion_x != Game->players[player].pawns[pawn].b.position_x){
        switch(Game->players[player].pawns[pawn].color){
            case 1:
                Game->players[player].pawns[pawn].current.posicion_x+= dice;
                if((Game->players[player].pawns[pawn].current.posicion_x > 5)&& (Game->players[player].pawns[pawn].current.posicion_y < 6)){
                    Game->players[player].pawns[pawn].current.posicion_x = 6;
                    
                }
        }
    }

}