#ifndef ATAQUE_DANO_H_INCLUDED
#define ATAQUE_DANO_H_INCLUDED

#include "variaveis_globais.h"
#include "estruturas.h"

void DesenhaBalas(struct Balas balas);

void Knockback(int *x1, int *y1, int x2, int y2, int forca, int tolerancia, char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ]);

void Atirar(struct Player player, struct Balas balas, char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], int posX[], int posY[], char *dir);

void InicializaBalas(int posX[], int posY[], int *vel);

void AtualizaBalas(struct Balas balas, struct Monstros monstros, int posX[], int posY[], int monstrosPosX[], int monstrosPosY[], char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ]);



#endif // ATAQUE_DANO_H_INCLUDED
