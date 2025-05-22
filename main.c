#include "raylib.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define LARGURA 1200
#define ALTURA 800
#define CELULAMATRIZ 50
#define MAXMONSTROS 20

struct Player
{
    int posX, posY, tamanhoPersonagem;;
    int velocidadeMovimento;
};

struct Monstros
{
    int quantidadeMonstros, posX[MAXMONSTROS], posY[MAXMONSTROS], enterrado[MAXMONSTROS], pontoX[MAXMONSTROS], pontoY[MAXMONSTROS], timerMovimento[MAXMONSTROS], ataqueStun[MAXMONSTROS];
    int velocidadeMovimento, raioVisao;
    float distPlayer[MAXMONSTROS];
};

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

//Lê o mapa e guarda as posições dos montros nas variáveis posX e posY da estrutura Monstros, além da quantidade de monstros no mapa inteiro
void CriaMonstros(char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], int posX[], int posY[], int enterrado[], int timerMovimento[], int pontoX[], int pontoY[], int ataqueStun[], int *quantidadeMonstros) {
    int i, j, iMonstro = 0;
    for(i=0;i<MAXMONSTROS;i++) {
        posX[i] = -1;
        posY[i] = -1;
        enterrado[i] = 0;
        timerMovimento[i] = 300;
        pontoX[i] = -1;
        pontoY[i] = -1;
        ataqueStun[i] = 0;
    }
    for(i=0;i<ALTURA/CELULAMATRIZ;i++) {
        for(j=0;j<LARGURA/CELULAMATRIZ;j++) {
            if(mapa[i][j] == 'M') {
                posX[iMonstro] = j*CELULAMATRIZ;
                posY[iMonstro] = i*CELULAMATRIZ;
                pontoX[iMonstro] = posX[iMonstro];
                pontoY[iMonstro] = posY[iMonstro];
                iMonstro++;
            }
        }
    }
    *quantidadeMonstros = iMonstro;
}

//Função que calcula distância entre dois pontos
float CalculaDist(int x1, int y1, int x2, int y2) {
    return(sqrt(pow((x1-x2),2)+pow((y1-y2),2)));
}

//Calcula a distância entre cada monstro e o player
void DistMonstroPlayer(int posX[], int posY[], float distPlayer[], struct Player player, struct Monstros monstros) {
    int i;
    for(i=0;i<monstros.quantidadeMonstros;i++) {
        distPlayer[i] = CalculaDist(posX[i],posY[i],player.posX,player.posY);
    }
}

//Determina se o monstro deveria se mexer ou não baseado em sua distância até o player
int MonstroDeveMover(struct Monstros monstros, struct Player player, int i) {
    if(abs(monstros.posX[i] - player.posX) <= monstros.raioVisao && abs(monstros.posY[i] - player.posY) <= monstros.raioVisao) {
        return 1;
    } else {
        return 0;
    }
}

//Funcao que dada uma matriz mapa, desenha os obstaculos marcados como P
void DesenhaMapa (char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ])
{
    char *p;
    int posX, posY;

    for(p = &mapa[0][0]; p <= &mapa[(ALTURA/CELULAMATRIZ) - 1][(LARGURA/CELULAMATRIZ) - 1]; p++)
    {
        if (*p == 'P')
        {
            posX = ((p - &mapa[0][0]) % (LARGURA/CELULAMATRIZ))*CELULAMATRIZ;
            posY = ((p - &mapa[0][0]) / (LARGURA/CELULAMATRIZ))*CELULAMATRIZ;
            DrawRectangle(posX, posY, CELULAMATRIZ, CELULAMATRIZ, BLUE);
        }
    }

}

//Funcao que desenha o jogador
void DesenhaJogador (struct Player player) {
    DrawRectangle(player.posX, player.posY, player.tamanhoPersonagem, player.tamanhoPersonagem, LIME);
}

//Funcao que desenha os monstros
void DesenhaMonstros(struct Monstros monstros, struct Player player) {
    int i;
    for(i=0;i<MAXMONSTROS;i++) {
        if(monstros.posX[i] != -1 && monstros.posY[i] != -1 && MonstroDeveMover(monstros, player, i) == 0)
            DrawRectangle(monstros.posX[i], monstros.posY[i], CELULAMATRIZ, CELULAMATRIZ, RED);
        if(monstros.posX[i] != -1 && monstros.posY[i] != -1 && MonstroDeveMover(monstros, player, i) == 1)
            DrawRectangle(monstros.posX[i], monstros.posY[i], CELULAMATRIZ, CELULAMATRIZ, ORANGE);
    }
}

//Funcao que recebe uma direcao (U, D, L, R), uma matriz mapa e movimenta um objeto, com restricao de movimento a obstaculos (genérica)
void Movimenta (char direcao, char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], int *posX, int *posY, int vel)
{

    switch (direcao)
    {
    case 'U':
        if (*posY > 0 &&
                (mapa[(*posY - 1)/CELULAMATRIZ][(*posX + CELULAMATRIZ - 1)/CELULAMATRIZ] != 'P' &&
                 mapa[(*posY - 1)/CELULAMATRIZ][*posX/CELULAMATRIZ] != 'P'))
        {
            *posY -= vel;
        }

        break;
    case 'D':
        if (*posY < ALTURA - CELULAMATRIZ &&
                (mapa[(*posY + CELULAMATRIZ + 1)/CELULAMATRIZ][*posX/CELULAMATRIZ] != 'P' &&
                 mapa[(*posY + CELULAMATRIZ + 1)/CELULAMATRIZ][(*posX + CELULAMATRIZ - 1)/CELULAMATRIZ] != 'P')
           )
        {
            *posY += vel;
        }

        break;
    case 'L':
        if (*posX > 0 &&
                (mapa[*posY/CELULAMATRIZ][(*posX - 1)/CELULAMATRIZ] != 'P' &&
                 mapa[(*posY + CELULAMATRIZ - 1)/CELULAMATRIZ][(*posX - 1)/CELULAMATRIZ] != 'P')
           )
        {
            *posX -= vel;
        }

        break;
    case 'R':
        if (*posX < LARGURA - CELULAMATRIZ &&
                (mapa[*posY/CELULAMATRIZ][(*posX + CELULAMATRIZ + 1)/CELULAMATRIZ] != 'P' &&
                 mapa[(*posY + CELULAMATRIZ - 1)/CELULAMATRIZ][(*posX + CELULAMATRIZ + 1)/CELULAMATRIZ] != 'P')
           )
        {
            *posX += vel;
        }

        break;
    default:
        break;
    }

}

//Aplica knockback ao levar dano. Recebe um int força e tolerancia, a qual indica a que distância do centro é preciso estar para levar knockback em duas direções (genérica)
void Knockback(int *x1, int *y1, int x2, int y2, int forca, int tolerancia, char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ]) {
    if(x2 - *x1 > tolerancia) {
        Movimenta('L',mapa,x1,y1,forca);
    }
    if(x2 - *x1 < -tolerancia) {
        Movimenta('R',mapa,x1,y1,forca);
    }
    if(y2 - *y1 > tolerancia) {
        Movimenta('U',mapa,x1,y1,forca);
    }
    if(y2 - *y1 < -tolerancia) {
        Movimenta('D',mapa,x1,y1,forca);
    }
}

int main()
{
    //Criar o player e a lista de monstros:
    struct Player player;
    struct Monstros monstros;

    //Variável para loops
    int i;

    //Inicialização da seed
    srand(time(NULL));

    //Cria a matriz contendo as posicoes iniciais do jogo, com P = parede, J = jogador
    char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ] =
    {
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'M', '-', '-', '-', '-'},
        {'-', '-', '-', '-', 'M', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'J', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'P', 'P', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'P', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', 'P', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', 'P', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', 'P', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'M', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    };

    //Define tamanho e velocidade do jogador
    player.tamanhoPersonagem = CELULAMATRIZ;
    player.velocidadeMovimento = 5;

    //Define variáveis dos monstros
    monstros.raioVisao = 200;
    monstros.velocidadeMovimento = 3;

    //Varre o mapa fornecido e posiciona o jogador inicialmente
    PosicionaJogadorInicialmente(mapa, &player.posX, &player.posY);

    //Setar posições iniciais dos monstros
    CriaMonstros(mapa,monstros.posX,monstros.posY,monstros.enterrado,monstros.timerMovimento,monstros.pontoX,monstros.pontoY,monstros.ataqueStun,&monstros.quantidadeMonstros);

    InitWindow(LARGURA, ALTURA, "Zinf"); //Inicializa janela, com certo tamanho e titulo
    SetTargetFPS(60);// Ajusta a janela para 60 frames por segundo

    //Este laco repete enquanto a janela nao for fechada
    //Utilizamos ele para atualizar o estado do programa / jogo
    while (!WindowShouldClose())
    {
        //Movimento do jogador
        if(IsKeyDown(KEY_W))
            Movimenta('U', mapa, &player.posX, &player.posY, player.velocidadeMovimento);
        if(IsKeyDown(KEY_S))
            Movimenta('D', mapa, &player.posX, &player.posY, player.velocidadeMovimento);
        if(IsKeyDown(KEY_A))
            Movimenta('L', mapa, &player.posX, &player.posY, player.velocidadeMovimento);
        if(IsKeyDown(KEY_D))
            Movimenta('R', mapa, &player.posX, &player.posY, player.velocidadeMovimento);



        //Lógica Monstros
        //Calcula as distâncias até o player
        DistMonstroPlayer(monstros.posX,monstros.posY,monstros.distPlayer,player,monstros);
        for(i=0;i<monstros.quantidadeMonstros;i++) {
            //Detecta se o monstro deve mover, e, se sim, move ele até ficar a pelo menos 25 pixels de distância do player, também reseta o timer de movimento
            if(MonstroDeveMover(monstros, player, i) && monstros.ataqueStun[i] <= 0) {
                //Enterra o monstro
                monstros.enterrado[i] = 1;
                if(monstros.posX[i] - player.posX < -25) {
                    Movimenta('R', mapa, &monstros.posX[i], &monstros.posY[i], monstros.velocidadeMovimento);
                } else if(monstros.posX[i] - player.posX > 25) {
                    Movimenta('L', mapa, &monstros.posX[i], &monstros.posY[i], monstros.velocidadeMovimento);
                } else if(monstros.posY[i] - player.posY < -25) {
                    Movimenta('D', mapa, &monstros.posX[i], &monstros.posY[i], monstros.velocidadeMovimento);
                } else if(monstros.posY[i] - player.posY > 25) {
                    Movimenta('U', mapa, &monstros.posX[i], &monstros.posY[i], monstros.velocidadeMovimento);
                }
                //Se o monstro estiver em cima do player, desenterra e fica parado
                else {
                    Knockback(&player.posX,&player.posY,monstros.posX[i],monstros.posY[i], 50, 20, mapa);
                    monstros.enterrado[i] = 0;
                    monstros.ataqueStun[i] = 50;
                }
                monstros.timerMovimento[i] = 500;
            }
            //Se o player não estiver dentro do raio de visão, detecta se o timer de movimento é <= 0. Se sim (o inimigo deve se mover), escolhe um ponto aleatório entre 100 e 200 pixels de sua posição e reseta o timer
            else if(monstros.timerMovimento[i] <= 0) {
                monstros.timerMovimento[i] = 300;
                monstros.pontoX[i] = monstros.posX[i] + ((rand() % 5) - 2) * 100;
                monstros.pontoY[i] = monstros.posY[i] + ((rand() % 5) - 2) * 100;
            }
            //Se não, move até o ponto e fica parado.
            else if(monstros.timerMovimento[i] <= 300) {
                if(monstros.posX[i] - monstros.pontoX[i] < -25) {
                    Movimenta('R', mapa, &monstros.posX[i], &monstros.posY[i], monstros.velocidadeMovimento);
                } else if(monstros.posX[i] - monstros.pontoX[i] > 25) {
                    Movimenta('L', mapa, &monstros.posX[i], &monstros.posY[i], monstros.velocidadeMovimento);
                } else if(monstros.posY[i] - monstros.pontoY[i] < -25) {
                    Movimenta('D', mapa, &monstros.posX[i], &monstros.posY[i], monstros.velocidadeMovimento);
                } else if(monstros.posY[i] - monstros.pontoY[i] > 25) {
                    Movimenta('U', mapa, &monstros.posX[i], &monstros.posY[i], monstros.velocidadeMovimento);
                }
            }
            //Decrementa o timer e o stun de ataque
            monstros.timerMovimento[i]--;
            monstros.ataqueStun[i]--;
        }



        // Atualiza o que eh mostrado na tela a partir do estado do jogo
        BeginDrawing(); //Inicia o ambiente de desenho na tela
        ClearBackground(RAYWHITE); //Limpa a tela e define cor de fundo
        DesenhaJogador(player);
        DesenhaMonstros(monstros,player);
        DesenhaMapa(mapa);

        EndDrawing(); //Finaliza o ambiente de desenho na tela
    }

    CloseWindow(); // Fecha a janela
    return 0;
}
