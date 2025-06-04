#ifndef MONSTROS_H_INCLUDED
#define MONSTROS_H_INCLUDED

#include <stdbool.h>
#include "variaveis_globais.h"
#include "jogador.h"
#include "estruturas.h"

void CriaMonstros(char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int *numeroDeMonstros);

float CalculaDistanciaEntreDoisPontos(float x1, float y1, float x2, float y2);

void CalculaDistanciaMonstroPlayer(struct Monstro *monstro, struct Player player);

void AtualizaDistanciaMonstroPlayer (struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Player player, int numeroDeMonstros);

bool MonstroNoRaioDeVisao(struct Monstro monstros, struct Player player);

bool ChecaColisaoPlayerMonstros (struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Player *player, int numeroDeMonstros, struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeObstaculos);

bool ChecaColisaoMonstroObstaculos (struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Monstro monstro, int numeroDeObstaculos, char direcao, char tipoObstaculo);

bool ChecaColisaoEntreMonstros (struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Monstro monstro, int numeroDeMonstros);

void MovimentaMonstro (char direcao, struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Monstro *monstro, int numeroDeObstaculos, struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeMonstros);

void DesenhaMonstros(struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeMonstros);

void MovimentoAutomaticoMonstros(struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeMonstros, struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeObstaculos);

void AtualizaTimerMonstros(struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeMonstros);

void AtualizaStatusMonstros(struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeMonstros, struct Player player);

char SorteiaDirecao(struct Monstro monstro, struct Player player);

void AtualizaNumeroDeMonstrosVivos(struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeMonstros, int *numeroDeMonstrosVivos);





//void DesenhaMonstros(struct Monstro monstros, struct Player player);

//void CriaMonstros(char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], int posX[], int posY[], int enterrado[], int timerMovimento[], int pontoX[], int pontoY[], int ataqueStun[], int *quantidadeMonstros);

//void DistanciaMonstroPlayer(int posX[], int posY[], float distPlayer[], struct Player player, struct Monstro monstros);


#endif // MONSTROS_H_INCLUDED
