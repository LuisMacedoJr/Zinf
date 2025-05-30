#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED

#include "raylib.h"

struct Monstros
{
    int quantidadeMonstros, posX[MAXMONSTROS], posY[MAXMONSTROS], enterrado[MAXMONSTROS], pontoX[MAXMONSTROS], pontoY[MAXMONSTROS], timerMovimento[MAXMONSTROS], ataqueStun[MAXMONSTROS];
    int velocidadeMovimento, raioVisao;
    float distPlayer[MAXMONSTROS];
};

struct Player
{
    Rectangle hitbox;
    int posX, posY, tamanhoPersonagem, velocidadeMovimento, vidas;
    char orientacao, armaAtual;
    //Variável armaAtual:
    //P = pistola;
    //C = chicote.
    int balas;
    //Número de balas da pistola. Só é relevante quando o jogar está com a pistola.
};

struct Balas {
    int posX[MAXBALAS], posY[MAXBALAS], balaVel;
    char direcao;
};

struct Obstaculo {
    Rectangle hitbox;
    char tipo;
};


#endif // ESTRUTURAS_H_INCLUDED
