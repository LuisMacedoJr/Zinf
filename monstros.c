#include <stdio.h>
#include <math.h>

#include "raylib.h"
#include "jogador.h"
#include "monstros.h"
#include "variaveis_globais.h"



//Lê o mapa e guarda as posições dos montros nas variáveis posX e posY da estrutura Monstros, além da quantidade de monstros no mapa inteiro
void CriaMonstros(char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], int posX[], int posY[], int enterrado[], int timerMovimento[], int pontoX[], int pontoY[], int ataqueStun[], int *quantidadeMonstros) {
    int i, j, iMonstro = 0;
    for(i=0;i<MAXMONSTROS;i++) {
        posX[i] = -1;
        posY[i] = -1;
        enterrado[i] = 0;
        timerMovimento[i] = 300;
        pontoX[i] = -1;
        pontoY[i] = -1;
        ataqueStun[i] = 0;
    }
    for(i=0;i<ALTURA/CELULAMATRIZ;i++) {
        for(j=0;j<LARGURA/CELULAMATRIZ;j++) {
            if(mapa[i][j] == 'M') {
                posX[iMonstro] = j*CELULAMATRIZ;
                posY[iMonstro] = i*CELULAMATRIZ;
                pontoX[iMonstro] = posX[iMonstro];
                pontoY[iMonstro] = posY[iMonstro];
                iMonstro++;
            }
        }
    }
    *quantidadeMonstros = iMonstro;
}

//Função que calcula distância entre dois pontos
float CalculaDist(int x1, int y1, int x2, int y2) {
    return(sqrt(pow((x1-x2),2)+pow((y1-y2),2)));
}

//Calcula a distância entre cada monstro e o player
void DistMonstroPlayer(int posX[], int posY[], float distPlayer[], struct Player player, struct Monstros monstros) {
    int i;
    for(i=0;i<monstros.quantidadeMonstros;i++) {
        distPlayer[i] = CalculaDist(posX[i],posY[i],player.posX,player.posY);
    }
}

//Determina se o monstro deveria se mexer ou não baseado em sua distância até o player
int MonstroDeveMover(struct Monstros monstros, struct Player player, int i) {
    if(abs(monstros.posX[i] - player.posX) <= monstros.raioVisao && abs(monstros.posY[i] - player.posY) <= monstros.raioVisao) {
        return 1;
    } else {
        return 0;
    }
}


//Funcao que desenha os monstros
void DesenhaMonstros(struct Monstros monstros, struct Player player) {
    int i;
    for(i=0;i<MAXMONSTROS;i++) {
        if(monstros.posX[i] != -1 && monstros.posY[i] != -1 && MonstroDeveMover(monstros, player, i) == 0)
            DrawRectangle(monstros.posX[i], monstros.posY[i], CELULAMATRIZ, CELULAMATRIZ, RED);
        if(monstros.posX[i] != -1 && monstros.posY[i] != -1 && MonstroDeveMover(monstros, player, i) == 1)
            DrawRectangle(monstros.posX[i], monstros.posY[i], CELULAMATRIZ, CELULAMATRIZ, ORANGE);
    }
}
