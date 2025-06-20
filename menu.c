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

void IniciaJogo(struct Jogo *jogo){
    jogo->modoDeJogo = TELAINICIAL;
    jogo->nivel = 1;
    jogo->score = 0;
}

void CriaSeta(struct Seta *seta) {
    seta->posicao.x = 250;
    seta->posicao.y = 100;
    seta->posicao.width = 30;
    seta->posicao.height = 30;
    seta->opcao = NOVOJOGO;
}

void DesenhaSeta(struct Seta seta) {
    DrawRectangleRec(seta.posicao, BLACK);
}

void MovimentaSeta(struct Seta *seta) {
    if (IsKeyPressed(KEY_W) && seta->opcao >= NOVOJOGO) {
        seta->opcao = seta->opcao + 1;
        seta->posicao.y = seta->posicao.y - 200;
    }
    if (IsKeyPressed(KEY_S) && seta->opcao <= SAIR) {
        seta->opcao = seta->opcao - 1;
        seta->posicao.y = seta->posicao.y + 200;
    }
}

void DesenhaOpcoesMenuInicial() {
    char novoJogo[TAMANHOTEXTO] = {"Novo jogo"};
    char carregarJogo[TAMANHOTEXTO] = {"Carregar jogo"};
    char ranking[TAMANHOTEXTO] = {"Ranking"};
    char sair[TAMANHOTEXTO] = {"Sair"};


    DrawText(novoJogo, 300, 100, 50, BLACK);
    DrawText(carregarJogo, 300, 300, 50, BLACK);
    DrawText(ranking, 300, 500, 50, BLACK);
    DrawText(sair, 300, 700, 50, BLACK);


}


void DesenhaTitulo() {

    char texto[TAMANHOTEXTO] = {"ZINF"};
    char aperteEnter[TAMANHOTEXTO] = {"Pressione Enter para iniciar"};

    DrawText(texto, 300, 300, 100, BLACK);
    DrawText(aperteEnter, 300, 500, 50, BLACK);

}


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

