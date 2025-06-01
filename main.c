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


//#define DEBUG

int main()
{
    //Criar as estruturas:
    struct Player player;
    struct Balas balas;

    //Cria array de obstaculos:
    struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)];
    int numeroDeObstaculos = 0;

    //Cria array de monstros:
    struct Monstro monstros[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)];
    int numeroDeMonstros = 0;


#ifdef DEBUG
    Rectangle rec1 = {0, 0, CELULAMATRIZ, CELULAMATRIZ};
#endif // DEBUG

    //Variável para loops
    int i;

    //Inicialização da seed
    srand(time(NULL));

    //Cria a matriz contendo as posicoes iniciais do jogo, com P = parede, J = jogador
    char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ] =
    {
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'M', '-', '-', 'M', '-', '-', '-', '-'},
        {'-', '-', '-', '-', 'M', '-', '-', '-', '-', '-', '-', '-', '-', 'M', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
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

    //Define tamanho e velocidade do jogador
    player.tamanhoPersonagem = CELULAMATRIZ;
    player.velocidadeMovimento = 5;
    player.vidas = 3;
    player.armaAtual = 'P';
    player.balas = 999;

    //Inicializa as balas
    InicializaBalas(balas.posX,balas.posY,&balas.balaVel);

    //Define variáveis dos monstros
//    monstros.raioVisao = 200;
//    monstros.velocidadeMovimento = 3;

    //Varre o mapa fornecido e posiciona o jogador inicialmente
    PosicionaJogadorInicialmente(mapa, &player);

    //Cria array de obstaculos
    CriaObstaculos(mapa, obstaculos, &numeroDeObstaculos);

    //Setar posições iniciais dos monstros
    CriaMonstros(mapa, monstros, &numeroDeMonstros);

    InitWindow(LARGURA, ALTURA, "Zinf"); //Inicializa janela, com certo tamanho e titulo
    SetTargetFPS(60);// Ajusta a janela para 60 frames por segundo

    //Este laco repete enquanto a janela nao for fechada
    //Utilizamos ele para atualizar o estado do programa / jogo
    while (!WindowShouldClose())
    {

        //Movimento do jogador
        if(DuasTeclas())
        {
            MovimentaJogador(player.orientacao, obstaculos, &player, numeroDeObstaculos);

        }
        else
        {
            if(IsKeyDown(KEY_W))
            {
                MovimentaJogador('U', obstaculos, &player, numeroDeObstaculos);
            }
            if(IsKeyDown(KEY_S))
            {
                MovimentaJogador('D', obstaculos, &player, numeroDeObstaculos);
            }
            if(IsKeyDown(KEY_A))
            {
                MovimentaJogador('L', obstaculos, &player, numeroDeObstaculos);
            }
            if(IsKeyDown(KEY_D))
            {
                MovimentaJogador('R', obstaculos, &player, numeroDeObstaculos);
            }

        }

        //Detecção de colisão com vida
        if(ChecaColisaoPlayerObstaculos(obstaculos, player, numeroDeObstaculos, player.orientacao, 'V'))
        {
            player.vidas++;
        }
//
//        //Atirar
//        if(IsKeyPressed(KEY_J) && player.balas > 0) {
//            Atirar(player, balas, mapa, balas.posX, balas.posY, &balas.direcao);
//            player.balas--;
//        }
//        //Mover Balas
//        AtualizaBalas(balas,monstros,balas.posX,balas.posY,monstros.posX,monstros.posY,mapa);

//        //Lógica Monstros
//        //Calcula as distâncias até o player

        AtualizaDistanciaMonstroPlayer(monstros, player, numeroDeMonstros);

        ChecaColisaoPlayerMonstros(monstros, &player, numeroDeMonstros, obstaculos, numeroDeObstaculos);


        AtualizaMonstros(monstros, numeroDeMonstros, obstaculos, numeroDeObstaculos);
        for (i = 0; i < numeroDeMonstros; i++)
        {
        MovimentoAutomaticoMonstro(&monstros[i], obstaculos, numeroDeObstaculos);
        }


//        for(i=0;i<monstros.quantidadeMonstros;i++) {
//            if(monstros.posX[i] != -1 && monstros.posY[i] != -1) {
//                //Detecta se o monstro deve mover, e, se sim, move ele até ficar a pelo menos 25 pixels de distância do player, também reseta o timer de movimento
//                if(MonstroDeveMover(monstros, player, i) && monstros.ataqueStun[i] <= 0) {
//                //Enterra o monstro
//                monstros.enterrado[i] = 1;
//                if(monstros.posX[i] - player.posX < -25) {
//                    Movimenta('R', mapa, &monstros.posX[i], &monstros.posY[i], monstros.velocidadeMovimento);
//                } else if(monstros.posX[i] - player.posX > 25) {
//                    Movimenta('L', mapa, &monstros.posX[i], &monstros.posY[i], monstros.velocidadeMovimento);
//                } else if(monstros.posY[i] - player.posY < -25) {
//                    Movimenta('D', mapa, &monstros.posX[i], &monstros.posY[i], monstros.velocidadeMovimento);
//                } else if(monstros.posY[i] - player.posY > 25) {
//                    Movimenta('U', mapa, &monstros.posX[i], &monstros.posY[i], monstros.velocidadeMovimento);
//                }
//                //Se o monstro estiver em cima do player, desenterra e fica parado
//                else {
//                    Knockback(&player.posX,&player.posY,monstros.posX[i],monstros.posY[i], 50, 20, mapa);
//                    monstros.enterrado[i] = 0;
//                    monstros.ataqueStun[i] = 50;
//                    player.vidas--;
//                }
//                monstros.timerMovimento[i] = 500;
//            }
        //Se o player não estiver dentro do raio de visão, detecta se o timer de movimento é <= 0. Se sim (o inimigo deve se mover), escolhe um ponto aleatório entre 100 e 200 pixels de sua posição e reseta o timer

//                //Se não, move até o ponto e fica parado.
//                else if(monstros.timerMovimento[i] <= 300) {
//                if(monstros.posX[i] - monstros.pontoX[i] < -25) {
//                    Movimenta('R', mapa, &monstros.posX[i], &monstros.posY[i], monstros.velocidadeMovimento);
//                } else if(monstros.posX[i] - monstros.pontoX[i] > 25) {
//                    Movimenta('L', mapa, &monstros.posX[i], &monstros.posY[i], monstros.velocidadeMovimento);
//                } else if(monstros.posY[i] - monstros.pontoY[i] < -25) {
//                    Movimenta('D', mapa, &monstros.posX[i], &monstros.posY[i], monstros.velocidadeMovimento);
//                } else if(monstros.posY[i] - monstros.pontoY[i] > 25) {
//                    Movimenta('U', mapa, &monstros.posX[i], &monstros.posY[i], monstros.velocidadeMovimento);
//                }
//            }
//                //Decrementa o timer e o stun de ataque
//                monstros.timerMovimento[i]--;
//                monstros.ataqueStun[i]--;
//            }
//        }
//


        // Atualiza o que eh mostrado na tela a partir do estado do jogo
        BeginDrawing(); //Inicia o ambiente de desenho na tela
        ClearBackground(RAYWHITE); //Limpa a tela e define cor de fundo
        DesenhaJogador(player);
//        DesenhaMonstros(monstros, numeroDeMonstros);
        DesenhaVidas(player);
//        DesenhaBalas(balas);
        DesenhaMapa(obstaculos, numeroDeObstaculos);

#ifdef DEBUG

        DrawRectangleRec(rec1, ORANGE);

#endif

        EndDrawing(); //Finaliza o ambiente de desenho na tela
    }

    CloseWindow(); // Fecha a janela
    return 0;
}
