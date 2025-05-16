#include "raylib.h"
#include <string.h>
#include <stdlib.h>

#define LARGURA 1200
#define ALTURA 800
#define CELULAMATRIZ 50

struct Player
{
    int posX, posY;
    int velocidadeMovimento;
    int tamanhoPersonagem;
};

struct Monster
{
    int posX, posY;
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

//Funcao que desenha o jogador continuamente
void DesenhaJogador (struct Player player) {
    DrawRectangle(player.posX, player.posY, player.tamanhoPersonagem, player.tamanhoPersonagem, LIME);
}

//Funcao que recebe uma direcao (U, D, L, R), uma matriz mapa e movimento o jogador, com restricao de movimento a obstaculos
void MovimentaJogador (char direcao, struct Player player, char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], int *posX, int *posY)
{

    switch (direcao)
    {
    case 'U':
        if (player.posY > 0 &&
                (mapa[(player.posY - 1)/CELULAMATRIZ][(player.posX + player.tamanhoPersonagem - 1)/CELULAMATRIZ] != 'P' &&
                 mapa[(player.posY - 1)/CELULAMATRIZ][player.posX/CELULAMATRIZ] != 'P'))
        {
            *posY -= player.velocidadeMovimento;
        }

        break;
    case 'D':
        if (player.posY < ALTURA - player.tamanhoPersonagem &&
                (mapa[(player.posY + player.tamanhoPersonagem + 1)/CELULAMATRIZ][player.posX/CELULAMATRIZ] != 'P' &&
                 mapa[(player.posY + player.tamanhoPersonagem + 1)/CELULAMATRIZ][(player.posX + player.tamanhoPersonagem - 1)/CELULAMATRIZ] != 'P')
           )
        {
            *posY += player.velocidadeMovimento;
        }

        break;
    case 'L':
        if (player.posX > 0 &&
                (mapa[player.posY/CELULAMATRIZ][(player.posX - 1)/CELULAMATRIZ] != 'P' &&
                 mapa[(player.posY + player.tamanhoPersonagem - 1)/CELULAMATRIZ][(player.posX - 1)/CELULAMATRIZ] != 'P')
           )
        {
            *posX -= player.velocidadeMovimento;
        }

        break;
    case 'R':
        if (player.posX < LARGURA - player.tamanhoPersonagem &&
                (mapa[player.posY/CELULAMATRIZ][(player.posX + player.tamanhoPersonagem + 1)/CELULAMATRIZ] != 'P' &&
                 mapa[(player.posY + player.tamanhoPersonagem - 1)/CELULAMATRIZ][(player.posX + player.tamanhoPersonagem + 1)/CELULAMATRIZ] != 'P')
           )
        {
            *posX += player.velocidadeMovimento;
        }

        break;
    default:
        break;
    }

}

int main()
{
    //Criar o player:
    struct Player player;

    //Codigo dedicado a mecanica de monstros
    //struct Monster monsters[] = {{8,1},{1,3},{8,5}};
    //int numMonsters = sizeof(monsters) / sizeof(monsters[0]);


    //Cria a matriz contendo as posicoes iniciais do jogo, com P = parede, J = jogador
    char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ] =
    {
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'J', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'P', 'P', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'P', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', 'P', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', 'P', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', 'P', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    };

//    int i, j;

    //define velocidade do jogador e tamanho
    player.velocidadeMovimento = 5;
    player.tamanhoPersonagem = 50;

    //Varre o mapa fornecido e posiciona o jogador inicialmente

    PosicionaJogadorInicialmente(mapa, &player.posX, &player.posY);

    InitWindow(LARGURA, ALTURA, "Zinf"); //Inicializa janela, com certo tamanho e titulo
    SetTargetFPS(60);// Ajusta a janela para 60 frames por segundo

    //Este laco repete enquanto a janela nao for fechada
    //Utilizamos ele para atualizar o estado do programa / jogo
    while (!WindowShouldClose())
    {
        //Movimento do jogador, com movimento continuo e com mecanica de colisao implementada
        if(IsKeyDown(KEY_UP))
        {
            MovimentaJogador('U', player, mapa, &player.posX, &player.posY);
        }

        if(IsKeyDown(KEY_DOWN))
        {
            MovimentaJogador('D', player, mapa, &player.posX, &player.posY);
        }

        if(IsKeyDown(KEY_LEFT))
        {
            MovimentaJogador('L', player, mapa, &player.posX, &player.posY);
        }

        if(IsKeyDown(KEY_RIGHT))
        {
            MovimentaJogador('R', player, mapa, &player.posX, &player.posY);
        }


        // Atualiza o que eh mostrado na tela a partir do estado do jogo
        BeginDrawing(); //Inicia o ambiente de desenho na tela
        ClearBackground(RAYWHITE); //Limpa a tela e define cor de fundo
        DesenhaJogador(player);
        DesenhaMapa(mapa);

//        for(i=0; i<numMonsters; i++)
//        {
//            DrawRectangle(monsters[i].posX*50,monsters[i].posY*50,50,50,RED);
//        }
        EndDrawing(); //Finaliza o ambiente de desenho na tela
    }

    CloseWindow(); // Fecha a janela
    return 0;
}
