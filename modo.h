#ifndef MODO_H_INCLUDED
#define MODO_H_INCLUDED

#include <stdbool.h>
#include "variaveis_globais.h"
#include "jogador.h"
#include "estruturas.h"

void ModoJogo(struct Jogo *jogo, struct Jogo jogosSalvos[]);
void ModoTelaInicial(struct Jogo *jogo);
void ModoMenuInicial(struct Jogo *jogo);
void ModoGameOver(struct Jogo *jogo);
void ModoEntreNiveis(struct Jogo *jogo);
void ModoSelecionaJogo(struct Jogo *jogo, int modo, struct Jogo jogosSalvos[]);
void ModoSelecionaNome(struct Jogo *jogo);




#endif // MODO_H_INCLUDED
