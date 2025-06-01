#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


#include "raylib.h"
#include "jogador.h"
#include "monstros.h"
#include "variaveis_globais.h"
#include "ataque_dano.h"


//srand(time(NULL));

//Lê o mapa e guarda as posições dos montros nas variáveis posX e posY da estrutura Monstros, além da quantidade de monstros no mapa inteiro
//void CriaMonstros(char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], int posX[], int posY[], int enterrado[], int timerMovimento[], int pontoX[], int pontoY[], int ataqueStun[], int *quantidadeMonstros) {
//    int i, j, iMonstro = 0;
//    for(i=0;i<MAXMONSTROS;i++) {
//        posX[i] = -1;
//        posY[i] = -1;
//        enterrado[i] = 0;
//        timerMovimento[i] = 300;
//        pontoX[i] = -1;
//        pontoY[i] = -1;
//        ataqueStun[i] = 0;
//    }
//    for(i=0;i<ALTURA/CELULAMATRIZ;i++) {
//        for(j=0;j<LARGURA/CELULAMATRIZ;j++) {
//            if(mapa[i][j] == 'M') {
//                posX[iMonstro] = j*CELULAMATRIZ;
//                posY[iMonstro] = i*CELULAMATRIZ;
//                pontoX[iMonstro] = posX[iMonstro];
//                pontoY[iMonstro] = posY[iMonstro];
//                iMonstro++;
//            }
//        }
//    }
//    *quantidadeMonstros = iMonstro;
//}

void CriaMonstros(char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int *numeroDeMonstros)
{
    char *p;
    int posX, posY;
    *numeroDeMonstros = 0;

    for(p = &mapa[0][0]; p <= &mapa[(ALTURA/CELULAMATRIZ) - 1][(LARGURA/CELULAMATRIZ) - 1]; p++)
    {
        if (*p == 'M')
        {
            posX = ((p - &mapa[0][0]) % (LARGURA/CELULAMATRIZ))*CELULAMATRIZ;
            posY = ((p - &mapa[0][0]) / (LARGURA/CELULAMATRIZ))*CELULAMATRIZ;

            monstros[*numeroDeMonstros].hitbox.x = posX;
            monstros[*numeroDeMonstros].hitbox.y = posY;
            monstros[*numeroDeMonstros].hitbox.width = CELULAMATRIZ;
            monstros[*numeroDeMonstros].hitbox.height = CELULAMATRIZ;
            monstros[*numeroDeMonstros].tipo = 'M';
            monstros[*numeroDeMonstros].vida = 1;
            monstros[*numeroDeMonstros].forca = 10;
            monstros[*numeroDeMonstros].raioVisao = 200;
            monstros[*numeroDeMonstros].velocidadeMovimento = 6;
            monstros[*numeroDeMonstros].timerMovimento = 300;


            *numeroDeMonstros += 1;

        }

    }

}

//Função que calcula distância entre dois pontos
float CalculaDistanciaEntreDoisPontos(float x1, float y1, float x2, float y2)
{
    return(sqrt(pow((x1-x2),2)+pow((y1-y2),2)));
}

//Calcula a distância entre cada monstro e o player
void CalculaDistanciaMonstroPlayer(struct Monstro *monstro, struct Player player)
{
    monstro->distanciaPlayer = CalculaDistanciaEntreDoisPontos(monstro->hitbox.x + (monstro->hitbox.width/2), monstro->hitbox.y + (monstro->hitbox.height/2), player.hitbox.x + (player.hitbox.width/2), player.hitbox.y + (player.hitbox.height/2));
}

void AtualizaDistanciaMonstroPlayer (struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Player player, int numeroDeMonstros)
{
    int i;

    for (i = 0; i < numeroDeMonstros; i++)
    {
        CalculaDistanciaMonstroPlayer(&monstros[i], player);
    }

}

bool ChecaColisaoPlayerMonstros (struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Player *player, int numeroDeMonstros, struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeObstaculos)
{

    int i;
    bool colisao = false;
    Rectangle hitbox = player->hitbox;


    for (i = 0; i < numeroDeMonstros; i ++)
    {
        if (monstros[i].vida > 0)
        {
            switch (monstros[i].tipo)
            {
            case 'M':
                if (CheckCollisionRecs(hitbox, monstros[i].hitbox))
                {
                    colisao = true;
                    player->vidas -= 1;
                    Knockback(monstros[i], player, obstaculos, numeroDeObstaculos);
                    return colisao;
                }
                break;
            default:
                break;
            }
        }
    }

    return colisao;
}



//Determina se o monstro deveria se mexer ou não baseado em sua distância até o player
bool MonstroDeveMover(struct Monstro monstro, struct Player player)
{
    if(fabs(monstro.hitbox.x - player.hitbox.x) <= monstro.raioVisao && fabs(monstro.hitbox.y - player.hitbox.y) <= monstro.raioVisao)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void DesenhaMonstros(struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeMonstros)
{
    int i;

    for (i = 0; i < numeroDeMonstros; i++)
    {

        switch (monstros[i].tipo)
        {
        case 'M':
            DrawRectangleRec(monstros[i].hitbox, RED);
            break;
        default:
            break;
        }

    }

}

void DesenhaMonstro(struct Monstro monstro)
{
    switch (monstro.tipo)
    {
    case 'M':
        DrawRectangleRec(monstro.hitbox, RED);
        break;
    default:
        break;
    }

}







bool ChecaColisaoMonstroObstaculos (struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Monstro monstro, int numeroDeObstaculos, char direcao, char tipoObstaculo)
{
    int i;
    bool colisao = false;
    Rectangle hitbox = monstro.hitbox;

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


void MovimentaMonstro (char direcao, struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Monstro *monstro, int numeroDeObstaculos)
{
    switch (direcao)
    {
    case 'U':
        if (!ChecaColisaoMonstroObstaculos(obstaculos, *monstro, numeroDeObstaculos, 'U', 'P') && monstro->hitbox.y > 0)
        {
            monstro->hitbox.y -= monstro->velocidadeMovimento;
            monstro->orientacao = 'U';
        }
        break;
    case 'D':
        if (!ChecaColisaoMonstroObstaculos(obstaculos, *monstro, numeroDeObstaculos, 'D', 'P') && monstro->hitbox.y + monstro->hitbox.height < ALTURA)
        {
            monstro->hitbox.y += monstro->velocidadeMovimento;
            monstro->orientacao = 'D';

        }
        break;
    case 'L':
        if (!ChecaColisaoMonstroObstaculos(obstaculos, *monstro, numeroDeObstaculos, 'L', 'P') && monstro->hitbox.x > 0)
        {
            monstro->hitbox.x -= monstro->velocidadeMovimento;
            monstro->orientacao = 'L';

        }
        break;
    case 'R':
        if (!ChecaColisaoMonstroObstaculos(obstaculos, *monstro, numeroDeObstaculos, 'R', 'P') && monstro->hitbox.x + monstro->hitbox.width < LARGURA)
        {
            monstro->hitbox.x += monstro->velocidadeMovimento;
            monstro->orientacao = 'R';

        }
        break;
    default:
        break;
    }

    DesenhaMonstro(*monstro);
}


void MovimentoAutomaticoMonstro(struct Monstro *monstro, struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeObstaculos)
{
    int i;
    if(monstro->timerMovimento <= 0)
    {
        monstro->timerMovimento = 300;
//        monstro->hitbox.x = monstro->hitbox.x + ((rand() % 5) - 2) * 100;
//        for (i = 0; i < 5; i++)
//        {
            MovimentaMonstro('R', obstaculos, monstro, numeroDeObstaculos);
//            DrawRectangleRec(monstro->hitbox, RED);
//        }
//        monstro->hitbox.x = monstro->hitbox.x + monstro->velocidadeMovimento;

//        monstro->hitbox.y = monstro->hitbox.y + ((rand() % 5) - 2) * 100;
    }

}

void AtualizaMonstros(struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeMonstros, struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeObstaculos)
{
    int i;
    int j;
//    for (j = 0; j < 25; j++)
//    {
    for (i = 0; i < numeroDeMonstros; i++)
    {
        monstros[i].timerMovimento -= 5;
//        MovimentoAutomaticoMonstro(&monstros[i], obstaculos, numeroDeObstaculos);
    }

    DesenhaMonstros(monstros, numeroDeMonstros);

//    }

}


//Funcao que desenha os monstros
//void DesenhaMonstros(struct Monstro monstros, struct Player player) {
//    int i;
//    for(i=0;i<MAXMONSTROS;i++) {
//        if(monstros.posX[i] != -1 && monstros.posY[i] != -1 && MonstroDeveMover(monstros, player, i) == 0)
//            DrawRectangle(monstros.posX[i], monstros.posY[i], CELULAMATRIZ, CELULAMATRIZ, RED);
//        if(monstros.posX[i] != -1 && monstros.posY[i] != -1 && MonstroDeveMover(monstros, player, i) == 1)
//            DrawRectangle(monstros.posX[i], monstros.posY[i], CELULAMATRIZ, CELULAMATRIZ, ORANGE);
//    }
//}


