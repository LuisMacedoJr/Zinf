#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

#include "variaveis_globais.h"
#include "estruturas.h"
#include "raylib.h"

//Funcoes relacionadas a leitura e desenho de mapa

void LeMapa(struct Jogo jogo, char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ]);

void CriaObstaculos (char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int *numeroDeObstaculos);

void CriaFeno(struct Feno fenos[]);

void DesenhaFeno(struct Feno feno[], Texture2D fenoTexture, int numeroDeFenos);

void AtualizaFeno(struct Feno feno[], int numeroDeFenos);

void DesenhaMapa(struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeObstaculos, Texture2D paredeTexture, Texture2D vidaTexture, Texture2D chicoteTexture, Texture2D balasTexture);

void AtualizaTimerAnimacaoVida(struct Obstaculo obstaculos[], int id);

void DesenhaChao(char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], Texture2D textureChao);

#endif // MAPA_H_INCLUDED
