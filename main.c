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

int main()
{
    //Inicia o jogo
    struct Jogo jogo;
    IniciaJogo(&jogo);

    InitWindow(LARGURA, ALTURA + ALTURABARRASTATUS, "Zinf"); //Inicializa janela, com certo tamanho e titulo
    SetTargetFPS(FPS);// Ajusta a janela para 60 frames por segundo

    while(jogo.modoDeJogo != FIM && !WindowShouldClose()){
        switch(jogo.modoDeJogo)
        {
        case JOGO:
            ModoJogo(&jogo);
            break;
        case TELAINICIAL:
            ModoTelaInicial(&jogo);
            break;
        case MENUINICIAL:
            ModoMenuInicial(&jogo);
            break;
        default:
            break;
        }
    }



    CloseWindow(); // Fecha a janela
    return 0;
}
