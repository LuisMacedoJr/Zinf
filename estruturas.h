#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED

#include "raylib.h"

//Contem as estruturas e enumeracoes utilizadas ao longo do programa


//Enumeracoes do modo de jogo
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

//Enumeracoes das opcoes do menu inicial
enum OpcoesMenuInicial {
    MENUINICIAL_NOVOJOGO,
    MENUINICIAL_CARREGAR,
    MENUINICIAL_RANKING,
    MENUINICIAL_SAIR
};


//Enumeracoes do menu de pause
enum OpcoesMenuPause {
    MENUPAUSE_VOLTAR,
    MENUPAUSE_SALVAR,
    MENUPAUSE_MENUINICIAL,
    MENUPAUSE_SAIR
};


//Enumeracoes dos jogos salvos
enum Saves {
    SAVE1,
    SAVE2,
    SAVE3,
    SAVE4,
    SAVE5,
    SAIR
};

//Estrutura monstro. Contem os dados pertinentes a cada monstro
struct Monstro
{
    Rectangle hitbox;
    int vida, id, forca, score;
    float velocidadeMovimento, raioVisao, timerMovimento, distanciaPlayer, timerStun;
    char tipo; // 'M' = monstro, 'Z' = vazio
    char orientacao; // 'U' = cima, 'D' = baixo, 'L' = esquerda, 'R' = direita
    char status; //'E' = esperando, 'M' = Movimentando
    bool stun, vivo;
    float timerAnimacao, MonsterFPS;
    int contadorFrame;
};

//Estrutura Player. Contem os dados pertinentes ao jogador

struct Player
{
    Rectangle hitbox;
    int velocidadeMovimento, vidas, municao, timerStun, numeroDeBalasNaTela, timerTiro;
    char orientacao, armaAtual;
    bool stun, atirando, movendo;
    int score;
    float timerAnimacao, PlayerFPS;
    int contadorFrame;

};

//Estrutura relativa a cada projetil
struct Bala {
    Rectangle hitbox;
    int velocidadeBala;
    char orientacao;
    bool ataque;
};

//Estrutura que qualifica um objeto
struct Obstaculo {
    Rectangle hitbox;
    char tipo; //P = Parede, B = Municao, C = Chicote, V = vida
    int vidaContadorFrame;
    float vidaTimerAnimacao, vidaFPS;
};

//Estrutura com os dados do chicote
struct Chicote {
    Rectangle hitbox;
    bool ataque;
    char orientacao;
};

//Estrutura com os dados principais do jogo. Essa estrutura sera posicionada em um array de jogos no momento do salvamento
struct Jogo {
    int nivel, numeroDeMonstrosVivos, vidasDoPlayer, score, municao;
    char armaAtual;
    bool ocupado;
    char nome[TAMANHOTEXTO];
    enum Modo modoDeJogo;
    enum Saves saveSlot;
};

//Estrutura relativa ao seletor nos menus
struct Seta {
    Rectangle posicao;
    enum OpcoesMenuInicial opcao;
    enum OpcoesMenuPause opcaoPause;
    enum Saves save;
};

//Estrutura que contem uma pontuacao. Essa estrutura sera posicionada em um array de Scores no momento de atualizacao do ranking
struct Score {
    char nome[TAMANHOTEXTO];
    int score, nivel;
    bool ocupado;
};

//Estrutura referente à bola de feno que passa pela tela periodicamente
struct Feno {
    Rectangle hitbox;
    float angulo;
    bool naTela;
    int timer;
};



#endif // ESTRUTURAS_H_INCLUDED
