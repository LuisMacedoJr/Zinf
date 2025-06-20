#ifndef MODO_H_INCLUDED
#define MODO_H_INCLUDED

#include <stdbool.h>
#include "variaveis_globais.h"
#include "jogador.h"
#include "estruturas.h"

void ModoJogo(struct Jogo *jogo);
void ModoTelaInicial(struct Jogo *jogo);
void ModoMenuInicial(struct Jogo *jogo);

#endif // MODO_H_INCLUDED
