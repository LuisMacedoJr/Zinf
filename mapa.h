#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

#include "variaveis_globais.h"
#include "estruturas.h"
#include "raylib.h"

void LeMapa(struct Jogo jogo, char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ]);

void CriaObstaculos (char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int *numeroDeObstaculos);

void DesenhaMapa(struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeObstaculos);

void DesenhaChao(char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], Texture2D textureChao);

#endif // MAPA_H_INCLUDED
