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

    sprintf(conteudoVidas, "%d", player.vidas);
    sprintf(conteudoNivel, "%d", 0);
    sprintf(conteudoScore, "%d", 0);

    DrawRectangle(0, 0, LARGURA, ALTURABARRASTATUS, DARKGRAY);

    DrawText(vidas, 10, 10, 40, WHITE);
    DrawText(conteudoVidas, 150, 10, 40, WHITE);
    DrawText(nivel, 200, 10, 40, WHITE);
    DrawText(conteudoNivel, 320, 10, 40, WHITE);
    DrawText(score, 370, 10, 40, WHITE);
    DrawText(conteudoScore, 520, 10, 40, WHITE);






}
