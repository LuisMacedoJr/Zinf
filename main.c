#include "raylib.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#include "jogador.h"
#include "mapa.h"
#include "monstros.h"
#include "ataque_dano.h"
#include "variaveis_globais.h"
#include "estruturas.h"
#include "menu.h"


//#define DEBUG

int main()
{
    //Criar as estruturas:
    struct Player player;

    //Preenche o player com valores pre-estabelecidos
    CriaPlayer(&player);

    //Cria array de obstaculos:
    struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)];
    int numeroDeObstaculos = 0;

    //Cria array de monstros:
    struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)];
    int numeroDeMonstros = 0;

    //Cria chicote:
    struct Chicote chicote;

    //Cria array de balas:
    struct Bala balas[MAXIMODEBALAS];
    CriaBalas(balas);



#ifdef DEBUG

    char distanciaString[20] = {'\0'};
    float distanciaFloat;

    char timerMovimento[20] = {'\0'};

#endif // DEBUG

    //Inicialização da seed
    srand(time(NULL));

    //Cria a matriz contendo as posicoes iniciais do jogo, com P = parede, J = jogador
    char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ] =
    {
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'M', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', 'M', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'M', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'J', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'V', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'P', 'P', '-', '-', 'M', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'P', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', 'P', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', 'V', '-', '-', '-', '-', 'P', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', 'P', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', 'M', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'M', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'M', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    };



    //Inicializa as balas
    //InicializaBalas(balas.posX,balas.posY,&balas.balaVel);

    //Varre o mapa fornecido e posiciona o jogador inicialmente
    PosicionaPlayerInicialmente(mapa, &player);

    //Preenche array de obstaculos
    CriaObstaculos(mapa, obstaculos, &numeroDeObstaculos);

    //Preenche array de monstros
    CriaMonstros(mapa, monstros, &numeroDeMonstros);
    int numeroDeMonstrosVivos = numeroDeMonstros;

    InitWindow(LARGURA, ALTURA + ALTURABARRASTATUS, "Zinf"); //Inicializa janela, com certo tamanho e titulo
    SetTargetFPS(FPS);// Ajusta a janela para 60 frames por segundo

    //Este laco repete enquanto a janela nao for fechada
    //Utilizamos ele para atualizar o estado do programa / jogo
    while (!WindowShouldClose())
    {

        //Movimento do jogador
        if(DuasTeclas())
        {
            MovimentaPlayer(player.orientacao, obstaculos, &player, numeroDeObstaculos);

        }
        else
        {
            if(IsKeyDown(KEY_W))
            {
                MovimentaPlayer('U', obstaculos, &player, numeroDeObstaculos);
            }
            if(IsKeyDown(KEY_S))
            {
                MovimentaPlayer('D', obstaculos, &player, numeroDeObstaculos);
            }
            if(IsKeyDown(KEY_A))
            {
                MovimentaPlayer('L', obstaculos, &player, numeroDeObstaculos);
            }
            if(IsKeyDown(KEY_D))
            {
                MovimentaPlayer('R', obstaculos, &player, numeroDeObstaculos);
            }

        }

        //Ataque com chicote
        if(IsKeyDown(KEY_J))
        {
            AtacaChicote(player, &chicote);

        }
        else
        {
            chicote.ataque = false;
        }

        if(IsKeyPressed(KEY_K))
        {
            Atira(&player, balas);

        }


        //Detecção de colisão com vida
        if(ChecaColisaoPlayerObstaculos(obstaculos, player, numeroDeObstaculos, player.orientacao, 'V'))
        {
            player.vidas++;
        }


        //Checa colisao e ataque entre o player e os monstros
        ChecaColisaoPlayerMonstros(monstros, &player, numeroDeMonstros, obstaculos, numeroDeObstaculos);

        ChecaColisaoChicoteMonstros(monstros, &chicote, numeroDeMonstros, obstaculos, numeroDeObstaculos, &player);

        AtualizaBalas(balas, obstaculos, numeroDeObstaculos, monstros, numeroDeMonstros, &player);

        //Atualiza valor da distancia de cada monstro em relacao ao player
        AtualizaDistanciaMonstroPlayer(monstros, player, numeroDeMonstros);

        //Atualiza timer e status dos monstros, baseado no ciclo espera-movimento
        AtualizaTimerMonstros(monstros, numeroDeMonstros);

        AtualizaStatusMonstros(monstros, numeroDeMonstros, player);

        AtualizaTimerPlayer (&player);

        AtualizaNumeroDeMonstrosVivos(monstros, numeroDeMonstros, &numeroDeMonstrosVivos);


        //Executa movimento setado pelo status e timer
        MovimentoAutomaticoMonstros(monstros, numeroDeMonstros, obstaculos, numeroDeObstaculos);

        // Atualiza o que eh mostrado na tela a partir do estado do jogo
        BeginDrawing(); //Inicia o ambiente de desenho na tela
        ClearBackground(RAYWHITE); //Limpa a tela e define cor de fundo
        DesenhaBarraStatus(player);


        if (player.vidas <= 0)
        {
            DesenhaGameOver();
        }
        else if (numeroDeMonstrosVivos <= 0)
        {
            DesenhaFimDoNivel();
        }
        else
        {
            DesenhaMapa(obstaculos, numeroDeObstaculos);
            DesenhaJogador(player);
            DesenhaChicote(chicote);
            DesenhaMonstros(monstros, numeroDeMonstros);
            DesenhaBalas(balas);
        }






#ifdef DEBUG

        sprintf(distanciaString, "%d", numeroDeMonstrosVivos);
        DrawText(distanciaString, 25, 60, 50, GREEN);

        sprintf(timerMovimento, "%g", player.hitbox.y);
        DrawText(timerMovimento, 25, 120, 50, GREEN);


#endif

        EndDrawing(); //Finaliza o ambiente de desenho na tela
    }

    CloseWindow(); // Fecha a janela
    return 0;
}
