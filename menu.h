#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdbool.h>
#include "variaveis_globais.h"
#include "jogador.h"
#include "estruturas.h"

void IniciaJogo(struct Jogo *jogo);
void CarregaArquivoSave(struct Jogo jogosSalvos[5]);
void DesenhaSaveSlot(struct Jogo jogo, int posicaoY);
void DesenhaSaves(struct Jogo jogosSalvos[]);
void CarregaJogo(struct Jogo *jogo, struct Jogo jogoSalvo);
void SalvaJogo(struct Jogo jogosSalvos[], struct Jogo jogo);
void CriaSeta(struct Seta *seta, int modo);
void DesenhaNome(struct Jogo jogo);
void DesenhaTitulo();
void DesenhaSeta(struct Seta seta);
void MovimentaSeta(struct Seta *seta, int modo);
void DesenhaOpcoesMenuInicial();
void DesenhaBarraStatus(struct Player player);
void DesenhaMenuPause(struct Jogo *jogo, struct Player player, struct Seta *seta);
void DesenhaOpcoesMenuPause();
void DesenhaFimDoNivel();
void DesenhaTelaEntreNiveis(struct Jogo jogo);
void DesenhaGameOver();
void SalvaRanking(struct Jogo jogo);
void AtualizaRanking (struct Score highscores[MAXIMODESCORES], struct Score novaScore);


#endif // MENU_H_INCLUDED
