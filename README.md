#include <stdio.h>

#define JOGADOR_X 'X'
#define JOGADOR_O 'O'
#define EMPATE 'E'
#define CARACTERE_BRANCO '_'

typedef struct{
    char tabuleiro[3][3];
    char jogadorAtual;
    int jogadas;
    char ganhador;
}JogodaVelha;

void inicializarJogo(JogodaVelha *jogo){
    int linha, coluna;
    jogo->jogadorAtual = JOGADOR_X;
    jogo->ganhador = 0;
    jogo->jogadas = 9;

    for(linha = 0; linha<3; linha++){
        for(coluna = 0; coluna<3; coluna++){
            jogo->tabuleiro[linha][coluna] = CARACTERE_BRANCO;
        }
    }
}

void exibirTabuleiro(JogodaVelha *jogo){
    int linha, coluna;
    printf("\n-----TABULEIRO-----\n\n");

    for(linha = 0; linha<3; linha++){
        for(coluna = 0; coluna<3; coluna++){
            printf("%c", jogo->tabuleiro[linha][coluna]);
            if(coluna<2){
                printf("|");
            }
            else{
                printf("\n");
            }

            if(linha<2){
                printf("---------\n");
            }
            else{
                printf("\n");
            }
        }
    }
}

void alternarJogador(JogodaVelha *jogo){
    if(jogo->jogadorAtual == JOGADOR_X){
       jogo->jogadorAtual = JOGADOR_O;
    }
    jogo->jogadorAtual = JOGADOR_X;
}

int realizarJogada(JogodaVelha *jogo, int posicao){
    if(!(posicao>=1 && posicao<=9)){
        printf("posiçao invalida! Digite um valor de 1 a 9! >:(\n");
        return 0;
    }
    posicao= posicao-1;
    int linha, coluna;

    if(posicao<3){
        linha=1;
        coluna=posicao;
    }
    else if(posicao<6){
        linha=2;
        coluna=posicao-3;
    }
    else{
        linha=3;
        coluna=posicao-6;
    }

    if(jogo->tabuleiro[linha][coluna]!=CARACTERE_BRANCO){
        printf("digite uma posiçao que ainda nao foi preenchida.\n");
        return 1;
    }

    jogo->tabuleiro[linha][coluna]= jogo->jogadorAtual;
    jogo->jogadas-=1;

    alternarJogador(jogo);

    return 2;
}

int verificarGanhador(JogodaVelha *jogo){
    int i;
    int linha, coluna;

     for(linha = 0; linha<3; linha++){
        for(coluna = 0; coluna<3; coluna++){
            if(jogo->tabuleiro[linha][0] != CARACTERE_BRANCO && jogo->tabuleiro[linha][0] == jogo->tabuleiro[linha][1] && jogo->tabuleiro[linha][0] == jogo->tabuleiro[linha][2]){
                jogo->ganhador= jogo->jogadorAtual;
                return 0;
            }
            else if(jogo->tabuleiro[0][coluna] != CARACTERE_BRANCO && jogo->tabuleiro[0][coluna] == jogo->tabuleiro[1][coluna] && jogo->tabuleiro[0][coluna] == jogo->tabuleiro[2][coluna]){
                jogo->ganhador= jogo->jogadorAtual;
                return 1;
            }
            else if(jogo->tabuleiro[0][0] != CARACTERE_BRANCO && jogo->tabuleiro[0][0] == jogo->tabuleiro[1][1] && jogo->tabuleiro[0][0] == jogo->tabuleiro[2][2]){
                jogo->ganhador= jogo->jogadorAtual;
                return 3;
            }
            else if(jogo->tabuleiro[0][2] != CARACTERE_BRANCO && jogo->tabuleiro[0][2] == jogo->tabuleiro[1][1] && jogo->tabuleiro[0][2] == jogo->tabuleiro[2][0]){
                jogo->ganhador= jogo->jogadorAtual;
                return 4;
            }
            else if(jogo->jogadas==0){
                jogo->ganhador= EMPATE;
                return 5;
            }
            else{
                return 6;
            }
        }
    }
}

int main(){
    JogodaVelha *jogo;
    int posicao, ganha;

    inicializarJogo(jogo);
    exibirTabuleiro(jogo);

    printf("O primeiro a jogar será o jogador x. Digitem sempre posições de 0 a 9 para fazerem suas jogadas e se divirtam!\n");

    while(ganha!=6){
        printf("digite a posição em que deseja jogar.\n");
        scanf("%d", &posicao);

        realizarJogada(jogo, posicao);
        exibirTabuleiro(jogo);
        ganha= verificarGanhador(jogo);
    }
    if(ganha != 5){
        printf("O jogador atual: %c, venceu!", jogo->jogadorAtual);
    }
    else{
        printf("Empate!");
    }
    return 0;
}
