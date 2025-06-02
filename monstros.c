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

//Le a matriz e preenche array de monstros com os devidos monstros e seus parametros
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
            posY = ((p - &mapa[0][0]) / (LARGURA/CELULAMATRIZ))*CELULAMATRIZ + ALTURABARRASTATUS;

            monstros[*numeroDeMonstros].hitbox.x = posX;
            monstros[*numeroDeMonstros].hitbox.y = posY;
            monstros[*numeroDeMonstros].hitbox.width = CELULAMATRIZ;
            monstros[*numeroDeMonstros].hitbox.height = CELULAMATRIZ;
            monstros[*numeroDeMonstros].tipo = 'M';
            monstros[*numeroDeMonstros].vida = 3;
            monstros[*numeroDeMonstros].forca = 10;
            monstros[*numeroDeMonstros].raioVisao = 300;
            monstros[*numeroDeMonstros].velocidadeMovimento = 2.5;
            monstros[*numeroDeMonstros].timerMovimento = 300;
            monstros[*numeroDeMonstros].timerStun = 300;
            monstros[*numeroDeMonstros].stun = false;
            monstros[*numeroDeMonstros].status = 'E';
            monstros[*numeroDeMonstros].id = *numeroDeMonstros;


            *numeroDeMonstros += 1;

        }

    }

}

//Fun��o que calcula dist�ncia entre dois pontos
float CalculaDistanciaEntreDoisPontos(float x1, float y1, float x2, float y2)
{
    return(sqrt(pow((x1-x2),2)+pow((y1-y2),2)));
}

//Calcula a dist�ncia entre cada monstro e o player
void CalculaDistanciaMonstroPlayer(struct Monstro *monstro, struct Player player)
{
    monstro->distanciaPlayer = CalculaDistanciaEntreDoisPontos(monstro->hitbox.x + (monstro->hitbox.width/2), monstro->hitbox.y + (monstro->hitbox.height/2), player.hitbox.x + (player.hitbox.width/2), player.hitbox.y + (player.hitbox.height/2));
}

//Atualiza a distancia entre cada monstro e o plaayer
void AtualizaDistanciaMonstroPlayer (struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Player player, int numeroDeMonstros)
{
    int i;

    for (i = 0; i < numeroDeMonstros; i++)
    {
        CalculaDistanciaMonstroPlayer(&monstros[i], player);
    }

}

//Checa se ha colisao entre o player e algum monstro. Se sim, decrementa vida do player e aplica knockback no player
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
                    KnockbackPlayer(monstros[i], player, obstaculos, numeroDeObstaculos);
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



//Determina se o monstro esta no raio de visao do player
bool MonstroNoRaioDeVisao(struct Monstro monstro, struct Player player)
{
    if(fabs((monstro.hitbox.x + monstro.hitbox.width/2) - (player.hitbox.x + player.hitbox.width/2)) <= monstro.raioVisao && fabs((monstro.hitbox.y + monstro.hitbox.height/2) - (player.hitbox.y + player.hitbox.height/2)) <= monstro.raioVisao)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Desenha os monstros do array
void DesenhaMonstros(struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeMonstros)
{
    int i;

    for (i = 0; i < numeroDeMonstros; i++)
    {

        if(monstros[i].vida > 0)
        {
            switch (monstros[i].tipo)
            {
            case 'M':
                switch (monstros[i].vida)
                {
                case 3:
                    DrawRectangleRec(monstros[i].hitbox, ORANGE);
                    break;
                case 2:
                    DrawRectangleRec(monstros[i].hitbox, RED);
                    break;
                case 1:
                    DrawRectangleRec(monstros[i].hitbox, MAROON);
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }

    }

}

//Checa se ha colisao entre a hitbox dos monstros e dos osbstaculos
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

//Checaa se ha colisao entre monstros
bool ChecaColisaoEntreMonstros (struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Monstro monstro, int numeroDeMonstros)
{
    int i;
    bool colisao = false;
    Rectangle hitbox = monstro.hitbox;

    for (i = 0; i < numeroDeMonstros; i++)
    {
        if (monstros[i].vida > 0 && i != monstro.id)
        {
            switch (monstro.orientacao)
            {
            case 'U':
                hitbox.y -= 1;
                if (CheckCollisionRecs(hitbox, monstros[i].hitbox))
                {
                    colisao = true;
                    return colisao;
                }
                break;
            case 'L':
                hitbox.x -= 1;
                if (CheckCollisionRecs(hitbox, monstros[i].hitbox))
                {
                    colisao = true;
                    return colisao;
                }
                break;
            case 'R':
                hitbox.x += 1;
                if (CheckCollisionRecs(hitbox, monstros[i].hitbox))
                {
                    colisao = true;
                    return colisao;
                }
                break;
            case 'D':
                hitbox.y += 1;
                if (CheckCollisionRecs(hitbox, monstros[i].hitbox))
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

    return colisao;

}

//Funcao que movimenta um dado monstro, levando em conta possiveis colisoes
void MovimentaMonstro (char direcao, struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Monstro *monstro, int numeroDeObstaculos, struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeMonstros)
{
    switch (direcao)
    {
    case 'U':
        if (!ChecaColisaoMonstroObstaculos(obstaculos, *monstro, numeroDeObstaculos, 'U', 'P') && monstro->hitbox.y > ALTURABARRASTATUS && !ChecaColisaoEntreMonstros(monstros, *monstro, numeroDeMonstros))
        {
            monstro->hitbox.y -= monstro->velocidadeMovimento;
            monstro->orientacao = 'U';
        }
        break;
    case 'D':
        if (!ChecaColisaoMonstroObstaculos(obstaculos, *monstro, numeroDeObstaculos, 'D', 'P') && monstro->hitbox.y + monstro->hitbox.height < ALTURA && !ChecaColisaoEntreMonstros(monstros, *monstro, numeroDeMonstros))
        {
            monstro->hitbox.y += monstro->velocidadeMovimento;
            monstro->orientacao = 'D';

        }
        break;
    case 'L':
        if (!ChecaColisaoMonstroObstaculos(obstaculos, *monstro, numeroDeObstaculos, 'L', 'P') && monstro->hitbox.x > 0 && !ChecaColisaoEntreMonstros(monstros, *monstro, numeroDeMonstros))
        {
            monstro->hitbox.x -= monstro->velocidadeMovimento;
            monstro->orientacao = 'L';

        }
        break;
    case 'R':
        if (!ChecaColisaoMonstroObstaculos(obstaculos, *monstro, numeroDeObstaculos, 'R', 'P') && monstro->hitbox.x + monstro->hitbox.width < LARGURA && !ChecaColisaoEntreMonstros(monstros, *monstro, numeroDeMonstros))
        {
            monstro->hitbox.x += monstro->velocidadeMovimento;
            monstro->orientacao = 'R';

        }
        break;
    default:
        break;
    }

}

//Executa o movimento de cada monstro de acordo com o status
void MovimentoAutomaticoMonstros(struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeMonstros, struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeObstaculos)
{
    int i;

    for (i = 0; i < numeroDeMonstros; i++)
    {
        switch(monstros[i].status)
        {
        case 'M':
            MovimentaMonstro(monstros[i].orientacao, obstaculos, &monstros[i], numeroDeObstaculos, monstros, numeroDeMonstros);
            break;
        default:
            break;
        }

    }

}

//Atualiz o timer de movimento e stun de cada monstro
void AtualizaTimerMonstros(struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeMonstros)
{
    int i;

    for (i = 0; i < numeroDeMonstros; i++)
    {
        switch(monstros[i].status)
        {
        case 'E':
            monstros[i].timerMovimento -= 2.5;
            break;
        case 'M':
            monstros[i].timerMovimento += 15;
            break;
        default:
            break;
        }
        if (monstros[i].stun) {
            monstros[i].timerStun -= 5;
        }

    }

}

//Escolhe uma direcao para o movimento automatico do monstro. Se o jogador estiver no raio de visao do monstro, o mesmo se move em direcao a ele
char SorteiaDirecao(struct Monstro monstro, struct Player player)
{
    int direcao;
    char modo = 'A';

    if (monstro.distanciaPlayer < monstro.raioVisao)
    {
        modo = 'P';
    }

    switch(modo)
    {
    case 'A':
        direcao = rand() % 4;
        switch (direcao)
        {
        case 0:
            return 'U';
            break;
        case 1:
            return 'R';
            break;
        case 2:
            return 'D';
            break;
        case 3:
            return 'L';
            break;
        default:
            break;
        }
        break;
    case 'P':
        if((monstro.hitbox.x >= player.hitbox.x + player.hitbox.width - player.velocidadeMovimento) && (player.hitbox.y < monstro.hitbox.y + monstro.hitbox.height) && (player.hitbox.y + player.hitbox.height > monstro.hitbox.y))
        {
            return 'L';
        }
        if((monstro.hitbox.x  + monstro.hitbox.width - player.velocidadeMovimento <= player.hitbox.x) && (player.hitbox.y < monstro.hitbox.y + monstro.hitbox.height) && (player.hitbox.y + player.hitbox.height > monstro.hitbox.y))
        {
            return 'R';
        }

        if((monstro.hitbox.y + monstro.hitbox.height - player.velocidadeMovimento <= player.hitbox.y) && (player.hitbox.x < monstro.hitbox.x + monstro.hitbox.width) && (player.hitbox.x + player.hitbox.width > monstro.hitbox.x))
        {
            return 'D';
        }
        if((monstro.hitbox.y >= player.hitbox.y + player.hitbox.height - player.velocidadeMovimento) && (player.hitbox.x < monstro.hitbox.x + monstro.hitbox.width) && (player.hitbox.x + player.hitbox.width > monstro.hitbox.x))
        {
            return 'U';
        }

        direcao = rand() % 2;
        float monstroX = monstro.hitbox.x + monstro.hitbox.width/2;
        float monstroY = monstro.hitbox.y + monstro.hitbox.height/2;
        float playerX = player.hitbox.x + player.hitbox.width/2;
        float playerY = player.hitbox.y + player.hitbox.height/2;

        if (monstroX >= playerX && monstroY >= playerY)
        {
            switch(direcao)
            {
            case 0:
                return 'U';
                break;
            case 1:
                return 'L';
                break;
            default:
                break;
            }
        }
        if (monstroX <= playerX && monstroY >= playerY)
        {
            switch(direcao)
            {
            case 0:
                return 'U';
                break;
            case 1:
                return 'R';
                break;
            default:
                break;
            }
        }
        if (monstroX >= playerX && monstroY <= playerY)
        {
            switch(direcao)
            {
            case 0:
                return 'D';
                break;
            case 1:
                return 'L';
                break;
            default:
                break;
            }
        }
        if (monstroX <= playerX && monstroY <= playerY)
        {
            switch(direcao)
            {
            case 0:
                return 'D';
                break;
            case 1:
                return 'R';
                break;
            default:
                break;
            }
        }
        break;
    default:
        break;
    }

}

//Atualiza status de movimento do monstro de acordo com o timer
void AtualizaStatusMonstros (struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeMonstros, struct Player player)
{
    int i;

    for (i = 0; i < numeroDeMonstros; i++)
    {

            if (monstros[i].timerMovimento < 0)
            {
                monstros[i].status = 'M';
                monstros[i].orientacao = SorteiaDirecao(monstros[i], player);
            }
            if (monstros[i].timerMovimento >= 300)
            {
                monstros[i].status = 'E';
            }
            if (monstros[i].timerStun <= 0) {
                monstros[i].timerStun = 300;
                monstros[i].stun = false;

            }

    }

}
