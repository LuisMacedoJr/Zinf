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
void AtacaChicote(struct Player player, struct Chicote *chicote) {
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


//Inicializa o array de balas
void CriaBalas(struct Bala balas[MAXIMODEBALAS])
{
    int i;

    for (i = 0; i < MAXIMODEBALAS; i++)
    {
        balas[i].ataque = false;
        balas[i].velocidadeBala = 10;
    }

}

//Funcao que atira e posiciona uma bala dentro do array de balas
void Atira(struct Player *player, struct Bala balas[MAXIMODEBALAS])
{
    bool atirou = false;

    int i;
    if (!player->atirando && player->municao > 0)
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


// Checa colisao entre uma bala e as paredes, impedindo sua passagem
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


// Movimenta a bala ao longo do cenario
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

//Atualiza status de cada bala no array de balas, afim de checar se a mesma atingiu algum monstro, parede ou saiu do cenario
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


//Checa se uma bala atingiu algum monstro, aplica o dano e faz a bala desaparecer
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


//Desenha o array de balas na tela
void DesenhaBalas (struct Bala balas[MAXIMODEBALAS])
{
    int i;

    for (i = 0; i < MAXIMODEBALAS; i++)
    {
        if (balas[i].ataque)
        {
            DrawRectangleRec(balas[i].hitbox, DARKGRAY);
        }
    }
}

