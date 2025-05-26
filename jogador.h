#ifndef JOGADOR_H_INCLUDED
#define JOGADOR_H_INCLUDED
#include "variaveis_globais.h"

struct Player
{
    int posX, posY, tamanhoPersonagem, velocidadeMovimento, vidas;
    char dirMaisRecente, armaAtual;
    //Variável armaAtual:
    //P = pistola;
    //C = chicote.
    int balas;
    //Número de balas da pistola. Só é relevante quando o jogar está com a pistola.
};

void PosicionaJogadorInicialmente (char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], int *posX, int *posY);

void DesenhaJogador (struct Player player);

int Movimenta (char direcao, char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], int *posX, int *posY, int vel);

int DuasTeclas();

void DesenhaVidas(struct Player player);

int ColisaoVida(char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], struct Player player);

#endif // JOGADOR_H_INCLUDED
