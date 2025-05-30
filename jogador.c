#include <stdio.h>
#include <stdbool.h>

#include "raylib.h"

#include "jogador.h"
#include "variaveis_globais.h"

//Funcao que recebe como parametro a matriz mapa e define a posicao inicial (x,y) do jogador conforme o mapa

void PosicionaJogadorInicialmente (char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], struct Player *player)
{

    char *p;

    player->hitbox.width = CELULAMATRIZ;
    player->hitbox.height = CELULAMATRIZ;

    for(p = &mapa[0][0]; p <= &mapa[(ALTURA/CELULAMATRIZ) - 1][(LARGURA/CELULAMATRIZ) - 1]; p++)
    {
        if (*p == 'J')
        {

            player->hitbox.x = ((p - &mapa[0][0]) % (LARGURA/CELULAMATRIZ))*CELULAMATRIZ;
            player->hitbox.y = ((p - &mapa[0][0]) / (LARGURA/CELULAMATRIZ))*CELULAMATRIZ;

        }
    }

}

//Funcao que desenha o jogador
void DesenhaJogador (struct Player player)
{
    DrawRectangleRec(player.hitbox, LIME);
}

bool ChecaColisao (struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Player player, int numeroDeObstaculos, char direcao, char tipoObstaculo)
{
    int i;
    bool colisao = false;
    Rectangle hitbox = player.hitbox;

    switch (tipoObstaculo)
    {
    case 'P':
        for (i = 0; i < numeroDeObstaculos; i ++)
        {
            if (obstaculos[i].tipo == 'P')
            {
                switch (direcao)
                {
                case 'U':
                    hitbox.y -= 1;
                    if (CheckCollisionRecs(hitbox, obstaculos[i].hitbox))
                    {
                        colisao = true;
                        return colisao;
                    }
                    break;
                case 'L':
                    hitbox.x -= 1;
                    if (CheckCollisionRecs(hitbox, obstaculos[i].hitbox))
                    {
                        colisao = true;
                        return colisao;
                    }
                    break;
                case 'R':
                    hitbox.x += 1;
                    if (CheckCollisionRecs(hitbox, obstaculos[i].hitbox))
                    {
                        colisao = true;
                        return colisao;
                    }
                    break;
                case 'D':
                    hitbox.y += 1;
                    if (CheckCollisionRecs(hitbox, obstaculos[i].hitbox))
                    {
                        colisao = true;
                        return colisao;
                    }
                    break;
                default:
                    break;
                }
            }
        }
        break;
    case 'V':
        for (i = 0; i < numeroDeObstaculos; i++)
        {
            if (obstaculos[i].tipo == 'V' && CheckCollisionRecs(hitbox, obstaculos[i].hitbox))
            {
                colisao = true;
                obstaculos[i].tipo = 'E';
                return colisao;
            }

        }
        break;
    default:
        break;
    }

    return colisao;

}




//Função que returna 1 caso duas teclas não opositoras estejam sendo pressionadas ao mesmo tempo, e 0 caso contrário.

bool DuasTeclas()
{
    bool duasTeclas = false;
    if(IsKeyDown(KEY_W) && IsKeyDown(KEY_A))
        duasTeclas = true;
    if(IsKeyDown(KEY_W) && IsKeyDown(KEY_D))
        duasTeclas = true;
    if(IsKeyDown(KEY_S) && IsKeyDown(KEY_A))
        duasTeclas = true;
    if(IsKeyDown(KEY_S) && IsKeyDown(KEY_D))
        duasTeclas = true;
    return duasTeclas;
}

//Funcao que recebe uma direcao (U, D, L, R), uma matriz mapa e movimenta um objeto, com restricao de movimento a obstaculos (genérica), retorna 1 se houve colisão.
void Movimenta (char direcao, struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Player *player, int numeroDeObstaculos)
{
    switch (direcao)
    {
    case 'U':
        if (!ChecaColisao(obstaculos, *player, numeroDeObstaculos, 'U', 'P'))
        {
            player->hitbox.y -= player->velocidadeMovimento;
            player->orientacao = 'U';
        }
        break;
    case 'D':
        if (!ChecaColisao(obstaculos, *player, numeroDeObstaculos, 'D', 'P'))
        {
            player->hitbox.y += player->velocidadeMovimento;
            player->orientacao = 'D';

        }
        break;
    case 'L':
        if (!ChecaColisao(obstaculos, *player, numeroDeObstaculos, 'L', 'P'))
        {
            player->hitbox.x -= player->velocidadeMovimento;
            player->orientacao = 'L';

        }
        break;
    case 'R':
        if (!ChecaColisao(obstaculos, *player, numeroDeObstaculos, 'R', 'P'))
        {
            player->hitbox.x += player->velocidadeMovimento;
            player->orientacao = 'R';

        }
        break;
    default:
        break;
    }
}



//Função que desenha a quantidade de vidas do jogador
void DesenhaVidas(struct Player player)
{
    int i;
    if(player.vidas > 0)
        for(i=0; i<player.vidas; i++)
            DrawRectangle(10+i*52,10,CELULAMATRIZ,CELULAMATRIZ,MAROON);
}


