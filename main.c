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
#include "modo.h"


int main()
{
    //Inicia o jogo, a partir da tela inicial
    struct Jogo jogo;
    IniciaJogo(&jogo);

    //Cria as estruturas que contem os jogos salvos e os scores
    struct Jogo jogosSalvos[5];
    struct Score ranking[5];

    //Realiza a leitura dos arquivos binarios do ranking e de jogo salvo
    CarregaArquivoSave(jogosSalvos);

    CarregaArquivoRanking(ranking);

    InitWindow(LARGURA, ALTURA + ALTURABARRASTATUS, "Zinf"); //Inicializa janela, com certo tamanho e titulo
    SetTargetFPS(FPS);// Ajusta a janela para 60 frames por segundo

    //O ciclo do jogo e realizado a partir da leitura continua do modo de jogo, expresso atraves de uma enumeracao de modos de jogo
    while(jogo.modoDeJogo != FIM && !WindowShouldClose())
    {
        switch(jogo.modoDeJogo)
        {
        case JOGO:
            ModoJogo(&jogo, jogosSalvos);
            break;
        case TELAINICIAL:
            ModoTelaInicial(&jogo);
            break;
        case MENUINICIAL:
            ModoMenuInicial(&jogo);
            break;
        case NOVOJOGO:
            ModoSelecionaJogo(&jogo, jogo.modoDeJogo, jogosSalvos);
            break;
        case CARREGAR:
            ModoSelecionaJogo(&jogo, jogo.modoDeJogo, jogosSalvos);
            break;
        case SELECIONANOME:
            ModoSelecionaNome(&jogo);
        case GAMEOVER:
            ModoGameOver(&jogo, ranking);
            break;
        case TELAENTRENIVEIS:
            ModoEntreNiveis(&jogo, jogosSalvos);
            break;
        case RANKING:
            ModoRanking(&jogo, ranking);
            break;
        default:
            break;
        }
    }



    CloseWindow(); // Fecha a janela
    return 0;
}
