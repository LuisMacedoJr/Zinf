#include <stdio.h>
#include <stdbool.h>

#include "raylib.h"
#include "variaveis_globais.h"
#include "mapa.h"

void LeMapa(struct Jogo jogo, char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ])
{
    char nomeDoArquivo[20] = {"mapas/mapa00.txt"};
    char caractereAtual;
    int i, j;
    FILE *arquivoMapa;


    if (jogo.nivel < 10)
    {
        nomeDoArquivo[10] = '0';
        nomeDoArquivo[11] = jogo.nivel + '0';
    }
    else
    {
        nomeDoArquivo[10] = jogo.nivel / 10 + '0';
        nomeDoArquivo[11] = jogo.nivel % 10 + '0';
    }

    arquivoMapa = fopen(nomeDoArquivo, "r");


    for (i = 0; i < ALTURA/CELULAMATRIZ; i++)
    {
        for(j = 0; j < LARGURA/CELULAMATRIZ; j++)
        {
            do{
            caractereAtual = fgetc(arquivoMapa);
            } while (caractereAtual == '\r' || caractereAtual == '\n');
            mapa[i][j] = caractereAtual;
        }
    }

}


//Funcao que dada uma matriz mapa, preenche um array de obstaculos. P para parede, V para vida
void CriaObstaculos (char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int *numeroDeObstaculos)
{
    char *p;
    int posX, posY;
    *numeroDeObstaculos = 0;

    for(p = &mapa[0][0]; p <= &mapa[(ALTURA/CELULAMATRIZ) - 1][(LARGURA/CELULAMATRIZ) - 1]; p++)
    {
        if (*p == 'P')
        {
            posX = ((p - &mapa[0][0]) % (LARGURA/CELULAMATRIZ))*CELULAMATRIZ;
            posY = ((p - &mapa[0][0]) / (LARGURA/CELULAMATRIZ))*CELULAMATRIZ + ALTURABARRASTATUS;

            obstaculos[*numeroDeObstaculos].hitbox.x = posX;
            obstaculos[*numeroDeObstaculos].hitbox.y = posY;
            obstaculos[*numeroDeObstaculos].hitbox.width = CELULAMATRIZ;
            obstaculos[*numeroDeObstaculos].hitbox.height = CELULAMATRIZ;
            obstaculos[*numeroDeObstaculos].tipo = 'P';

            *numeroDeObstaculos += 1;

        }
        if (*p == 'V')
        {
            posX = ((p - &mapa[0][0]) % (LARGURA/CELULAMATRIZ))*CELULAMATRIZ;
            posY = ((p - &mapa[0][0]) / (LARGURA/CELULAMATRIZ))*CELULAMATRIZ + ALTURABARRASTATUS;

            obstaculos[*numeroDeObstaculos].hitbox.x = posX;
            obstaculos[*numeroDeObstaculos].hitbox.y = posY;
            obstaculos[*numeroDeObstaculos].hitbox.width = CELULAMATRIZ;
            obstaculos[*numeroDeObstaculos].hitbox.height = CELULAMATRIZ;
            obstaculos[*numeroDeObstaculos].tipo = 'V';


            *numeroDeObstaculos += 1;

        }
    }

}

//Desenha o mapa de acordo com o array de obstaculos previamente preenchido
void DesenhaMapa(struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeObstaculos)
{
    int i;

    for (i = 0; i < numeroDeObstaculos; i++)
    {

        switch (obstaculos[i].tipo)
        {
        case 'P':
            DrawRectangleRec(obstaculos[i].hitbox, BROWN);
            break;
        case 'V':
            DrawRectangleRec(obstaculos[i].hitbox, PINK);
            break;
        default:
            break;
        }

    }

}

//Desenha o chao
void DesenhaChao(char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ],Texture2D textureChao)
{
    int i, j;
    for(i=0; i<ALTURA/CELULAMATRIZ; i++)
        for(j=0; j<LARGURA/CELULAMATRIZ; j++)
            DrawTextureV(textureChao,(Vector2)
        {
            j*CELULAMATRIZ,(i)*CELULAMATRIZ + ALTURABARRASTATUS
        },WHITE);

}

//void leMapa

