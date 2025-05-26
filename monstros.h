#ifndef MONSTROS_H_INCLUDED
#define MONSTROS_H_INCLUDED

#include "variaveis_globais.h"
#include "jogador.h"

struct Monstros
{
    int quantidadeMonstros, posX[MAXMONSTROS], posY[MAXMONSTROS], enterrado[MAXMONSTROS], pontoX[MAXMONSTROS], pontoY[MAXMONSTROS], timerMovimento[MAXMONSTROS], ataqueStun[MAXMONSTROS];
    int velocidadeMovimento, raioVisao;
    float distPlayer[MAXMONSTROS];
};

void CriaMonstros(char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], int posX[], int posY[], int enterrado[], int timerMovimento[], int pontoX[], int pontoY[], int ataqueStun[], int *quantidadeMonstros);

float CalculaDist(int x1, int y1, int x2, int y2);

void DistMonstroPlayer(int posX[], int posY[], float distPlayer[], struct Player player, struct Monstros monstros);

int MonstroDeveMover(struct Monstros monstros, struct Player player, int i);

void DesenhaMonstros(struct Monstros monstros, struct Player player);

#endif // MONSTROS_H_INCLUDED
