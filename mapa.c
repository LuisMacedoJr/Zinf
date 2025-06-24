#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "raylib.h"
#include "variaveis_globais.h"
#include "mapa.h"

//Le um arquivo mapaxx.txt, preenchendo uma matriz de caracteres e atualizando o nivel
void LeMapa(struct Jogo jogo, char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ])
{
    char nomeDoArquivo[20] = {"mapas/mapa00.txt"};
    char caractereAtual;
    int i, j;
    FILE *arquivoMapa;


    if (jogo.nivel < 10)
    {
        nomeDoArquivo[10] = '0';
        nomeDoArquivo[11] = jogo.nivel + '0';
    }
    else
    {
        nomeDoArquivo[10] = jogo.nivel / 10 + '0';
        nomeDoArquivo[11] = jogo.nivel % 10 + '0';
    }

    arquivoMapa = fopen(nomeDoArquivo, "r");


    for (i = 0; i < ALTURA/CELULAMATRIZ; i++)
    {
        for(j = 0; j < LARGURA/CELULAMATRIZ; j++)
        {
            do
            {
                caractereAtual = fgetc(arquivoMapa);
            }
            while (caractereAtual == '\r' || caractereAtual == '\n');
            mapa[i][j] = caractereAtual;
        }
    }

}


//Funcao que dada uma matriz mapa, preenche um array de obstaculos. P para parede, V para vida, E para chicote e B para municao
void CriaObstaculos (char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ], struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int *numeroDeObstaculos)
{
    char *p;
    int posX, posY;
    *numeroDeObstaculos = 0;

    for(p = &mapa[0][0]; p <= &mapa[(ALTURA/CELULAMATRIZ) - 1][(LARGURA/CELULAMATRIZ) - 1]; p++)
    {
        if (*p == 'P')
        {
            posX = ((p - &mapa[0][0]) % (LARGURA/CELULAMATRIZ))*CELULAMATRIZ;
            posY = ((p - &mapa[0][0]) / (LARGURA/CELULAMATRIZ))*CELULAMATRIZ + ALTURABARRASTATUS;

            obstaculos[*numeroDeObstaculos].hitbox.x = posX;
            obstaculos[*numeroDeObstaculos].hitbox.y = posY;
            obstaculos[*numeroDeObstaculos].hitbox.width = CELULAMATRIZ;
            obstaculos[*numeroDeObstaculos].hitbox.height = CELULAMATRIZ;
            obstaculos[*numeroDeObstaculos].tipo = 'P';

            *numeroDeObstaculos += 1;

        }
        if (*p == 'V')
        {
            posX = ((p - &mapa[0][0]) % (LARGURA/CELULAMATRIZ))*CELULAMATRIZ;
            posY = ((p - &mapa[0][0]) / (LARGURA/CELULAMATRIZ))*CELULAMATRIZ + ALTURABARRASTATUS;

            obstaculos[*numeroDeObstaculos].hitbox.x = posX;
            obstaculos[*numeroDeObstaculos].hitbox.y = posY;
            obstaculos[*numeroDeObstaculos].hitbox.width = CELULAMATRIZ;
            obstaculos[*numeroDeObstaculos].hitbox.height = CELULAMATRIZ;
            obstaculos[*numeroDeObstaculos].tipo = 'V';
            obstaculos[*numeroDeObstaculos].vidaFPS = 15;
            obstaculos[*numeroDeObstaculos].vidaContadorFrame = 0;
            obstaculos[*numeroDeObstaculos].vidaTimerAnimacao = 1/obstaculos[*numeroDeObstaculos].vidaFPS;


            *numeroDeObstaculos += 1;

        }
        if (*p == 'E')
        {
            posX = ((p - &mapa[0][0]) % (LARGURA/CELULAMATRIZ))*CELULAMATRIZ;
            posY = ((p - &mapa[0][0]) / (LARGURA/CELULAMATRIZ))*CELULAMATRIZ + ALTURABARRASTATUS;

            obstaculos[*numeroDeObstaculos].hitbox.x = posX;
            obstaculos[*numeroDeObstaculos].hitbox.y = posY;
            obstaculos[*numeroDeObstaculos].hitbox.width = CELULAMATRIZ;
            obstaculos[*numeroDeObstaculos].hitbox.height = CELULAMATRIZ;
            obstaculos[*numeroDeObstaculos].tipo = 'E';


            *numeroDeObstaculos += 1;

        }
        if (*p == 'B')
        {
            posX = ((p - &mapa[0][0]) % (LARGURA/CELULAMATRIZ))*CELULAMATRIZ;
            posY = ((p - &mapa[0][0]) / (LARGURA/CELULAMATRIZ))*CELULAMATRIZ + ALTURABARRASTATUS;

            obstaculos[*numeroDeObstaculos].hitbox.x = posX;
            obstaculos[*numeroDeObstaculos].hitbox.y = posY;
            obstaculos[*numeroDeObstaculos].hitbox.width = CELULAMATRIZ;
            obstaculos[*numeroDeObstaculos].hitbox.height = CELULAMATRIZ;
            obstaculos[*numeroDeObstaculos].tipo = 'B';


            *numeroDeObstaculos += 1;

        }
    }

}

//Função que cria bolas de feno para serem usadas mais tarde
void CriaFeno(struct Feno fenos[]) {
    int i;
    for(i=0;i<MAXIMODEFENOS;i++) {
        fenos[i].hitbox.x = -999;
        fenos[i].hitbox.y = -999;
        fenos[i].hitbox.width = 50;
        fenos[i].hitbox.height = 50;
        fenos[i].angulo = 0;
        fenos[i].naTela = false;
        fenos[i].timer = rand()%1500;
    }
}

//Função que desenha os fenos
void DesenhaFeno(struct Feno feno[], Texture2D fenoTexture, int numeroDeFenos) {
    int i;
    for(i=0;i<numeroDeFenos;i++) {
        if(i%2 == 0)
            DrawTexturePro(fenoTexture, (Rectangle) {50*(i%2),0,50,50}, (Rectangle) {feno[i].hitbox.x,feno[i].hitbox.y,50,50}, (Vector2) {25,25}, feno[i].angulo, WHITE);
        if(i%2 == 1)
            DrawTexturePro(fenoTexture, (Rectangle) {50*(i%2),0,50,50}, (Rectangle) {feno[i].hitbox.x,feno[i].hitbox.y,50,50}, (Vector2) {25,25}, -feno[i].angulo, WHITE);
    }
}

//Função que atualiza diversas coisas em relação à struct feno, como sua posição, angulo, timer, etc.
void AtualizaFeno(struct Feno feno[], int numeroDeFenos) {
    int i;
    for(i=0;i<numeroDeFenos;i++) {
        //Checar se o timer está abaixo de 0 e se o feno está fora da tela
        if(feno[i].timer < 0 && !feno[i].naTela) {
            //Se sim, colocá-lo na tela e resetar o timer
            feno[i].naTela = true;
            feno[i].hitbox.x = i%2*LARGURA;
            feno[i].hitbox.y = rand()%(ALTURA-50) + 25;
            feno[i].timer = rand()%1500;
        } else {
            //Se não, diminuir o timer
            feno[i].timer--;
        }

        //Checar se o feno está fora da tela
        if(feno[i].hitbox.x > LARGURA+50 || feno[i].hitbox.x < -50)
            feno[i].naTela = false;

        //Mover o feno se ele estiver visível
        if(feno[i].naTela) {
            if(i%2 == 0) {
                feno[i].hitbox.x += 7;
                feno[i].hitbox.y += sin(feno[i].timer/3)*3;
            }
            if(i%2 == 1) {
                feno[i].hitbox.x -= 7;
                feno[i].hitbox.y -= sin(feno[i].timer/3)*3;
            }
        }

        //Rotacionar o feno se ele estiver visível
        if(feno[i].naTela) {
            if(feno[i].angulo > 360)
                feno[i].angulo = 0;
            feno[i].angulo += 15;
        }
    }
}

//Desenha o mapa de acordo com o array de obstaculos previamente preenchido, também chama a função AtualizaTimerAnimacaoVida
void DesenhaMapa(struct Obstaculo obstaculos[(ALTURA/CELULAMATRIZ)*(LARGURA/CELULAMATRIZ)], int numeroDeObstaculos, Texture2D paredeTexture, Texture2D vidaTexture, Texture2D chicoteTexture, Texture2D balasTexture)
{
    int i;

    for (i = 0; i < numeroDeObstaculos; i++)
    {
        switch (obstaculos[i].tipo)
        {
        case 'P':
            DrawTextureRec(paredeTexture, (Rectangle) {50*(i%2),0,50,50}, (Vector2) {obstaculos[i].hitbox.x,obstaculos[i].hitbox.y}, WHITE);
            break;
        case 'V':
            if(obstaculos[i].vidaContadorFrame > 16)
                obstaculos[i].vidaContadorFrame = 0;
            DrawTextureRec(vidaTexture, (Rectangle) {50*obstaculos[i].vidaContadorFrame,0,50,50}, (Vector2) {obstaculos[i].hitbox.x,obstaculos[i].hitbox.y}, WHITE);
            break;
        case 'E':
            DrawTextureRec(chicoteTexture, (Rectangle) {0,0,50,50}, (Vector2) {obstaculos[i].hitbox.x,obstaculos[i].hitbox.y}, WHITE);
            break;
        case 'B':
            DrawTextureRec(balasTexture, (Rectangle) {0,0,50,50}, (Vector2) {obstaculos[i].hitbox.x,obstaculos[i].hitbox.y}, WHITE);
            break;
        default:
            break;
        }
        AtualizaTimerAnimacaoVida(obstaculos,i);
    }
}

//Diminui o timer de animação da vida pelo tempo passado entre o ultimo frame e o atual. Se o valor ficar abaixo de 0, reseta para o inverso do fps e aumenta o contador de frames. Basicamente
//timer representa o tempo que deve passar entre cada frame da animação, por isso que quando o tempo passado for maior do que o timer, ele é resetado e aumenta o contador de frames.
void AtualizaTimerAnimacaoVida(struct Obstaculo obstaculos[], int id)
{
    obstaculos[id].vidaTimerAnimacao -= GetFrameTime();
    if(obstaculos[id].vidaTimerAnimacao < 0)
    {
        obstaculos[id].vidaContadorFrame++;
        obstaculos[id].vidaTimerAnimacao = 1/obstaculos[id].vidaFPS;
    }
}

//Desenha o chao a partir de uma textura
void DesenhaChao(char mapa[ALTURA/CELULAMATRIZ][LARGURA/CELULAMATRIZ],Texture2D textureChao)
{
    int i, j;
    for(i=0; i<ALTURA/CELULAMATRIZ; i++)
        for(j=0; j<LARGURA/CELULAMATRIZ; j++)
            DrawTextureV(textureChao,(Vector2)
        {
            j*CELULAMATRIZ,(i)*CELULAMATRIZ + ALTURABARRASTATUS
        },WHITE);

}

