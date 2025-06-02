#ifndef JOGADOR_H_INCLUDED
#define JOGADOR_H_INCLUDED

#include <stdbool.h>
#include "variaveis_globais.h"
#include "estruturas.h"

void CriaPlayer (struct Player *player);

void PosicionaPlayerInicialmente (char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], struct Player *player);

void DesenhaJogador (struct Player player);

bool ChecaColisaoPlayerObstaculos (struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Player player, int numeroDeObstaculos, char direcao, char tipoObstaculo);

void MovimentaPlayer (char direcao, struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Player *player, int numeroDeObstaculos);

bool DuasTeclas();

void DesenhaVidas(struct Player player);

#endif // JOGADOR_H_INCLUDED
