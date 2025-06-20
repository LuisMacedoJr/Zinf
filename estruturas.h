#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED

#include "raylib.h"

struct Monstro
{
    Rectangle hitbox;
    int vida, id, forca, score;
    float velocidadeMovimento, raioVisao, timerMovimento, distanciaPlayer, timerStun;
    char tipo; // 'M' = monstro, 'E' = vazio
    char orientacao; // 'U' = cima, 'D' = baixo, 'L' = esquerda, 'D' = direita
    char status; //'E' = esperando, 'M' = Movimentando, 'S' = Stun
    bool stun, vivo;
    float timerAnimacao, MonsterFPS;
    int contadorFrame;
};

struct Player
{
    Rectangle hitbox;
    int velocidadeMovimento, vidas, municao, timerStun, numeroDeBalasNaTela, timerTiro;
    char orientacao, armaAtual;
    bool stun, atirando, movendo;
    int score;
    float timerAnimacao, PlayerFPS;
    int contadorFrame;
    //Vari�vel armaAtual:
    //P = pistola;
    //C = chicote;
    //E = vazio.
    //N�mero de balas da pistola. S� � relevante quando o jogar est� com a pistola.
};

struct Bala {
    Rectangle hitbox;
    int velocidadeBala;
    char orientacao;
    bool ataque;
};

struct Obstaculo {
    Rectangle hitbox;
    char tipo;
};

struct Chicote {
    Rectangle hitbox;
    bool ataque;
};


#endif // ESTRUTURAS_H_INCLUDED
