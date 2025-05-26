#include <stdio.h>
#include "raylib.h"
#include "jogador.h"
#include "variaveis_globais.h"



//Funcao que recebe como parametro a matriz mapa e define a posicao inicial (x,y) do jogador conforme o mapa

void PosicionaJogadorInicialmente (char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], int *posX, int *posY)
{

    char *p;

    for(p = &mapa[0][0]; p <= &mapa[(ALTURA/CELULAMATRIZ) - 1][(LARGURA/CELULAMATRIZ) - 1]; p++)
    {
        if (*p == 'J')
        {
            *posX = ((p - &mapa[0][0]) % (LARGURA/CELULAMATRIZ))*CELULAMATRIZ;
            *posY = ((p - &mapa[0][0]) / (LARGURA/CELULAMATRIZ))*CELULAMATRIZ;
        }
    }

}

//Funcao que desenha o jogador
void DesenhaJogador (struct Player player) {
    DrawRectangle(player.posX, player.posY, player.tamanhoPersonagem, player.tamanhoPersonagem, LIME);
}

//Funcao que recebe uma direcao (U, D, L, R), uma matriz mapa e movimenta um objeto, com restricao de movimento a obstaculos (genérica), retorna 1 se houve colisão.
int Movimenta (char direcao, char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], int *posX, int *posY, int vel)
{
    switch (direcao)
    {
    case 'U':
        if (*posY > 0 &&
                (mapa[(*posY - 1)/CELULAMATRIZ][(*posX + CELULAMATRIZ - 1)/CELULAMATRIZ] != 'P' &&
                 mapa[(*posY - 1)/CELULAMATRIZ][*posX/CELULAMATRIZ] != 'P'))
        {
            *posY -= vel;
            return 0;
        } else {
            return 1;
        }

        break;
    case 'D':
        if (*posY < ALTURA - CELULAMATRIZ &&
                (mapa[(*posY + CELULAMATRIZ + 1)/CELULAMATRIZ][*posX/CELULAMATRIZ] != 'P' &&
                 mapa[(*posY + CELULAMATRIZ + 1)/CELULAMATRIZ][(*posX + CELULAMATRIZ - 1)/CELULAMATRIZ] != 'P')
           )
        {
            *posY += vel;
            return 0;
        } else {
            return 1;
        }

        break;
    case 'L':
        if (*posX > 0 &&
                (mapa[*posY/CELULAMATRIZ][(*posX - 1)/CELULAMATRIZ] != 'P' &&
                 mapa[(*posY + CELULAMATRIZ - 1)/CELULAMATRIZ][(*posX - 1)/CELULAMATRIZ] != 'P')
           )
        {
            *posX -= vel;
            return 0;
        } else {
            return 1;
        }

        break;
    case 'R':
        if (*posX < LARGURA - CELULAMATRIZ &&
                (mapa[*posY/CELULAMATRIZ][(*posX + CELULAMATRIZ + 1)/CELULAMATRIZ] != 'P' &&
                 mapa[(*posY + CELULAMATRIZ - 1)/CELULAMATRIZ][(*posX + CELULAMATRIZ + 1)/CELULAMATRIZ] != 'P')
           )
        {
            *posX += vel;
            return 0;
        } else {
            return 1;
        }

        break;
    default:
        return 1;
        break;
    }
}

//Função que returna 1 caso duas teclas não opositoras estejam sendo pressionadas ao mesmo tempo, e 0 caso contrário.
int DuasTeclas() {
    int i = 0;
    if(IsKeyDown(KEY_W) && IsKeyDown(KEY_A))
        i = 1;
    if(IsKeyDown(KEY_W) && IsKeyDown(KEY_D))
        i = 1;
    if(IsKeyDown(KEY_S) && IsKeyDown(KEY_A))
        i = 1;
    if(IsKeyDown(KEY_S) && IsKeyDown(KEY_D))
        i = 1;
    return i;
}

//Função que desenha a quantidade de vidas do jogador
void DesenhaVidas(struct Player player) {
    int i;
    if(player.vidas > 0)
        for(i=0;i<player.vidas;i++)
            DrawRectangle(10+i*52,10,50,50,MAROON);
}

//Função que detecta colisão entre player e o item de vida extra, e deleta o item em caso positivo.
int ColisaoVida(char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], struct Player player) {
    if(mapa[player.posY/CELULAMATRIZ][player.posX/CELULAMATRIZ] == 'V') {
        mapa[player.posY/CELULAMATRIZ][player.posX/CELULAMATRIZ] = '-';
        return 1;
    } else {
        return 0;
    }
}

