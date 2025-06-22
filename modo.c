#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#include "raylib.h"
#include "jogador.h"
#include "monstros.h"
#include "modo.h"
#include "menu.h"
#include "mapa.h"
#include "variaveis_globais.h"
#include "ataque_dano.h"

void ModoJogo(struct Jogo *jogo, struct Jogo jogosSalvos[])
{

    //Criar as estruturas:
    struct Player player;

    //Preenche o player com valores pre-estabelecidos
    CriaPlayer(&player, *jogo);

    struct Seta seta;
    CriaSeta(&seta, PAUSE);

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
    char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ] = {'\0'};
    LeMapa(*jogo, mapa);


    //Varre o mapa fornecido e posiciona o jogador inicialmente
    PosicionaPlayerInicialmente(mapa, &player);

    //Preenche array de obstaculos
    CriaObstaculos(mapa, obstaculos, &numeroDeObstaculos);

    //Preenche array de monstros
    CriaMonstros(mapa, monstros, &numeroDeMonstros);
    int numeroDeMonstrosVivos = numeroDeMonstros;


    //Criação das texturas
    Texture2D TexturaPlayer = LoadTexture("textures/player/empty_handed.png");
    Texture2D TexturaMonstro = LoadTexture("textures/monstros/snake.png");
    Texture2D TexturaChao = LoadTexture("textures/ground.png");

    //Este laco repete enquanto a janela nao for fechada
    //Utilizamos ele para atualizar o estado do programa / jogo
    while (!WindowShouldClose() && (jogo->modoDeJogo == JOGO || jogo->modoDeJogo == PAUSE))
    {

        //Movimento do jogador
        if (jogo->modoDeJogo != PAUSE)
        {
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
        }
        PlayerParado(&player);

        //Atualiza os contadores de frames
        AtualizaTimerAnimacaoPlayer(&player);
        AtualizaTimerAnimacaoMonstro(monstros,numeroDeMonstros);

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

        if(IsKeyPressed(KEY_P))
        {
            jogo->modoDeJogo = PAUSE;
        }


        //Detecção de colisão com vida
        if(ChecaColisaoPlayerObstaculos(obstaculos, player, numeroDeObstaculos, player.orientacao, 'V'))
        {
            player.vidas++;
        }


        //Checa colisao e ataque entre o player e os monstros
        ChecaColisaoPlayerMonstros(monstros, &player, numeroDeMonstros, obstaculos, numeroDeObstaculos);

        ChecaColisaoChicoteMonstros(monstros, &chicote, numeroDeMonstros, obstaculos, numeroDeObstaculos, &player);

        if (player.vidas <= 0)
        {
            jogo->score = player.score;
            jogo->modoDeJogo = GAMEOVER;
        }

        if (numeroDeMonstrosVivos <= 0)
        {
            jogo->score = player.score;
            jogo->vidasDoPlayer = player.vidas;
            jogo->nivel = jogo->nivel + 1;
            jogo->municao = player.municao;
            jogo->armaAtual = player.armaAtual;
            jogo->modoDeJogo = TELAENTRENIVEIS;
        }

        if (jogo->modoDeJogo != PAUSE)
        {
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
        }
        if(jogo->modoDeJogo == PAUSE)
        {
            MovimentaSeta(&seta, PAUSE);
            if (IsKeyPressed(KEY_ENTER))
            {
                switch(seta.opcaoPause)
                {
                case MENUPAUSE_VOLTAR:
                    jogo->modoDeJogo = JOGO;
                    break;
                case MENUPAUSE_SALVAR:
                    SalvaJogo(jogosSalvos, *jogo);
                    break;
                case MENUPAUSE_MENUINICIAL:
                    jogo->modoDeJogo = MENUINICIAL;
                    break;
                case MENUPAUSE_SAIR:
                    jogo->modoDeJogo = FIM;
                    break;
                default:
                    break;

                }
            }

        }

        // Atualiza o que eh mostrado na tela a partir do estado do jogo
        BeginDrawing(); //Inicia o ambiente de desenho na tela

        ClearBackground(RAYWHITE); //Limpa a tela e define cor de fundo
        DesenhaBarraStatus(player);



        DesenhaChao(mapa,TexturaChao);
        DesenhaMapa(obstaculos, numeroDeObstaculos);
        DesenhaJogador(&player,TexturaPlayer);
        DesenhaChicote(chicote);
        DesenhaMonstro(monstros, TexturaMonstro, numeroDeMonstros);
        DesenhaBalas(balas);

        if(jogo->modoDeJogo == PAUSE)
        {
            DesenhaMenuPause(jogo, player, &seta);

        }


#ifdef DEBUG

        sprintf(distanciaString, "%d", numeroDeMonstrosVivos);
        DrawText(distanciaString, 25, 60, 50, GREEN);

        sprintf(timerMovimento, "%g", player.hitbox.y);
        DrawText(timerMovimento, 25, 120, 50, GREEN);


#endif

        EndDrawing(); //Finaliza o ambiente de desenho na tela
    }

}

void ModoTelaInicial(struct Jogo *jogo)
{

    while (jogo->modoDeJogo == TELAINICIAL && !WindowShouldClose())
    {
        if(IsKeyDown(KEY_ENTER))
        {
            jogo->modoDeJogo = MENUINICIAL;
        }
        // Atualiza o que eh mostrado na tela a partir do estado do jogo
        BeginDrawing(); //Inicia o ambiente de desenho na tela
        ClearBackground(BEIGE); //Limpa a tela e define cor de fundo
        DesenhaTitulo();

        EndDrawing(); //Finaliza o ambiente de desenho na tela
    }

}

void ModoMenuInicial(struct Jogo *jogo)
{
    struct Seta seta;
    CriaSeta(&seta, MENUINICIAL);

    while (jogo->modoDeJogo == MENUINICIAL && !WindowShouldClose())
    {
        MovimentaSeta(&seta, MENUINICIAL);

        if (IsKeyPressed(KEY_ENTER))
        {
            switch(seta.opcao)
            {
            case MENUINICIAL_NOVOJOGO:
                IniciaJogo(jogo);
                jogo->modoDeJogo = NOVOJOGO;
                break;
            case MENUINICIAL_CARREGAR:
                jogo->modoDeJogo = CARREGAR;
                break;
            case MENUINICIAL_RANKING:
                jogo->modoDeJogo = RANKING;
                break;
            case MENUINICIAL_SAIR:
                jogo->modoDeJogo = FIM;
                break;
            default:
                break;

            }
        }

        // Atualiza o que eh mostrado na tela a partir do estado do jogo
        BeginDrawing(); //Inicia o ambiente de desenho na tela
        ClearBackground(BEIGE); //Limpa a tela e define cor de fundo
        DesenhaSeta(seta);
        DesenhaOpcoesMenuInicial();


        EndDrawing(); //Finaliza o ambiente de desenho na tela
    }

}

void ModoEntreNiveis(struct Jogo *jogo)
{


    while (jogo->modoDeJogo == TELAENTRENIVEIS && !WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            jogo->modoDeJogo = JOGO;
            break;
        }

        // Atualiza o que eh mostrado na tela a partir do estado do jogo
        BeginDrawing(); //Inicia o ambiente de desenho na tela
        ClearBackground(BEIGE); //Limpa a tela e define cor de fundo
        DesenhaTelaEntreNiveis(*jogo);

        EndDrawing(); //Finaliza o ambiente de desenho na tela
    }

}

void ModoSelecionaJogo(struct Jogo *jogo, int modo, struct Jogo jogosSalvos[])
{
    struct Seta seta;
    CriaSeta(&seta, modo);

    while ((jogo->modoDeJogo == NOVOJOGO || jogo->modoDeJogo == CARREGAR || jogo->modoDeJogo == SALVAR) && !WindowShouldClose())
    {
        MovimentaSeta(&seta, modo);

        if (IsKeyPressed(KEY_ENTER))
        {
            if(seta.save == SAIR) {
                    jogo->modoDeJogo = MENUINICIAL;

            }
            if(jogo->modoDeJogo == NOVOJOGO && !jogosSalvos[seta.save].ocupado)
            {
                IniciaJogo(jogo);
                jogo->saveSlot = seta.save;
                jogo->ocupado = true;
                jogo->modoDeJogo = SELECIONANOME;

            }

            if(jogo->modoDeJogo == CARREGAR && jogosSalvos[seta.save].ocupado)
            {
                CarregaJogo(jogo, jogosSalvos[seta.save]);
                jogo->saveSlot = seta.save;
                jogo->modoDeJogo = TELAENTRENIVEIS;

            }

        }

        // Atualiza o que eh mostrado na tela a partir do estado do jogo
        BeginDrawing(); //Inicia o ambiente de desenho na tela
        ClearBackground(BEIGE); //Limpa a tela e define cor de fundo
        DesenhaSeta(seta);
        DesenhaSaves(jogosSalvos);


        EndDrawing(); //Finaliza o ambiente de desenho na tela
    }


}

void ModoSelecionaNome(struct Jogo *jogo)
{
    char nomeEscrito[25] = {'\0'};
    char caractereDigitado;
    int posicao = 0;

    strncpy(jogo->nome, nomeEscrito, 25);

    while (jogo->modoDeJogo == SELECIONANOME && !WindowShouldClose() && posicao >= 0 && posicao < 25)
    {

            caractereDigitado = GetCharPressed();
            if (caractereDigitado >= 32 && caractereDigitado <= 125 && posicao < 19)
            {
                jogo->nome[posicao] = caractereDigitado;
                posicao++;
            }
            if (IsKeyPressed(KEY_BACKSPACE) && posicao !=0)
            {
                posicao--;
                jogo->nome[posicao] = '\0';
            }

            if (IsKeyPressed(KEY_ENTER)) {
                jogo->modoDeJogo = JOGO;
            }





            // Atualiza o que eh mostrado na tela a partir do estado do jogo
            BeginDrawing(); //Inicia o ambiente de desenho na tela
            ClearBackground(BEIGE); //Limpa a tela e define cor de fundo

            DesenhaNome(*jogo);

            EndDrawing(); //Finaliza o ambiente de desenho na tela

    }

}




void ModoGameOver(struct Jogo *jogo)
{
    SalvaRanking(*jogo);

    while (jogo->modoDeJogo == GAMEOVER && !WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            jogo->modoDeJogo = TELAINICIAL;
            break;
        }

        // Atualiza o que eh mostrado na tela a partir do estado do jogo
        BeginDrawing(); //Inicia o ambiente de desenho na tela
        ClearBackground(BEIGE); //Limpa a tela e define cor de fundo
        DesenhaGameOver();

        EndDrawing(); //Finaliza o ambiente de desenho na tela
    }

}



