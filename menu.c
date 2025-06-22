#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "raylib.h"
#include "jogador.h"
#include "monstros.h"
#include "variaveis_globais.h"
#include "ataque_dano.h"
#include "menu.h"

void IniciaJogo(struct Jogo *jogo)
{
    jogo->modoDeJogo = TELAINICIAL;
    jogo->nivel = 1;
    jogo->score = 0;
    jogo->vidasDoPlayer = 3;
    jogo->municao = 5;
    jogo->armaAtual = 'C';
}

void CarregaJogo(struct Jogo *jogo, struct Jogo jogoSalvo)
{
    jogo->nivel = jogoSalvo.nivel;
    jogo->score = jogoSalvo.score;
    jogo->vidasDoPlayer = jogoSalvo.vidasDoPlayer;
    jogo->municao = jogoSalvo.municao;
    jogo->armaAtual = jogoSalvo.armaAtual;
}

void CarregaArquivoSave(struct Jogo jogosSalvos[])
{
    int i;

    struct Jogo jogosSalvosTemp[5];

    FILE *arquivoSaveLeitura = fopen("save.bin", "rb");

    if (arquivoSaveLeitura == NULL)
    {
        for (i = 0; i <5; i++)
        {
            jogosSalvos[i].ocupado = false;
        }


        FILE *arquivoSaveEscrita = fopen("save.bin", "wb");

        fwrite(jogosSalvos, sizeof(struct Jogo), 5, arquivoSaveEscrita);

        fclose(arquivoSaveEscrita);

    }
    else
    {

        fread(jogosSalvosTemp, sizeof(struct Jogo), 5, arquivoSaveLeitura);

        for(i = 0; i < 5; i++)
        {
            if (jogosSalvosTemp[i].ocupado)
            {
                jogosSalvos[i] = jogosSalvosTemp[i];
            }
            else
            {
                jogosSalvos[i].ocupado = false;
            }

        }

    }

    fclose(arquivoSaveLeitura);
}

void SalvaJogo(struct Jogo jogosSalvos[], struct Jogo jogo)
{
    FILE *arquivoSave = fopen("save.bin", "wb");

    jogosSalvos[jogo.saveSlot] = jogo;

    fwrite(jogosSalvos, sizeof(struct Jogo), 5, arquivoSave);

    fclose(arquivoSave);
}




void DesenhaSaveSlot(struct Jogo jogo, int posicaoY)
{

    char saveNome[TAMANHOTEXTO] = {'\0'};
    strcpy(saveNome, jogo.nome);
    char saveNivel[TAMANHOTEXTO];
    sprintf(saveNivel, "%d", jogo.nivel);
    char saveVidas[TAMANHOTEXTO];
    sprintf(saveVidas, "%d", jogo.vidasDoPlayer);
    char saveScore[TAMANHOTEXTO];
    sprintf(saveScore, "%d", jogo.score);


    DrawText(saveNome, 300, posicaoY, 50, BLACK);
    DrawText(saveNivel, 300, posicaoY + 55, 40, BLACK);
    DrawText(saveVidas, 400, posicaoY + 55, 40, BLACK);
    DrawText(saveScore, 600, posicaoY + 55, 40, BLACK);


}

void DesenhaNome(struct Jogo jogo)
{
    char saveNome[25] = {'\0'};
    strncpy(saveNome, jogo.nome, 25);
    char texto[TAMANHOTEXTO] = {"Digite seu nome"};


    DrawText(texto, 350, 200, 50, BLACK);
    DrawText(saveNome, 300, 450, 50, BLACK);

}



void DesenhaSaves(struct Jogo jogosSalvos[])
{

    int i;
    int posicaoY = 150;
    char texto[TAMANHOTEXTO] = {"Selecione o jogo"};
    char sair[TAMANHOTEXTO] = {"Retornar ao menu"};



    for (i = 0; i < 5; i++)
    {
        if (jogosSalvos[i].ocupado)
        {
            DesenhaSaveSlot(jogosSalvos[i], posicaoY);
        }
        else
        {
            char saveNome[TAMANHOTEXTO] = {"Novo Jogo"};
            DrawText(saveNome, 300, posicaoY, 50, BLACK);
        }
        posicaoY += 100;
    }


    DrawText(texto, 300, 50, 50, BLACK);
    DrawText(sair, 300, 720, 50, BLACK);


}







void CriaSeta(struct Seta *seta, int modo)
{

    switch(modo)
    {
    case MENUINICIAL:
        seta->posicao.x = 250;
        seta->posicao.y = 160;
        seta->posicao.width = 30;
        seta->posicao.height = 30;
        seta->opcao = MENUINICIAL_NOVOJOGO;
        break;
    case PAUSE:
        seta->posicao.x = 250;
        seta->posicao.y = 275;
        seta->posicao.width = 30;
        seta->posicao.height = 30;
        seta->opcaoPause = MENUPAUSE_VOLTAR;
        break;
    case NOVOJOGO:
    case CARREGAR:
    case SALVAR:
        seta->posicao.x = 250;
        seta->posicao.y = 160;
        seta->posicao.width = 30;
        seta->posicao.height = 30;
        seta->save = SAVE1;
        break;
    default:
        break;
    }

}

void DesenhaSeta(struct Seta seta)
{
    DrawRectangleRec(seta.posicao, BLACK);
}

void MovimentaSeta(struct Seta *seta, int modo)
{

    switch(modo)
    {
    case MENUINICIAL:
        if (IsKeyPressed(KEY_W) && seta->opcao != MENUINICIAL_NOVOJOGO)
        {
            seta->opcao = seta->opcao - 1;
            seta->posicao.y = seta->posicao.y - 150;
        }
        if (IsKeyPressed(KEY_S) && seta->opcao != MENUINICIAL_SAIR)
        {
            seta->opcao = seta->opcao + 1;
            seta->posicao.y = seta->posicao.y + 150;
        }
        break;
    case PAUSE:
        if (IsKeyPressed(KEY_W) && seta->opcaoPause != MENUPAUSE_VOLTAR)
        {
            seta->opcaoPause = seta->opcaoPause - 1;
            seta->posicao.y = seta->posicao.y - 70;
        }
        if (IsKeyPressed(KEY_S) && seta->opcaoPause != MENUPAUSE_SAIR)
        {
            seta->opcaoPause = seta->opcaoPause + 1;
            seta->posicao.y = seta->posicao.y + 70;
        }
        break;
    case NOVOJOGO:
    case CARREGAR:
    case SALVAR:
        if (IsKeyPressed(KEY_W) && seta->save != SAVE1 && seta->save != SAIR)
        {
            seta->save = seta->save - 1;
            seta->posicao.y = seta->posicao.y - 100;
        } else if (IsKeyPressed(KEY_W) && seta->save == SAIR)
        {
            seta->save = SAVE5;
            seta->posicao.y = seta->posicao.y - 170;
        }
        if (IsKeyPressed(KEY_S) && seta->save != SAVE5 && seta->save != SAIR)
        {
            seta->save = seta->save + 1;
            seta->posicao.y = seta->posicao.y + 100;
        } else if (IsKeyPressed(KEY_S) && seta->save == SAVE5)
        {
            seta->save = SAIR;
            seta->posicao.y = seta->posicao.y + 170;
        }


        break;
    }
}

void DesenhaOpcoesMenuInicial()
{
    char novoJogo[TAMANHOTEXTO] = {"Novo jogo"};
    char carregarJogo[TAMANHOTEXTO] = {"Carregar jogo"};
    char ranking[TAMANHOTEXTO] = {"Ranking"};
    char sair[TAMANHOTEXTO] = {"Sair"};


    DrawText(novoJogo, 300, 150, 50, BLACK);
    DrawText(carregarJogo, 300, 300, 50, BLACK);
    DrawText(ranking, 300, 450, 50, BLACK);
    DrawText(sair, 300, 600, 50, BLACK);


}


void DesenhaTitulo()
{

    char texto[TAMANHOTEXTO] = {"ZINF"};
    char aperteEnter[TAMANHOTEXTO] = {"Pressione Enter para iniciar"};

    DrawText(texto, 450, 300, 100, BLACK);
    DrawText(aperteEnter, 210, 500, 50, BLACK);

}


//Desenha barra superior de acordo com os valores
void DesenhaBarraStatus(struct Player player)
{

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

void DesenhaMenuPause(struct Jogo *jogo, struct Player player, struct Seta *seta)
{
    DrawRectangle(190, 220, 820, 360, BLACK);
    DrawRectangle(200, 230, 800, 340, BEIGE);
    DesenhaSeta(*seta);
    DesenhaOpcoesMenuPause();
}

void DesenhaOpcoesMenuPause()
{
    char voltar[TAMANHOTEXTO] = {"Voltar"};
    char salvar[TAMANHOTEXTO] = {"Salvar jogo"};
    char menuInicial[TAMANHOTEXTO] = {"Voltar ao menu inicial"};
    char sair[TAMANHOTEXTO] = {"Sair"};


    DrawText(voltar, 300, 270, 50, BLACK);
    DrawText(salvar, 300, 340, 50, BLACK);
    DrawText(menuInicial, 300, 410, 50, BLACK);
    DrawText(sair, 300, 480, 50, BLACK);


}


void DesenhaFimDoNivel()
{

    char texto[TAMANHOTEXTO] = {"FIM DO NIVEL"};


    DrawText(texto, 250, 400, 100, BLACK);
}


void DesenhaGameOver()
{

    char texto[TAMANHOTEXTO] = {"GAME OVER"};
    char voltar[TAMANHOTEXTO] = {"Pressione Enter para voltar ao inicio"};

    DrawText(texto, 280, 300, 100, RED);
    DrawText(voltar, 130, 600, 50, BLACK);


}

void DesenhaTelaEntreNiveis(struct Jogo jogo)
{

    char texto[TAMANHOTEXTO] = {"NIVEL "};
    if (jogo.nivel < 10)
    {
        texto[6] = jogo.nivel + '0';
    }
    else
    {
        texto[6] = jogo.nivel / 10 + '0';
        texto[7] = jogo.nivel % 10 + '0';
    }

    char proximo[TAMANHOTEXTO] = {"Pressione Enter para continuar"};

    DrawText(texto, 280, 300, 100, BLACK);
    DrawText(proximo, 130, 600, 50, BLACK);


}

void SalvaRanking(struct Jogo jogo)
{
    struct Score highscores[MAXIMODESCORES];
    struct Score novaScore;

    novaScore.score = jogo.score;

    FILE *arquivoRankingEntrada = fopen("Highscores.bin","rb");

    if (arquivoRankingEntrada != NULL)
    {
        fread(highscores, sizeof(struct Score), MAXIMODESCORES, arquivoRankingEntrada);
    }

    fclose(arquivoRankingEntrada);

    AtualizaRanking(highscores, novaScore);


    FILE *arquivoRankingSaida = fopen("Highscores.bin","wb");

    if (arquivoRankingSaida != NULL)
    {
        fwrite(highscores, sizeof(struct Score), MAXIMODESCORES, arquivoRankingSaida);
    }

    fclose(arquivoRankingSaida);


}

void AtualizaRanking (struct Score highscores[MAXIMODESCORES], struct Score novaScore)
{
    int i;

    int posicao = MAXIMODESCORES;

    for (i = 9; i >= 0; i--)
    {
        if (novaScore.score >= highscores[i].score)
        {
            posicao = i;
        }
    }

#ifdef DEBUG
    printf("posicao: %d\n", posicao);
#endif // DEBUG

    for (i = 9; i > posicao; i--)
    {
        highscores[i] = highscores[i - 1];
    }
    if (posicao < 9)
    {
        highscores[posicao] = novaScore;
    }
}

