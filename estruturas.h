#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED

#include "raylib.h"

struct Monstro
{
    Rectangle hitbox;
    int vida;
    int quantidadeMonstros, posX[MAXMONSTROS], posY[MAXMONSTROS], enterrado[MAXMONSTROS], pontoX[MAXMONSTROS], pontoY[MAXMONSTROS], timerMovimento, ataqueStun[MAXMONSTROS];
    int velocidadeMovimento, raioVisao;
    char tipo;
    char orientacao;
    int forca;
    float distanciaPlayer;
};

struct Player
{
    Rectangle hitbox;
    int posX, posY, tamanhoPersonagem, velocidadeMovimento, vidas;
    char orientacao, armaAtual;
    //Vari�vel armaAtual:
    //P = pistola;
    //C = chicote.
    int balas;
    //N�mero de balas da pistola. S� � relevante quando o jogar est� com a pistola.
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
