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
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', 'J', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
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

    int i, j;

    //define velocidade do jogador e tamanho
    player.velocidadeMovimento = 5;
    player.tamanhoPersonagem = 50;

    //Varre o mapa fornecido e posiciona o jogador inicialmente
    for(i=0; i<ALTURA/CELULAMATRIZ; i++)
    {
        for(j=0; j<LARGURA/CELULAMATRIZ; j++)
        {
            if(mapa[i][j] == 'J')
            {
                player.posX = j*CELULAMATRIZ;
                player.posY = i*CELULAMATRIZ;
            }
        }
    }


    InitWindow(LARGURA, ALTURA, "Zinf"); //Inicializa janela, com certo tamanho e titulo
    SetTargetFPS(60);// Ajusta a janela para 60 frames por segundo

    //Este laco repete enquanto a janela nao for fechada
    //Utilizamos ele para atualizar o estado do programa / jogo
    while (!WindowShouldClose())
    {

        //Movimento do jogador, com movimento continuo e com mecanica de colisao implementada
        if(IsKeyDown(KEY_UP) && player.posY > 0 &&
                (mapa[(player.posY - 1)/CELULAMATRIZ][(player.posX + player.tamanhoPersonagem - 1)/CELULAMATRIZ] != 'P' &&
                 mapa[(player.posY - 1)/CELULAMATRIZ][player.posX/CELULAMATRIZ] != 'P')
          )
        {
            player.posY -= player.velocidadeMovimento;
        }
        if(IsKeyDown(KEY_DOWN) && player.posY < ALTURA - player.tamanhoPersonagem &&
                (mapa[(player.posY + player.tamanhoPersonagem + 1)/CELULAMATRIZ][player.posX/CELULAMATRIZ] != 'P' &&
                 mapa[(player.posY + player.tamanhoPersonagem + 1)/CELULAMATRIZ][(player.posX + player.tamanhoPersonagem - 1)/CELULAMATRIZ] != 'P')
          )
        {
            player.posY += player.velocidadeMovimento;
        }
        if(IsKeyDown(KEY_LEFT) && player.posX > 0 &&
                (mapa[player.posY/CELULAMATRIZ][(player.posX - 1)/CELULAMATRIZ] != 'P' &&
                 mapa[(player.posY + player.tamanhoPersonagem - 1)/CELULAMATRIZ][(player.posX - 1)/CELULAMATRIZ] != 'P')
          )
        {
            player.posX -= player.velocidadeMovimento;
        }
        if(IsKeyDown(KEY_RIGHT) && player.posX < LARGURA - player.tamanhoPersonagem
                &&
                (mapa[player.posY/CELULAMATRIZ][(player.posX + player.tamanhoPersonagem + 1)/CELULAMATRIZ] != 'P' &&
                 mapa[(player.posY + player.tamanhoPersonagem - 1)/CELULAMATRIZ][(player.posX + player.tamanhoPersonagem + 1)/CELULAMATRIZ] != 'P')
          )
        {
            player.posX += player.velocidadeMovimento;
        }

        // Atualiza o que eh mostrado na tela a partir do estado do jogo
        BeginDrawing(); //Inicia o ambiente de desenho na tela
        ClearBackground(RAYWHITE); //Limpa a tela e define cor de fundo
        DrawRectangle(player.posX, player.posY, player.tamanhoPersonagem, player.tamanhoPersonagem, LIME);
        for (i = 0; i < LARGURA/CELULAMATRIZ; i++)
        {
            for (j = 0; j < ALTURA/CELULAMATRIZ; j++)
            {
                if (mapa[j][i] == 'P')
                {
                    DrawRectangle(i*CELULAMATRIZ, j*CELULAMATRIZ, CELULAMATRIZ, CELULAMATRIZ, BLUE);
                }
            }
        }
//        for(i=0; i<numMonsters; i++)
//        {
//            DrawRectangle(monsters[i].posX*50,monsters[i].posY*50,50,50,RED);
//        }
        EndDrawing(); //Finaliza o ambiente de desenho na tela
    }

    CloseWindow(); // Fecha a janela
    return 0;
}




// codigo nao utilizado


 //   struct Obstaculo obstaculo;


//struct Obstaculo
//{
//    int posX, posY;
//    int tamanhoObstaculo;
//};



//
//   (player.posY != obstaculo.posY + obstaculo.tamanhoObstaculo ||
//                 player.posX > obstaculo.posX + obstaculo.tamanhoObstaculo ||
//                 player.posX + player.tamanhoPersonagem < obstaculo.posX ||
//                 paredes[(player.posY/50) - 1][player.posX/50] != 1)
//          )
