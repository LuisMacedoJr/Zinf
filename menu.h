#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdbool.h>
#include "variaveis_globais.h"
#include "jogador.h"
#include "estruturas.h"

//Funcao de inicializacao do jogo

void IniciaJogo(struct Jogo *jogo);

//Funcoes relacionadas ao salvamento de jogo

void CarregaJogo(struct Jogo *jogo, struct Jogo jogoSalvo);

void SalvaJogo(struct Jogo jogosSalvos[], struct Jogo jogo);

void CarregaArquivoSave(struct Jogo jogosSalvos[5]);

void DesenhaSaveSlot(struct Jogo jogo, int posicaoY);

void DesenhaSaves(struct Jogo jogosSalvos[]);


//Funcoes relacionadas ao preenchimento e exibicao do ranking

void DesenhaScoreSlot(struct Score score, int posicaoY);

void DesenhaScores(struct Score ranking[]);

void CarregaArquivoRanking(struct Score ranking[]);

void SalvaRanking(struct Score ranking[], struct Jogo jogo);

void InsereScore(struct Score novaScore, struct Score ranking[]);

//Funcoes que trabalham com o ponteiro de selecao (seta)

void DesenhaSeta(struct Seta seta);

void MovimentaSeta(struct Seta *seta, int modo);

void CriaSeta(struct Seta *seta, int modo);

//Funcoes do modo tela inicial

void DesenhaTitulo();

//Funcoes do modo Menu Inicial

void DesenhaOpcoesMenuInicial();

//Funcoes do modo de selecao de nome

void DesenhaNome(struct Jogo jogo);

//Funcoes de menu do modo de jogo

void DesenhaBarraStatus(struct Player player, struct Jogo jogo);

void DesenhaMenuPause(struct Jogo *jogo, struct Player player, struct Seta *seta);

void DesenhaOpcoesMenuPause();

//Funcoes de fim de nivel

void DesenhaFimDoNivel();

void DesenhaTelaEntreNiveis(struct Jogo jogo);

void DesenhaGameOver();


#endif // MENU_H_INCLUDED
