#include "raylib.h"
#include <string.h>
#include <stdlib.h>

#define LARGURA 800
#define ALTURA 450

int main(){
    char texto[50] = "Pressione uma seta"; //Texto inicial

    InitWindow(LARGURA, ALTURA, "Teclas"); //Inicializa janela, com certo tamanho e titulo
    SetTargetFPS(60);// Ajusta a janela para 60 frames por segundo

    //Este laco repete enquanto a janela nao for fechada
    //Utilizamos ele para atualizar o estado do programa / jogo
    while (!WindowShouldClose())
    {
	// Trata entrada do usuario e atualiza estado do jogo
	if (IsKeyPressed(KEY_RIGHT)) {
	    strcpy(texto,"Direita");
	}
	if (IsKeyPressed(KEY_LEFT)) {
	    strcpy(texto,"Esquerda");
	}
	if (IsKeyPressed(KEY_UP)) {
	    strcpy(texto,"Cima");
	}
	if (IsKeyPressed(KEY_DOWN)) {
	    strcpy(texto,"Baixo");
	}

	// Atualiza o que eh mostrado na tela a partir do estado do jogo
	BeginDrawing(); //Inicia o ambiente de desenho na tela
	ClearBackground(RAYWHITE); //Limpa a tela e define cor de fundo
	DrawText(texto, 300, 200, 40, RED); //Desenha um texto, com posicao, tamanho e cor
	EndDrawing(); //Finaliza o ambiente de desenho na tela
    }

    CloseWindow(); // Fecha a janela
    return 0;
}
