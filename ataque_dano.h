#ifndef ATAQUE_DANO_H_INCLUDED
#define ATAQUE_DANO_H_INCLUDED

#include <stdbool.h>
#include "variaveis_globais.h"
#include "estruturas.h"

void AtacaChicote(struct Player player, struct Chicote *chicote);

void DesenhaChicote(struct Chicote chicote);

bool ChecaColisaoChicoteMonstros (struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Chicote *chicote, int numeroDeMonstros, struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeObstaculos, struct Player player);

//void DesenhaBalas(struct Balas balas);

void KnockbackMonstro(struct Chicote chicote, struct Monstro *monstro, struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeObstaculos, struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeMonstros, struct Player player);

void KnockbackPlayer(struct Monstro monstro, struct Player *player, struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeObstaculos);

//void Atirar(struct Player player, struct Balas balas, char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], int posX[], int posY[], char *dir);

//void InicializaBalas(int posX[], int posY[], int *vel);

//void AtualizaBalas(struct Balas balas, struct Monstro monstros, int posX[], int posY[], int monstrosPosX[], int monstrosPosY[], char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ]);



#endif // ATAQUE_DANO_H_INCLUDED
