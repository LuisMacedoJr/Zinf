#ifndef ATAQUE_DANO_H_INCLUDED
#define ATAQUE_DANO_H_INCLUDED

#include <stdbool.h>
#include "variaveis_globais.h"
#include "estruturas.h"

//Funcoes relacionadas ao ataque com chicote

void AtacaChicote(struct Player player, struct Chicote *chicote);

void DesenhaChicote(struct Chicote chicote, Texture2D chicoteAttackTexture);

bool ChecaColisaoChicoteMonstros (struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Chicote *chicote, int numeroDeMonstros, struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeObstaculos, struct Player *player);

void KnockbackMonstro(struct Chicote chicote, struct Monstro *monstro, struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeObstaculos, struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeMonstros, struct Player player);

//Funcao que movimenta o player em resposta ao dano

void KnockbackPlayer(struct Monstro monstro, struct Player *player, struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeObstaculos);

//Funcoes relacionadas ao ataque com pistola/bala

void CriaBalas(struct Bala balas[MAXIMODEBALAS]);

void Atira(struct Player *player, struct Bala balas[MAXIMODEBALAS]);

bool ChecaColisaoBalaObstaculos (struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Bala bala, int numeroDeObstaculos, char tipoObstaculo);

void MovimentaBala (char direcao, struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Bala *bala, int numeroDeObstaculos);

void AtualizaBalas(struct Bala balas[MAXIMODEBALAS], struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeObstaculos, struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeMonstros, struct Player *player);

bool ChecaColisaoBalaMonstros (struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Bala *bala, int numeroDeMonstros, struct Player *player);

void DesenhaBalas (struct Bala balas[MAXIMODEBALAS]);











//void Atirar(struct Player player, struct Balas balas, char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], int posX[], int posY[], char *dir);

//void InicializaBalas(int posX[], int posY[], int *vel);

//void AtualizaBalas(struct Balas balas, struct Monstro monstros, int posX[], int posY[], int monstrosPosX[], int monstrosPosY[], char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ]);



#endif // ATAQUE_DANO_H_INCLUDED
