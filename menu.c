#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "jogador.h"
#include "monstros.h"
#include "variaveis_globais.h"
#include "ataque_dano.h"
#include "menu.h"

//Desenha barra superior de acordo com os valores
void DesenhaBarraStatus(struct Player player) {

    char vidas[TAMANHOTEXTO] = {"Vidas: "};
    char conteudoVidas[TAMANHOTEXTO] = {'\0'};
    char nivel[TAMANHOTEXTO] = {"Nivel: "};
    char conteudoNivel[TAMANHOTEXTO] = {'\0'};
    char score[TAMANHOTEXTO] = {"Score: "};
    char conteudoScore[TAMANHOTEXTO] = {'\0'};
    char municao[TAMANHOTEXTO] = {"Municao: "};
    char conteudoMunicao[TAMANHOTEXTO] = {'\0'};

    sprintf(conteudoVidas, "%d", player.vidas);
    sprintf(conteudoNivel, "%d", 0);
    sprintf(conteudoScore, "%d", player.score);
    sprintf(conteudoMunicao, "%d", player.municao);


    DrawRectangle(0, 0, LARGURA, ALTURABARRASTATUS, DARKGRAY);

    DrawText(vidas, 10, 10, 40, WHITE);
    DrawText(conteudoVidas, 150, 10, 40, WHITE);
    DrawText(municao, 200, 10, 40, WHITE);
    DrawText(conteudoMunicao, 390, 10, 40, WHITE);
    DrawText(nivel, 700, 10, 40, WHITE);
    DrawText(conteudoNivel, 820, 10, 40, WHITE);
    DrawText(score, 900, 10, 40, WHITE);
    DrawText(conteudoScore, 1050, 10, 40, WHITE);
}

void DesenhaFimDoNivel() {

    char texto[TAMANHOTEXTO] = {"FIM DO NIVEL"};


    DrawText(texto, 300, 600, 100, BLACK);
}


void DesenhaGameOver() {

    char texto[TAMANHOTEXTO] = {"GAME OVER"};

    DrawText(texto, 300, 600, 100, RED);
}

