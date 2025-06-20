#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdbool.h>
#include "variaveis_globais.h"
#include "jogador.h"
#include "estruturas.h"

void IniciaJogo(struct Jogo *jogo);
void CriaSeta(struct Seta *seta);
void DesenhaTitulo();
void DesenhaSeta(struct Seta seta);
void MovimentaSeta(struct Seta *seta);
void DesenhaOpcoesMenuInicial();
void DesenhaBarraStatus(struct Player player);
void DesenhaFimDoNivel();
void DesenhaGameOver();


#endif // MENU_H_INCLUDED
