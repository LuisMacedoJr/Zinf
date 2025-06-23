#ifndef MODO_H_INCLUDED
#define MODO_H_INCLUDED

#include <stdbool.h>
#include "variaveis_globais.h"
#include "jogador.h"
#include "estruturas.h"

//Funcoes que contem os ciclos de cada modo de jogo

void ModoJogo(struct Jogo *jogo, struct Jogo jogosSalvos[]);

void ModoTelaInicial(struct Jogo *jogo);

void ModoMenuInicial(struct Jogo *jogo);

void ModoGameOver(struct Jogo *jogo, struct Score ranking[]);

void ModoEntreNiveis(struct Jogo *jogo, struct Jogo jogosSalvos[]);

void ModoSelecionaJogo(struct Jogo *jogo, int modo, struct Jogo jogosSalvos[]);

void ModoSelecionaNome(struct Jogo *jogo);

void ModoRanking(struct Jogo *jogo, struct Score ranking[]);




#endif // MODO_H_INCLUDED
