#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED

#include "raylib.h"

enum Modo {
    TELAINICIAL,
    MENUINICIAL,
    JOGO,
    PAUSE,
    NOVOJOGO,
    CARREGAR,
    SALVAR,
    RANKING,
    GAMEOVER,
    TELAENTRENIVEIS,
    SELECIONANOME,
    FIM
};

enum OpcoesMenuInicial {
    MENUINICIAL_NOVOJOGO,
    MENUINICIAL_CARREGAR,
    MENUINICIAL_RANKING,
    MENUINICIAL_SAIR
};

enum OpcoesMenuPause {
    MENUPAUSE_VOLTAR,
    MENUPAUSE_SALVAR,
    MENUPAUSE_MENUINICIAL,
    MENUPAUSE_SAIR
};

enum Saves {
    SAVE1,
    SAVE2,
    SAVE3,
    SAVE4,
    SAVE5,
    SAIR
};


struct Monstro
{
    Rectangle hitbox;
    int vida, id, forca, score;
    float velocidadeMovimento, raioVisao, timerMovimento, distanciaPlayer, timerStun;
    char tipo; // 'M' = monstro, 'E' = vazio
    char orientacao; // 'U' = cima, 'D' = baixo, 'L' = esquerda, 'D' = direita
    char status; //'E' = esperando, 'M' = Movimentando, 'S' = Stun
    bool stun, vivo;
    float timerAnimacao, MonsterFPS;
    int contadorFrame;
};

struct Player
{
    Rectangle hitbox;
    int velocidadeMovimento, vidas, municao, timerStun, numeroDeBalasNaTela, timerTiro;
    char orientacao, armaAtual;
    bool stun, atirando, movendo;
    int score;
    float timerAnimacao, PlayerFPS;
    int contadorFrame;
    //Variável armaAtual:
    //P = pistola;
    //C = chicote;
    //E = vazio.
    //Número de balas da pistola. Só é relevante quando o jogar está com a pistola.
};

struct Bala {
    Rectangle hitbox;
    int velocidadeBala;
    char orientacao;
    bool ataque;
};

struct Obstaculo {
    Rectangle hitbox;
    char tipo;
};

struct Chicote {
    Rectangle hitbox;
    bool ataque;
};

struct Jogo {
    int nivel, numeroDeMonstrosVivos, vidasDoPlayer, score, municao;
    char armaAtual;
    bool ocupado;
    char nome[TAMANHOTEXTO];
    enum Modo modoDeJogo;
    enum Saves saveSlot;
};

struct Seta {
    Rectangle posicao;
    enum OpcoesMenuInicial opcao;
    enum OpcoesMenuPause opcaoPause;
    enum Saves save;
};

struct Score {
    char nome[TAMANHOTEXTO];
    int score;
};




#endif // ESTRUTURAS_H_INCLUDED
