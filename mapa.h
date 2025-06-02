#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

#include "variaveis_globais.h"
#include "estruturas.h"
#include "raylib.h"

void CriaObstaculos (char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int *numeroDeObstaculos);

void DesenhaMapa(struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeObstaculos);

#endif // MAPA_H_INCLUDED
