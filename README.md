# Zinf



Autoria:

\- Luis Henrique Macedo Jr: Código e manutenção do repositório

\- Gabriel da Luz de Souza: Arte e conceito





O jogo pode ser compilado através do editor CodeBlocks.

Uma versão compilada e executável encontra-se em "Zinf - executavel.7z"



1 - Como jogar

A partir do menu inicial, inicie um novo jogo em um slot não preenchido.

Insira o nome do jogador e pressione Enter. O personagem principal

possui os seguintes comandos:

W - cima

A - esquerda

S - baixo

D - direita

J - golpe com chicote (se disponível)

K - atira com arma (se houver munição)

P - pausa a tela e abre o menu de pause

Cada fase termina quando o jogador derrotar todos os inimigos da tela.

Cada inimigo gera uma pontuação, com um valor entre 1-100. O jogador

pode usar o chicote ou a pistola para eliminar os inimigos. Caso perca

todas as vidas, o jogo acaba e retorna à tela inicial, com o score sendo

salvo em um ranking.

O salvamento ocorre de forma automática na passagem de cada nível,

porém, caso queira, o jogador pode salvar manualmente no menu

pause. Um jogo salvo pode ser carregado através da opção carregar

jogo no menu inicial.



2 - Funcionalidades implementadas

Movimento automático de monstros:

\- Cada monstro move-se aleatoriamente em uma de quatro

direções. Caso o jogador esteja no raio de visão do monstro, o

monstro persegue o jogador.

Knockback durante dano:

\- Ao receberem dano, tanto o jogador quanto os monstros sofrem

um recuo relacionado ao dano, com exceção do dano com projétil,

onde não há knockback

Pistola como arma:

\- O jogador pode coletar munições, que podem ser utilizadas ao

apertar K.

Animações:

\- Foi implementado um ciclo de animação para o jogador, os

monstros, itens e cenário

Stun:

\- Ao receber dano, tanto o jogador quanto os monstros ficam

imunes a novos danos por um período de tempo.

Hitbox:

\- Cada estrutura possui uma hitbox. Uma hitbox é um Rectangle,

que, através da função CheckCollisionRec, permite identificar

quando quaisquer duas hitbox estão em contato. A hitbox do

player e dos monstros é ligeiramente menor que seus sprites, de

forma a balancear o gameplay.

Salvamento e carregamento de jogo:

\- O jogo é salvo durante a passagem de cada nível e de forma

manual através do menu de pause. O jogo pode ser carregado

através do menu de carregamento de jogo.

Ranking:

\- O ranking é atualizado sempre que o jogador morre, e pode ser

acessado através do menu inicial.

Menu pause:

\- O jogo pode ser pausado a qualquer momento utilizando a tecla P.

O menu permite o retorno ao menu inicial, salvamento de jogo,

retorno ao jogo e encerramento da aplicação.



4 - Estrutura do código

O código foi separado em diferentes arquivos .c e .h, de forma a

organizar a construção do aplicativo. Em linhas gerais, a lógica do

aplicativo se dá da seguinte forma nas duas principais funções:

Função main:

\- Uma estrutura Jogo guarda informações que serão reutilizadas por

todas as subfunções para declarar o modo do jogo e dados do

jogador. A função main inicializa uma estrutura Jogo.

\- Um array de estruturas Jogo é criado e, então, preenchido com um

array de Jogos contidos em um arquivo .bin (caso não exista, será

criado). Estes representam os jogos salvos e poderão ser

carregados pelo menu.

\- Um array de estruturas Score é criado e preenchido com os scores

armazenados em um arquivo binário.

\- A função main checa continuamente o atributo modo de jogo da

variável Jogo. Esse atributo é definido por uma enumeração,

contendo os seguintes modos de jogo, cujos ciclos estão

declarados em suas respectivas funções, no arquivo modo.c:

\- Tela Inicial

\- Menu Inicial

\- Seleção de Jogo

\- Seleção de Nome

\- Ranking

\- Tela Entre Níveis

\- Game Over

\- Jogo

\- Caso haja mudança na variável, um novo modo de jogo é

acionado.

Função modoJogo:

\- São inicializadas as estruturas Jogador, um array de Monstros, um

array de Obstáculos, um array de Balas e uma matriz de

caracteres representando o mapa, além das estruturas Chicote e

Seta (para o menu de pause).

\- É realizada a leitura do arquivo de mapa em formato de txt, que

preenche a matriz de caracteres.

\- O jogador, o array de monstros e o array de obstáculos são

atualizados conforme a matriz de caracteres do mapa.

\- As texturas são carregadas.

\- O ciclo de leitura contínua se inicia e se mantém enquanto o modo

de jogo estiver definido como Jogo.

\- O movimento do player é lido, e permitido somente quando não há

colisão.

\- É checada a colisão com itens, modificando a estrutura jogador

conforme for condizente.

\- As detecções de ataque, tanto do jogador quanto dos monstros

ocorrem, gerando os respectivos danos, aplicando-se o knockback

e iniciando o timer de stun.

\- O ciclo de movimentação de monstros ocorre, alternando-se entre

o status de movimento e espera, que utiliza um timer para ocorrer.

\- Caso haja pause, o ciclo se interrompe e um menu inicial é aberto,

possibilitando o salvamento de jogo, retorno ao menu inicial e

saída do jogo.

\- Caso o jogador perca todas as vidas, o modo de jogo é alterado

para fim de jogo. O score então é salvo no arquivo binário de

ranking e o jogador é redirecionado à tela inicial.

\- Caso todos os inimigos morram, o modo de jogo é alterado para a

tela entre níveis, onde ocorre o salvamento automático da

estrutura jogo na sua respectiva posição do array de jogos do

arquivo de salvamento binário. O modo de jogo então é alterado

novamente para jogo e o próximo nível é carregado.

\- O jogo é capaz de ler até 99 mapas. Em nossa implementação,

foram desenhados 11 mapas, sem um fim de jogo. Caso o jogador

atinja o último nível, o jogo continuará procurando por novos

mapas.



5 - Ferramentas:

A plataforma Github foi utilizada extensivamente para a realização do

projeto.

A biblioteca Raylib e a IDE CodeBlocks foram utilizadas como

ferramentas de desenvolvimento.

