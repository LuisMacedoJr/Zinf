#include <stdio.h>
#include <math.h>

#include "raylib.h"
#include "variaveis_globais.h"
#include "ataque_dano.h"
#include "jogador.h"
#include "monstros.h"
#include "estruturas.h"

//void DesenhaBalas(struct Balas balas) {
//    int i;
//    for(i=0;i<MAXBALAS;i++)
//        if(balas.posX[i] != -1 && balas.posY[i] != -1)
//            DrawRectangle(balas.posX[i],balas.posY[i],CELULAMATRIZ,CELULAMATRIZ,YELLOW);
//}

//Aplica knockback ao levar dano. Recebe um int força e tolerancia, a qual indica a que distância do centro é preciso estar para levar knockback em duas direções (genérica)
//void Knockback(int *x1, int *y1, int x2, int y2, int forca, int tolerancia, char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ]) {
//    if(x2 - *x1 > tolerancia) {
//        Movimenta('L',mapa,x1,y1,forca);
//    }
//    if(x2 - *x1 < -tolerancia) {
//        Movimenta('R',mapa,x1,y1,forca);
//    }
//    if(y2 - *y1 > tolerancia) {
//        Movimenta('U',mapa,x1,y1,forca);
//    }
//    if(y2 - *y1 < -tolerancia) {
//        Movimenta('D',mapa,x1,y1,forca);
//    }
//}


//Função que atira a bala da pistola, onde o player está olhando.
//void Atirar(struct Player player, struct Balas balas, char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], int posX[], int posY[], char *dir) {
//    int i = 0;
//    if(player.dirMaisRecente == 'U' && mapa[(player.posY - 1)/CELULAMATRIZ][player.posX/CELULAMATRIZ] != 'P') {
//        while (i < 3) {
//            if(posX[i] == -1 || posY[i] == -1) {
//                posX[i] = player.posX;
//                posY[i] = player.posY - CELULAMATRIZ;
//                *dir = 'U';
//                break;
//            }
//            i++;
//        }
//    }
//    if(player.dirMaisRecente == 'D' && mapa[(player.posY + 1)/CELULAMATRIZ][player.posX/CELULAMATRIZ] != 'P') {
//        while (i < 3) {
//            if(posX[i] == -1 || posY[i] == -1) {
//                posX[i] = player.posX;
//                posY[i] = player.posY + CELULAMATRIZ;
//                *dir = 'D';
//                break;
//            }
//            i++;
//        }
//    }
//    if(player.dirMaisRecente == 'L' && mapa[player.posY/CELULAMATRIZ][(player.posX - 1)/CELULAMATRIZ] != 'P') {
//        while (i < 3) {
//            if(posX[i] == -1 || posY[i] == -1) {
//                posX[i] = player.posX - CELULAMATRIZ;
//                posY[i] = player.posY;
//                *dir = 'L';
//                break;
//            }
//            i++;
//        }
//    }
//    if(player.dirMaisRecente == 'R' && mapa[player.posY/CELULAMATRIZ][(player.posX + 1)/CELULAMATRIZ] != 'P') {
//        while (i < 3) {
//            if(posX[i] == -1 || posY[i] == -1) {
//                posX[i] = player.posX + CELULAMATRIZ;
//                posY[i] = player.posY;
//                *dir = 'R';
//                break;
//            }
//            i++;
//        }
//    }
//}

//Função que seta todas as posições de balas para 0, e a velocidade para 10
void InicializaBalas(int posX[], int posY[], int *vel) {
    int i;
    for(i=0;i<MAXBALAS;i++) {
        posX[i] = -1;
        posY[i] = -1;
    }
    *vel = 10;
}

//Função que atualiza a posição das balas dependendo na orientação delas, e checa colisão com monstros/paredes, destruindo a bala e matando os monstros.
//void AtualizaBalas(struct Balas balas, struct Monstros monstros, int posX[], int posY[], int monstrosPosX[], int monstrosPosY[], char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ]) {
//    int i, j;
//    for(i=0;i<MAXBALAS;i++) {
//        if(posX[i] != -1 && posY[i] != -1) {
//            Movimenta(balas.direcao, mapa, &posX[i], &posY[i], balas.balaVel);
//            if(Movimenta(balas.direcao, mapa, &posX[i], &posY[i], balas.balaVel)) {
//                posX[i] = -1;
//                posY[i] = -1;
//            }
//            for(j=0;j<MAXMONSTROS;j++) {
//                if(abs(monstrosPosX[j] - posX[i]) < 25 && abs(monstrosPosY[j] - posY[i]) < 25) {
//                    monstrosPosX[j] = -1;
//                    monstrosPosY[j] = -1;
//                    posX[i] = -1;
//                    posY[i] = -1;
//                }
//            }
//        }
//    }
//}
