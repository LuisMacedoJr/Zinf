#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "variaveis_globais.h"
#include "ataque_dano.h"
#include "jogador.h"
#include "monstros.h"
#include "estruturas.h"

//Funcao que posiciona o chicote a frente do jogador
void AtacaChicote(struct Player player, struct Chicote *chicote)
{
    if (player.armaAtual == 'C')
    {
        float comprimentoChicote = 50;
        float larguraChicote = 20;

        chicote->ataque = true;

        switch (player.orientacao)
        {
        case 'U':
            chicote->hitbox.width = larguraChicote;
            chicote->hitbox.height = comprimentoChicote;
            chicote->hitbox.x = player.hitbox.x + player.hitbox.width/2 - chicote->hitbox.width/2;
            chicote->hitbox.y = player.hitbox.y - chicote->hitbox.height;
            break;
        case 'L':
            chicote->hitbox.width = comprimentoChicote;
            chicote->hitbox.height = larguraChicote;
            chicote->hitbox.x = player.hitbox.x - chicote->hitbox.width;
            chicote->hitbox.y = player.hitbox.y + player.hitbox.height/2 - chicote->hitbox.height/2;
            break;
        case 'D':
            chicote->hitbox.width = larguraChicote;
            chicote->hitbox.height = comprimentoChicote;
            chicote->hitbox.x = player.hitbox.x + player.hitbox.width/2 - chicote->hitbox.width/2;
            chicote->hitbox.y = player.hitbox.y + chicote->hitbox.height;
            break;
        case 'R':
            chicote->hitbox.width = comprimentoChicote;
            chicote->hitbox.height = larguraChicote;
            chicote->hitbox.x = player.hitbox.x + chicote->hitbox.width;
            chicote->hitbox.y = player.hitbox.y + player.hitbox.height/2 - chicote->hitbox.height/2;
            break;
        }
    }

}

//funcao que desenha o chicote previamente posicionado
void DesenhaChicote(struct Chicote chicote)
{
    if (chicote.ataque)
    {
        DrawRectangleRec(chicote.hitbox, YELLOW);
    }
}

//Funcao que checa colisao entre a hitbox do chicote e dos monstros. Se sim, decrementa vida do monstro e aplica knockback no mesmo
bool ChecaColisaoChicoteMonstros (struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Chicote *chicote, int numeroDeMonstros, struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeObstaculos, struct Player *player)
{

    int i;
    bool colisao = false;
    Rectangle hitbox = chicote->hitbox;

    for (i = 0; i < numeroDeMonstros; i ++)
    {
        if (monstros[i].vivo)
        {
            switch (monstros[i].tipo)
            {
            case 'M':
                if (CheckCollisionRecs(hitbox, monstros[i].hitbox) && !monstros[i].stun && chicote->ataque)
                {
                    colisao = true;
                    monstros[i].vida -= 1;
                    if (monstros[i].vida == 0)
                    {
                        monstros[i].vivo = false;
                        player->score += monstros[i].score;
                    }
                    monstros[i].stun = true;
                    monstros[i].timerStun = 300;
                    KnockbackMonstro(*chicote, &monstros[i], obstaculos, numeroDeObstaculos, monstros, numeroDeMonstros, *player);
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


//Aplica knockback no player, definido de acordo com a forca do monstro
void KnockbackPlayer(struct Monstro monstro, struct Player *player, struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeObstaculos)
{

    int i;
    int forca = monstro.forca;
    int direcao;
    bool houveMovimento = false;

    if((monstro.hitbox.x + monstro.hitbox.width/2 >= player->hitbox.x + player->hitbox.width - player->velocidadeMovimento) && (player->hitbox.y < monstro.hitbox.y + monstro.hitbox.height) && (player->hitbox.y + player->hitbox.height > monstro.hitbox.y))
    {
        for (i = 0; i < forca; i++)
        {
            MovimentaPlayer('L', obstaculos, player, numeroDeObstaculos);
        }
        houveMovimento = true;
    }
    if((monstro.hitbox.x  + monstro.hitbox.width/2 - player->velocidadeMovimento <= player->hitbox.x) && (player->hitbox.y < monstro.hitbox.y + monstro.hitbox.height) && (player->hitbox.y + player->hitbox.height > monstro.hitbox.y))
    {
        for (i = 0; i < forca; i++)
        {
            MovimentaPlayer('R', obstaculos, player, numeroDeObstaculos);
        }
        houveMovimento = true;

    }

    if((monstro.hitbox.y + monstro.hitbox.height/2 - player->velocidadeMovimento <= player->hitbox.y) && (player->hitbox.x < monstro.hitbox.x + monstro.hitbox.width) && (player->hitbox.x + player->hitbox.width > monstro.hitbox.x))
    {
        for (i = 0; i < forca; i++)
        {
            MovimentaPlayer('D', obstaculos, player, numeroDeObstaculos);
        }
        houveMovimento = true;

    }
    if((monstro.hitbox.y + monstro.hitbox.height/2 >= player->hitbox.y + player->hitbox.height - player->velocidadeMovimento) && (player->hitbox.x < monstro.hitbox.x + monstro.hitbox.width) && (player->hitbox.x + player->hitbox.width > monstro.hitbox.x))
    {
        for (i = 0; i < forca; i++)
        {
            MovimentaPlayer('U', obstaculos, player, numeroDeObstaculos);
        }
        houveMovimento = true;

    }

    if (!houveMovimento)
    {
        direcao = rand() % 4;
        switch (direcao)
        {
        case 0:
            for (i = 0; i < forca; i++)
            {
                MovimentaPlayer('U', obstaculos, player, numeroDeObstaculos);
            }
            break;
        case 1:
            for (i = 0; i < forca; i++)
            {
                MovimentaPlayer('R', obstaculos, player, numeroDeObstaculos);
            }
            break;
        case 2:
            for (i = 0; i < forca; i++)
            {
                MovimentaPlayer('D', obstaculos, player, numeroDeObstaculos);
            }
            break;
        case 3:
            for (i = 0; i < forca; i++)
            {
                MovimentaPlayer('L', obstaculos, player, numeroDeObstaculos);
            }
            break;
        default:
            break;
        }
    }




}

//Aplica knockback no monstro
void KnockbackMonstro(struct Chicote chicote, struct Monstro *monstro, struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeObstaculos, struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeMonstros, struct Player player)
{

    int i;
    int forca = 25;

    if((player.hitbox.x >= monstro->hitbox.x + monstro->hitbox.width - monstro->velocidadeMovimento) && (monstro->hitbox.y < player.hitbox.y + player.hitbox.height) && (monstro->hitbox.y + monstro->hitbox.height > player.hitbox.y))
    {
        for (i = 0; i < forca; i++)
        {
            MovimentaMonstro('L', obstaculos, monstro, numeroDeObstaculos, monstros, numeroDeMonstros);
        }
    }
    if((player.hitbox.x  + player.hitbox.width - monstro->velocidadeMovimento <= monstro->hitbox.x) && (monstro->hitbox.y < player.hitbox.y + player.hitbox.height) && (monstro->hitbox.y + monstro->hitbox.height > player.hitbox.y))
    {
        for (i = 0; i < forca; i++)
        {
            MovimentaMonstro('R', obstaculos, monstro, numeroDeObstaculos, monstros, numeroDeMonstros);
        }
    }

    if((player.hitbox.y + player.hitbox.height - monstro->velocidadeMovimento <= monstro->hitbox.y) && (monstro->hitbox.x < player.hitbox.x + player.hitbox.width) && (monstro->hitbox.x + monstro->hitbox.width > player.hitbox.x))
    {
        for (i = 0; i < forca; i++)
        {
            MovimentaMonstro('D', obstaculos, monstro, numeroDeObstaculos, monstros, numeroDeMonstros);
        }
    }
    if((player.hitbox.y >= monstro->hitbox.y + monstro->hitbox.height - monstro->velocidadeMovimento) && (monstro->hitbox.x < player.hitbox.x + player.hitbox.width) && (monstro->hitbox.x + monstro->hitbox.width > player.hitbox.x))
    {
        for (i = 0; i < forca; i++)
        {
            MovimentaMonstro('U', obstaculos, monstro, numeroDeObstaculos, monstros, numeroDeMonstros);
        }
    }

}

void CriaBalas(struct Bala balas[MAXIMODEBALAS])
{
    int i;

    for (i = 0; i < MAXIMODEBALAS; i++)
    {
        balas[i].ataque = false;
        balas[i].velocidadeBala = 10;
    }

}

void Atira(struct Player *player, struct Bala balas[MAXIMODEBALAS])
{
    bool atirou = false;

    int i;
    if (player->armaAtual == 'C' && !player->atirando && player->municao > 0)
    {

        for (i = 0; i < MAXIMODEBALAS; i++)
        {

            if (!balas[i].ataque && !atirou)
            {
                float comprimentoBala = 50;
                float larguraBala = 20;

                balas[i].ataque = true;

                atirou = true;
                player->atirando = true;
                player->timerTiro = 300;
                player->municao -= 1;

                switch (player->orientacao)
                {
                case 'U':
                    balas[i].orientacao = 'U';
                    balas[i].hitbox.width = larguraBala;
                    balas[i].hitbox.height = comprimentoBala;
                    balas[i].hitbox.x = player->hitbox.x + player->hitbox.width/2 - balas[i].hitbox.width/2;
                    balas[i].hitbox.y = player->hitbox.y - balas[i].hitbox.height;
                    break;
                case 'L':
                    balas[i].orientacao = 'L';
                    balas[i].hitbox.width = comprimentoBala;
                    balas[i].hitbox.height = larguraBala;
                    balas[i].hitbox.x = player->hitbox.x - balas[i].hitbox.width;
                    balas[i].hitbox.y = player->hitbox.y + player->hitbox.height/2 - balas[i].hitbox.height/2;
                    break;
                case 'D':
                    balas[i].orientacao = 'D';
                    balas[i].hitbox.width = larguraBala;
                    balas[i].hitbox.height = comprimentoBala;
                    balas[i].hitbox.x = player->hitbox.x + player->hitbox.width/2 - balas[i].hitbox.width/2;
                    balas[i].hitbox.y = player->hitbox.y + balas[i].hitbox.height;
                    break;
                case 'R':
                    balas[i].orientacao = 'R';
                    balas[i].hitbox.width = comprimentoBala;
                    balas[i].hitbox.height = larguraBala;
                    balas[i].hitbox.x = player->hitbox.x + balas[i].hitbox.width;
                    balas[i].hitbox.y = player->hitbox.y + player->hitbox.height/2 - balas[i].hitbox.height/2;
                    break;
                }
            }
        }

    }

}

bool ChecaColisaoBalaObstaculos (struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Bala bala, int numeroDeObstaculos, char tipoObstaculo)
{
    int i;
    bool colisao = false;
    Rectangle hitbox = bala.hitbox;

    switch (tipoObstaculo)
    {
    case 'P':
        for (i = 0; i < numeroDeObstaculos; i ++)
        {
            if (obstaculos[i].tipo == 'P' && CheckCollisionRecs(hitbox, obstaculos[i].hitbox))
            {

                colisao = true;
                return colisao;

            }
        }
        break;
    default:
        break;
    }

    return colisao;

}


void MovimentaBala (char direcao, struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Bala *bala, int numeroDeObstaculos)
{
    if(ChecaColisaoBalaObstaculos(obstaculos, *bala, numeroDeObstaculos, 'P')
            || bala->hitbox.y <= ALTURABARRASTATUS + 10
            || bala->hitbox.y + bala->hitbox.height >= ALTURA + ALTURABARRASTATUS
            || bala->hitbox.x <= 0
            || bala->hitbox.x + bala->hitbox.width >= LARGURA)
    {
        bala->ataque = false;
    }
    else
    {

        switch (direcao)
        {
        case 'U':
            bala->hitbox.y -= bala->velocidadeBala;
            break;
        case 'D':
            bala->hitbox.y += bala->velocidadeBala;
            break;
        case 'L':
            bala->hitbox.x -= bala->velocidadeBala;
            break;
        case 'R':
            bala->hitbox.x += bala->velocidadeBala;
            break;
        default:
            break;
        }
    }

}

void AtualizaBalas(struct Bala balas[MAXIMODEBALAS], struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeObstaculos, struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeMonstros, struct Player *player)
{
    int i;

    for (i = 0; i < MAXIMODEBALAS; i++)
    {
        if (balas[i].ataque)
        {
            ChecaColisaoBalaMonstros(monstros, &balas[i], numeroDeMonstros, player);
            MovimentaBala(balas[i].orientacao, obstaculos, &balas[i], numeroDeObstaculos);
        }
    }

}

bool ChecaColisaoBalaMonstros (struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], struct Bala *bala, int numeroDeMonstros, struct Player *player)
{

    int i;
    bool colisao = false;
    Rectangle hitbox = bala->hitbox;

    for (i = 0; i < numeroDeMonstros; i ++)
    {
        if (monstros[i].vida > 0)
        {
            switch (monstros[i].tipo)
            {
            case 'M':
                if (CheckCollisionRecs(hitbox, monstros[i].hitbox) && !monstros[i].stun)
                {
                    colisao = true;
                    monstros[i].vida -= 1;
                    if (monstros[i].vida == 0)
                    {
                        monstros[i].vivo = false;
                        player->score += monstros[i].score;
                    }
                    monstros[i].stun = true;
                    monstros[i].timerStun = 300;
                    bala->ataque = false;
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

void DesenhaBalas (struct Bala balas[MAXIMODEBALAS])
{
    int i;

    for (i = 0; i < MAXIMODEBALAS; i++)
    {
        if (balas[i].ataque)
        {
            DrawRectangleRec(balas[i].hitbox, YELLOW);
        }
    }
}



//Função que atira a bala da pistola, onde o player está olhando.
//void Atirar(struct Player player, struct Balas balas, char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], int posX[], int posY[], char *dir) {
//    int i = 0;
//    if(player.dirMaisRecente == 'U' && mapa[(player.posY - 1)/CELULAMATRIZ][player.posX/CELULAMATRIZ] != 'P') {
//        while (i < 3) {
//            if(posX[i] == -1 || posY[i] == -1) {
//                posX[i] = player.posX;
//                posY[i] = player.posY - CELULAMATRIZ;
//                *dir = 'U';
//                break;
//            }
//            i++;
//        }
//    }
//    if(player.dirMaisRecente == 'D' && mapa[(player.posY + 1)/CELULAMATRIZ][player.posX/CELULAMATRIZ] != 'P') {
//        while (i < 3) {
//            if(posX[i] == -1 || posY[i] == -1) {
//                posX[i] = player.posX;
//                posY[i] = player.posY + CELULAMATRIZ;
//                *dir = 'D';
//                break;
//            }
//            i++;
//        }
//    }
//    if(player.dirMaisRecente == 'L' && mapa[player.posY/CELULAMATRIZ][(player.posX - 1)/CELULAMATRIZ] != 'P') {
//        while (i < 3) {
//            if(posX[i] == -1 || posY[i] == -1) {
//                posX[i] = player.posX - CELULAMATRIZ;
//                posY[i] = player.posY;
//                *dir = 'L';
//                break;
//            }
//            i++;
//        }
//    }
//    if(player.dirMaisRecente == 'R' && mapa[player.posY/CELULAMATRIZ][(player.posX + 1)/CELULAMATRIZ] != 'P') {
//        while (i < 3) {
//            if(posX[i] == -1 || posY[i] == -1) {
//                posX[i] = player.posX + CELULAMATRIZ;
//                posY[i] = player.posY;
//                *dir = 'R';
//                break;
//            }
//            i++;
//        }
//    }
//}

////Função que seta todas as posições de balas para 0, e a velocidade para 10
//void InicializaBalas(int posX[], int posY[], int *vel)
//{
//    int i;
//    for(i=0; i<MAXBALAS; i++)
//    {
//        posX[i] = -1;
//        posY[i] = -1;
//    }
//    *vel = 10;
//}

//Função que atualiza a posição das balas dependendo na orientação delas, e checa colisão com monstros/paredes, destruindo a bala e matando os monstros.
//void AtualizaBalas(struct Balas balas, struct Monstros monstros, int posX[], int posY[], int monstrosPosX[], int monstrosPosY[], char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ]) {
//    int i, j;
//    for(i=0;i<MAXBALAS;i++) {
//        if(posX[i] != -1 && posY[i] != -1) {
//            Movimenta(balas.direcao, mapa, &posX[i], &posY[i], balas.balaVel);
//            if(Movimenta(balas.direcao, mapa, &posX[i], &posY[i], balas.balaVel)) {
//                posX[i] = -1;
//                posY[i] = -1;
//            }
//            for(j=0;j<MAXMONSTROS;j++) {
//                if(abs(monstrosPosX[j] - posX[i]) < 25 && abs(monstrosPosY[j] - posY[i]) < 25) {
//                    monstrosPosX[j] = -1;
//                    monstrosPosY[j] = -1;
//                    posX[i] = -1;
//                    posY[i] = -1;
//                }
//            }
//        }
//    }
//}
