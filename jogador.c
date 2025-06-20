#include <stdio.h>
#include <stdbool.h>

#include "raylib.h"

#include "jogador.h"
#include "variaveis_globais.h"
#include "monstros.h"

//Funcao que inicializa parametros basicos do player
void CriaPlayer (struct Player *player) {
    player->velocidadeMovimento = 5;
    player->movendo = false;
    player->PlayerFPS =  3;
    player->timerAnimacao = 1/player->PlayerFPS;
    player->contadorFrame = 0;
    player->orientacao = 'D';
    player->vidas = 3;
    player->armaAtual = 'C';
    player->municao = 10;
    player->stun = false;
    player->timerStun = 300;
    player->timerTiro = 300;
    player->atirando = false;
    player->numeroDeBalasNaTela = 0;
    player->score = 0;
}


//Le a matriz e posiciona o jogador inicialmente
void PosicionaPlayerInicialmente (char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], struct Player *player)
{

    char *p;

    player->hitbox.width = CELULAMATRIZ;
    player->hitbox.height = CELULAMATRIZ;

    for(p = &mapa[0][0]; p <= &mapa[(ALTURA/CELULAMATRIZ) - 1][(LARGURA/CELULAMATRIZ) - 1]; p++)
    {
        if (*p == 'J')
        {

            player->hitbox.x = ((p - &mapa[0][0]) % (LARGURA/CELULAMATRIZ))*CELULAMATRIZ;
            player->hitbox.y = ((p - &mapa[0][0]) / (LARGURA/CELULAMATRIZ))*CELULAMATRIZ + ALTURABARRASTATUS;

        }
    }

}

//Funcao que desenha o jogador
void DesenhaJogador (struct Player *player, Texture2D playerTexture)
{
    switch(player->orientacao) {
        case 'U':
            if(!player->movendo) {DrawTextureRec(playerTexture, (Rectangle){50,0,50,50}, (Vector2){player->hitbox.x, player->hitbox.y}, WHITE);}
            else {
                if(player->contadorFrame > 3)
                    player->contadorFrame = 0;
                DrawTextureRec(playerTexture, (Rectangle){50*player->contadorFrame,0,50,50}, (Vector2){player->hitbox.x, player->hitbox.y}, WHITE);
            }
            break;
        case 'D':
            if(!player->movendo) {DrawTextureRec(playerTexture, (Rectangle){50,100,50,50}, (Vector2){player->hitbox.x, player->hitbox.y}, WHITE);}
            else {
                if(player->contadorFrame > 3)
                    player->contadorFrame = 0;
                DrawTextureRec(playerTexture, (Rectangle){50*player->contadorFrame,100,50,50}, (Vector2){player->hitbox.x, player->hitbox.y}, WHITE);
            }
            break;
        case 'L':
            if(!player->movendo) {DrawTextureRec(playerTexture, (Rectangle){50,150,50,50}, (Vector2){player->hitbox.x, player->hitbox.y}, WHITE);}
            else {
                if(player->contadorFrame > 3)
                    player->contadorFrame = 0;
                DrawTextureRec(playerTexture, (Rectangle){50*player->contadorFrame,150,50,50}, (Vector2){player->hitbox.x, player->hitbox.y}, WHITE);
            }
            break;
        case 'R':
            if(!player->movendo) {DrawTextureRec(playerTexture, (Rectangle){50,50,50,50}, (Vector2){player->hitbox.x, player->hitbox.y}, WHITE);}
            else {
                if(player->contadorFrame > 3)
                    player->contadorFrame = 0;
                DrawTextureRec(playerTexture, (Rectangle){50*player->contadorFrame,50,50,50}, (Vector2){player->hitbox.x, player->hitbox.y}, WHITE);
            }
            break;
    }
}

//Checa colisao entre a hitbox do player e dos obstaculos
bool ChecaColisaoPlayerObstaculos (struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Player player, int numeroDeObstaculos, char direcao, char tipoObstaculo)
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

//Detecta se o player não está se movendo.
void PlayerParado(struct Player *player) {
    if(!IsKeyDown(KEY_W) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_S) && !IsKeyDown(KEY_D))
        player->movendo = false;
}

//Diminui o timer de animação do player pelo tempo passado entre o ultimo frame e o atual. Se o valor ficar abaixo de 0, reseta para o inverso do fps e aumenta o contador de frames. Basicamente
//timer representa o tempo que deve passar entre cada frame da animação, por isso que quando o tempo passado for maior do que o timer, ele é resetado e aumenta o contador de frames.
void AtualizaTimerAnimacaoPlayer(struct Player *player) {
    player->timerAnimacao -= GetFrameTime();
    if(player->timerAnimacao < 0) {
        player->contadorFrame++;
        player->timerAnimacao = 1/player->PlayerFPS;
    }
}

//Função que retorna true caso duas teclas não opositoras estejam sendo pressionadas ao mesmo tempo, e false caso contrário.
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

//Funcao que recebe uma direcao (U, D, L, R) e movimenta o player, levando em conta colisao com objetos.
void MovimentaPlayer (char direcao, struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Player *player, int numeroDeObstaculos)
{
    switch (direcao)
    {
    case 'U':
        if (!ChecaColisaoPlayerObstaculos(obstaculos, *player, numeroDeObstaculos, 'U', 'P') && player->hitbox.y > ALTURABARRASTATUS)
        {
            player->hitbox.y -= player->velocidadeMovimento;
            player->orientacao = 'U';
            player->movendo = true;
        }
        break;
    case 'D':
        if (!ChecaColisaoPlayerObstaculos(obstaculos, *player, numeroDeObstaculos, 'D', 'P') && player->hitbox.y + player->hitbox.height < ALTURA + ALTURABARRASTATUS)
        {
            player->hitbox.y += player->velocidadeMovimento;
            player->orientacao = 'D';
            player->movendo = true;

        }
        break;
    case 'L':
        if (!ChecaColisaoPlayerObstaculos(obstaculos, *player, numeroDeObstaculos, 'L', 'P') && player->hitbox.x > 0)
        {
            player->hitbox.x -= player->velocidadeMovimento;
            player->orientacao = 'L';
            player->movendo = true;

        }
        break;
    case 'R':
        if (!ChecaColisaoPlayerObstaculos(obstaculos, *player, numeroDeObstaculos, 'R', 'P') && player->hitbox.x + player->hitbox.width < LARGURA)
        {
            player->hitbox.x += player->velocidadeMovimento;
            player->orientacao = 'R';
            player->movendo = true;

        }
        break;
    default:
        break;
    }
}

void AtualizaTimerPlayer (struct Player *player)
{

    if (player->stun)
    {
        player->timerStun -= 5;
    }

    if (player->timerStun <= 0)
    {
        player->timerStun = 300;
        player->stun = false;

    }

    if (player->atirando)
    {
        player->timerTiro -= 7;
    }

    if (player->timerTiro <= 0)
    {
        player->timerTiro = 300;
        player->atirando = false;

    }

}




