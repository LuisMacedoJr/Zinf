#ifndef ATAQUE_DANO_H_INCLUDED
#define ATAQUE_DANO_H_INCLUDED

#include "variaveis_globais.h"
#include "estruturas.h"

void DesenhaBalas(struct Balas balas);

void Knockback(struct Monstro monstro, struct Player *player, struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeObstaculos);

void Atirar(struct Player player, struct Balas balas, char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], int posX[], int posY[], char *dir);

void InicializaBalas(int posX[], int posY[], int *vel);

void AtualizaBalas(struct Balas balas, struct Monstro monstros, int posX[], int posY[], int monstrosPosX[], int monstrosPosY[], char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ]);



#endif // ATAQUE_DANO_H_INCLUDED
