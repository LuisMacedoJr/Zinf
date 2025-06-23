#ifndef JOGADOR_H_INCLUDED
#define JOGADOR_H_INCLUDED

#include <stdbool.h>
#include "variaveis_globais.h"
#include "estruturas.h"


//Funcoes relacionadas a inicializacao do jogador

void CriaPlayer (struct Player *player, struct Jogo jogo);

void PosicionaPlayerInicialmente (char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], struct Player *player);

//Funcoes relacionadas ao ciclo de movimentacao do player

void DesenhaJogador (struct Player *player, Texture2D playerTexture);

bool ChecaColisaoPlayerObstaculos (struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Player player, int numeroDeObstaculos, char direcao, char tipoObstaculo);

void MovimentaPlayer (char direcao, struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Player *player, int numeroDeObstaculos);

bool DuasTeclas();

//Funcoes de atualizacao de timer

void AtualizaTimerPlayer (struct Player *player);

void AtualizaTimerAnimacaoPlayer(struct Player *player);

void PlayerParado(struct Player *player);

#endif // JOGADOR_H_INCLUDED
