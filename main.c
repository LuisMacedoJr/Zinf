#include "raylib.h"
#include <string.h>
#include <stdlib.h>

#define LARGURA 500
#define ALTURA 300

struct Player {
    int posX, posY;
};

struct Monster {
    int posX, posY;
};

int main(){
    //Criar o player:
    struct Player player;
    struct Monster monsters[] = {{8,1},{1,3},{8,5}};

    //Declaração de variáveis:
    char mapa[ALTURA/50][LARGURA/50] = {{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
                                        {'-', '-', '-', '-', '-', '-', '-', '-', 'M', '-'},
                                        {'-', '-', '-', '-', '-', 'J', '-', '-', '-', '-'},
                                        {'-', 'M', '-', '-', '-', '-', '-', '-', '-', '-'},
                                        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
                                        {'-', '-', '-', '-', '-', '-', '-', '-', 'M', '-'}};
    int i, j, posPlayerX, posPlayerY;
    int numMonsters = sizeof(monsters) / sizeof(monsters[0]);

    InitWindow(LARGURA, ALTURA, "Teclas"); //Inicializa janela, com certo tamanho e titulo
    SetTargetFPS(60);// Ajusta a janela para 60 frames por segundo

    //Este laco repete enquanto a janela nao for fechada
    //Utilizamos ele para atualizar o estado do programa / jogo
    while (!WindowShouldClose())
    {

    //Interpretação do mapa
    for(i=0;i<ALTURA/50;i++) {
        for(j=0;j<LARGURA/50;j++) {
            if(mapa[i][j] == 'J') {
                player.posX = j;
                player.posY = i;
            }
        }
    }

    //Movimento do jogador:
    if(IsKeyDown(KEY_UP)) {
        mapa[player.posY][player.posX] = '-';
        mapa[player.posY-1][player.posX] = 'J';
    }
    if(IsKeyDown(KEY_DOWN) && player.posY < ALTURA/50) {
        mapa[player.posY][player.posX] = '-';
        mapa[player.posY+1][player.posX] = 'J';
    }
    if(IsKeyDown(KEY_LEFT) && player.posX > 0) {
        mapa[player.posY][player.posX] = '-';
        mapa[player.posY][player.posX-1] = 'J';
    }
    if(IsKeyDown(KEY_RIGHT) && player.posX < LARGURA/50) {
        mapa[player.posY][player.posX] = '-';
        mapa[player.posY][player.posX+1] = 'J';
    }

// Atualiza o que eh mostrado na tela a partir do estado do jogo
BeginDrawing(); //Inicia o ambiente de desenho na tela
ClearBackground(RAYWHITE); //Limpa a tela e define cor de fundo
DrawRectangle(player.posX*50,player.posY*50,50,50,LIME);
for(i=0;i<numMonsters;i++) {
        DrawRectangle(monsters[i].posX*50,monsters[i].posY*50,50,50,RED);
}
EndDrawing(); //Finaliza o ambiente de desenho na tela
    }

    CloseWindow(); // Fecha a janela
    return 0;
}
