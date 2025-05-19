#include "raylib.h"
#include <string.h>
#include <stdlib.h>

#define LARGURA 1200
#define ALTURA 800
#define CELULAMATRIZ 50
#define MAXMONSTROS 20

struct Player
{
    int posX, posY, tamanhoPersonagem;;
    int velocidadeMovimento;
};

struct Monsters
{
    int posX[MAXMONSTROS], posY[MAXMONSTROS];
};

//Funcao que recebe como parametro a matriz mapa e define a posicao inicial (x,y) do jogador conforme o mapa
void PosicionaJogadorInicialmente (char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], int *posX, int *posY)
{

    char *p;

    for(p = &mapa[0][0]; p <= &mapa[(ALTURA/CELULAMATRIZ) - 1][(LARGURA/CELULAMATRIZ) - 1]; p++)
    {
        if (*p == 'J')
        {
            *posX = ((p - &mapa[0][0]) % (LARGURA/CELULAMATRIZ))*CELULAMATRIZ;
            *posY = ((p - &mapa[0][0]) / (LARGURA/CELULAMATRIZ))*CELULAMATRIZ;
        }
    }

}

//Lê o mapa e guarda as posições dos montros nas variáveis posX e posY da estrutura Monsters
void CriaMonstros(char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], int posX[], int posY[]) {
    int i, j, iMonstro = 0;
    for(i=0;i<MAXMONSTROS;i++) {
        posX[i] = -1;
        posY[i] = -1;
    }
    for(i=0;i<ALTURA/CELULAMATRIZ;i++) {
        for(j=0;j<LARGURA/CELULAMATRIZ;j++) {
            if(mapa[i][j] == 'M') {
                posX[iMonstro] = j*CELULAMATRIZ;
                posY[iMonstro] = i*CELULAMATRIZ;
                iMonstro++;
            }
        }
    }
}

//Funcao que dada uma matriz mapa, desenha os obstaculos marcados como P
void DesenhaMapa (char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ])
{
    char *p;
    int posX, posY;

    for(p = &mapa[0][0]; p <= &mapa[(ALTURA/CELULAMATRIZ) - 1][(LARGURA/CELULAMATRIZ) - 1]; p++)
    {
        if (*p == 'P')
        {
            posX = ((p - &mapa[0][0]) % (LARGURA/CELULAMATRIZ))*CELULAMATRIZ;
            posY = ((p - &mapa[0][0]) / (LARGURA/CELULAMATRIZ))*CELULAMATRIZ;
            DrawRectangle(posX, posY, CELULAMATRIZ, CELULAMATRIZ, BLUE);
        }
    }

}

//Funcao que desenha o jogador
void DesenhaJogador (struct Player player) {
    DrawRectangle(player.posX, player.posY, player.tamanhoPersonagem, player.tamanhoPersonagem, LIME);
}

//Funcao que desenha os monstros
void DesenhaMonstros(struct Monsters monstros) {
    int i;
    for(i=0;i<MAXMONSTROS;i++)
        if(monstros.posX[i] != -1, monstros.posY[i] != -1)
            DrawRectangle(monstros.posX[i], monstros.posY[i], CELULAMATRIZ, CELULAMATRIZ, RED);
}

//Funcao que recebe uma direcao (U, D, L, R), uma matriz mapa e movimento o jogador, com restricao de movimento a obstaculos
void MovimentaJogador (char direcao, struct Player player, char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], int *posX, int *posY)
{

    switch (direcao)
    {
    case 'U':
        if (player.posY > 0 &&
                (mapa[(player.posY - 1)/CELULAMATRIZ][(player.posX + player.tamanhoPersonagem - 1)/CELULAMATRIZ] != 'P' &&
                 mapa[(player.posY - 1)/CELULAMATRIZ][player.posX/CELULAMATRIZ] != 'P'))
        {
            *posY -= player.velocidadeMovimento;
        }

        break;
    case 'D':
        if (player.posY < ALTURA - player.tamanhoPersonagem &&
                (mapa[(player.posY + player.tamanhoPersonagem + 1)/CELULAMATRIZ][player.posX/CELULAMATRIZ] != 'P' &&
                 mapa[(player.posY + player.tamanhoPersonagem + 1)/CELULAMATRIZ][(player.posX + player.tamanhoPersonagem - 1)/CELULAMATRIZ] != 'P')
           )
        {
            *posY += player.velocidadeMovimento;
        }

        break;
    case 'L':
        if (player.posX > 0 &&
                (mapa[player.posY/CELULAMATRIZ][(player.posX - 1)/CELULAMATRIZ] != 'P' &&
                 mapa[(player.posY + player.tamanhoPersonagem - 1)/CELULAMATRIZ][(player.posX - 1)/CELULAMATRIZ] != 'P')
           )
        {
            *posX -= player.velocidadeMovimento;
        }

        break;
    case 'R':
        if (player.posX < LARGURA - player.tamanhoPersonagem &&
                (mapa[player.posY/CELULAMATRIZ][(player.posX + player.tamanhoPersonagem + 1)/CELULAMATRIZ] != 'P' &&
                 mapa[(player.posY + player.tamanhoPersonagem - 1)/CELULAMATRIZ][(player.posX + player.tamanhoPersonagem + 1)/CELULAMATRIZ] != 'P')
           )
        {
            *posX += player.velocidadeMovimento;
        }

        break;
    default:
        break;
    }

}

//Função que detecta se duas teclas estão sendo pressionadas ao mesmo tempo, e, se sim, normaliza o vetor da velocidade
void NormalizaVelocidade(int *vel) {
    if(IsKeyDown(KEY_W) && IsKeyDown(KEY_A))
        *vel = 2;
    else if(IsKeyDown(KEY_W) && IsKeyDown(KEY_D))
        *vel = 2;
    else if(IsKeyDown(KEY_S) && IsKeyDown(KEY_A))
        *vel = 2;
    else if(IsKeyDown(KEY_S) && IsKeyDown(KEY_D))
        *vel = 2;
    else
        *vel = 5;
}

int main()
{
    //Criar o player e a lista de monstros:
    struct Player player;
    struct Monsters monstros;

    //Cria a matriz contendo as posicoes iniciais do jogo, com P = parede, J = jogador
    char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ] =
    {
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'M', '-', '-', '-', '-'},
        {'-', '-', '-', '-', 'M', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'J', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'P', 'P', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'P', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', 'P', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', 'P', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', 'P', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'M', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    };

    //define tamanho e velocidade do jogador
    player.tamanhoPersonagem = CELULAMATRIZ;
    player.velocidadeMovimento = 5;

    //Varre o mapa fornecido e posiciona o jogador inicialmente
    PosicionaJogadorInicialmente(mapa, &player.posX, &player.posY);

    //Setar posições iniciais dos monstros
    CriaMonstros(mapa,monstros.posX,monstros.posY);

    InitWindow(LARGURA, ALTURA, "Zinf"); //Inicializa janela, com certo tamanho e titulo
    SetTargetFPS(60);// Ajusta a janela para 60 frames por segundo

    //Este laco repete enquanto a janela nao for fechada
    //Utilizamos ele para atualizar o estado do programa / jogo
    while (!WindowShouldClose())
    {
        //Movimento do jogador
        if(IsKeyDown(KEY_W))
            MovimentaJogador('U', player, mapa, &player.posX, &player.posY);
        if(IsKeyDown(KEY_S))
            MovimentaJogador('D', player, mapa, &player.posX, &player.posY);
        if(IsKeyDown(KEY_A))
            MovimentaJogador('L', player, mapa, &player.posX, &player.posY);
        if(IsKeyDown(KEY_D))
            MovimentaJogador('R', player, mapa, &player.posX, &player.posY);



        // Atualiza o que eh mostrado na tela a partir do estado do jogo
        BeginDrawing(); //Inicia o ambiente de desenho na tela
        ClearBackground(RAYWHITE); //Limpa a tela e define cor de fundo
        DesenhaJogador(player);
        DesenhaMonstros(monstros);
        DesenhaMapa(mapa);

        EndDrawing(); //Finaliza o ambiente de desenho na tela
    }

    CloseWindow(); // Fecha a janela
    return 0;
}
