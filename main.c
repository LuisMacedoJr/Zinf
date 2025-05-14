#include "raylib.h"
#include <string.h>
#include <stdlib.h>

#define LARGURA 1200
#define ALTURA 800

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

struct Obstaculo
{
    int posX, posY;
    int tamanhoObstaculo;
};



int main()
{
    //Criar o player:
    struct Player player;
    struct Monster monsters[] = {{8,1},{1,3},{8,5}};
    struct Obstaculo obstaculo;

    //Declaração de variáveis:
    char mapa[ALTURA/50][LARGURA/50] = {{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', 'M', '-'},
        {'-', '-', '-', '-', '-', 'J', '-', '-', '-', '-'},
        {'-', 'M', '-', '-', '-', '-', '-', 'O', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', 'M', '-'}
    };

    int i, j;
    int numMonsters = sizeof(monsters) / sizeof(monsters[0]);

    player.velocidadeMovimento = 5;
    player.tamanhoPersonagem = 50;

    obstaculo.tamanhoObstaculo = 50;


    //Varre o mapa fornecido e posiciona o jogador inicialmente
    for(i=0; i<ALTURA/50; i++)
    {
        for(j=0; j<LARGURA/50; j++)
        {
            if(mapa[i][j] == 'J')
            {
                player.posX = i*50;
                player.posY = j*50;
            }
            if(mapa[i][j] == 'O')
            {
                obstaculo.posX = i*50;
                obstaculo.posY = j*50;
            }
        }
    }

    InitWindow(LARGURA, ALTURA, "Zinf"); //Inicializa janela, com certo tamanho e titulo
    SetTargetFPS(60);// Ajusta a janela para 60 frames por segundo

    //Este laco repete enquanto a janela nao for fechada
    //Utilizamos ele para atualizar o estado do programa / jogo
    while (!WindowShouldClose())
    {

        //Movimento do jogador:
        if(IsKeyDown(KEY_UP) && player.posY > 0 &&
           (player.posY != obstaculo.posY + obstaculo.tamanhoObstaculo ||
            player.posX > obstaculo.posX + obstaculo.tamanhoObstaculo ||
            player.posX + player.tamanhoPersonagem < obstaculo.posX)
            )
        {
            player.posY -= player.velocidadeMovimento;
        }
        if(IsKeyDown(KEY_DOWN) && player.posY < ALTURA - player.tamanhoPersonagem)
        {
            player.posY += player.velocidadeMovimento;
        }
        if(IsKeyDown(KEY_LEFT) && player.posX > 0)
        {
            player.posX -= player.velocidadeMovimento;
        }
        if(IsKeyDown(KEY_RIGHT) && player.posX < LARGURA - player.tamanhoPersonagem)
        {
            player.posX += player.velocidadeMovimento;
        }

        // Atualiza o que eh mostrado na tela a partir do estado do jogo
        BeginDrawing(); //Inicia o ambiente de desenho na tela
        ClearBackground(RAYWHITE); //Limpa a tela e define cor de fundo
        DrawRectangle(player.posX, player.posY, player.tamanhoPersonagem, player.tamanhoPersonagem, LIME);
        DrawRectangle(obstaculo.posX, obstaculo.posY, obstaculo.tamanhoObstaculo, obstaculo.tamanhoObstaculo, BLUE);
//        for(i=0; i<numMonsters; i++)
//        {
//            DrawRectangle(monsters[i].posX*50,monsters[i].posY*50,50,50,RED);
//        }
        EndDrawing(); //Finaliza o ambiente de desenho na tela
    }

    CloseWindow(); // Fecha a janela
    return 0;
}
