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



//Ciclo do modo principal de jogo
void ModoJogo(struct Jogo *jogo, struct Jogo jogosSalvos[])
{

    //Criar as estruturas:
    struct Player player;

    //Preenche o player com valores pre-estabelecidos
    CriaPlayer(&player, *jogo);

    //Cria e preenche a seta (utilizada no menu de pause)
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

        //Deteccao da colisao com chicote, equipando o jogador com a arma
        if(ChecaColisaoPlayerObstaculos(obstaculos, player, numeroDeObstaculos, player.orientacao, 'E'))
        {
            player.armaAtual = 'C';
        }

        //Deteccao da colisao com municao, fornecendo 5 balas ao jogador
        if(ChecaColisaoPlayerObstaculos(obstaculos, player, numeroDeObstaculos, player.orientacao, 'B'))
        {
            player.municao += 5;
        }


        //Checa colisao e ataque entre o player e os monstros
        ChecaColisaoPlayerMonstros(monstros, &player, numeroDeMonstros, obstaculos, numeroDeObstaculos);

        ChecaColisaoChicoteMonstros(monstros, &chicote, numeroDeMonstros, obstaculos, numeroDeObstaculos, &player);

        //Define fim do jogo se o player atingir zero vidas
        if (player.vidas <= 0)
        {
            jogo->score = player.score;
            jogo->modoDeJogo = GAMEOVER;
        }

        //Define passagem de nivel se todos os inimigos estiverem mortos
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
            //Atualiza posicao e colisao das balas
            AtualizaBalas(balas, obstaculos, numeroDeObstaculos, monstros, numeroDeMonstros, &player);

            //Atualiza valor da distancia de cada monstro em relacao ao player
            AtualizaDistanciaMonstroPlayer(monstros, player, numeroDeMonstros);

            //Atualiza timer e status dos monstros, baseado no ciclo espera-movimento
            AtualizaTimerMonstros(monstros, numeroDeMonstros);

            //Atualiza o status do monstro (movendo, esperando, stun), de acordo com o timer atualizado
            AtualizaStatusMonstros(monstros, numeroDeMonstros, player);

            //Atualiza timer do player, para fins de stun, uso da pistola
            AtualizaTimerPlayer (&player);

            //Atualiza a variavel numero de monstros vivos
            AtualizaNumeroDeMonstrosVivos(monstros, numeroDeMonstros, &numeroDeMonstrosVivos);

            //Executa movimento setado pelo status e timer
            MovimentoAutomaticoMonstros(monstros, numeroDeMonstros, obstaculos, numeroDeObstaculos);
        }

        //Atualizacoes do modo de pause
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

        DesenhaBarraStatus(player, *jogo);

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


        EndDrawing(); //Finaliza o ambiente de desenho na tela
    }

}

//Ciclo da tela de apresentacao do jogo
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


//Ciclo do menu inicial, permitindo a selecao das opcoes e atualizacao do modo de jogo
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


//Ciclo da tela entre cada nivel. Realiza o salvamento automatico do jogo
void ModoEntreNiveis(struct Jogo *jogo, struct Jogo jogosSalvos[])
{

    SalvaJogo(jogosSalvos, *jogo);


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


//Ciclo da tela de selecao de jogos salvos
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

//Ciclo da selecao de nome do jogador
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
                jogo->modoDeJogo = TELAENTRENIVEIS;
            }





            // Atualiza o que eh mostrado na tela a partir do estado do jogo
            BeginDrawing(); //Inicia o ambiente de desenho na tela
            ClearBackground(BEIGE); //Limpa a tela e define cor de fundo

            DesenhaNome(*jogo);

            EndDrawing(); //Finaliza o ambiente de desenho na tela

    }

}


//Ciclo do game over. Realiza a atualizacao do ranking com o score do jogador
void ModoGameOver(struct Jogo *jogo, struct Score ranking[])
{
    SalvaRanking(ranking, *jogo);

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


//Ciclo da tela de exibicao do ranking
void ModoRanking(struct Jogo *jogo, struct Score ranking[])
{

    while (jogo->modoDeJogo == RANKING && !WindowShouldClose())
    {

        if (IsKeyPressed(KEY_ENTER))
        {
            jogo->modoDeJogo = MENUINICIAL;
        }


        // Atualiza o que eh mostrado na tela a partir do estado do jogo
        BeginDrawing(); //Inicia o ambiente de desenho na tela
        ClearBackground(BEIGE); //Limpa a tela e define cor de fundo
        DesenhaScores(ranking);


        EndDrawing(); //Finaliza o ambiente de desenho na tela
    }


}




