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


//#define DEBUG
#define DEBUG2

int main()
{
    //Inicia o jogo
    struct Jogo jogo;
    IniciaJogo(&jogo);

    struct Jogo jogosSalvos[5];

    CarregaArquivoSave(jogosSalvos);

    InitWindow(LARGURA, ALTURA + ALTURABARRASTATUS, "Zinf"); //Inicializa janela, com certo tamanho e titulo
    SetTargetFPS(FPS);// Ajusta a janela para 60 frames por segundo

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
            ModoGameOver(&jogo);
            break;
        case TELAENTRENIVEIS:
            ModoEntreNiveis(&jogo);
            break;
        default:
            break;
        }
    }



    CloseWindow(); // Fecha a janela
    return 0;
}
