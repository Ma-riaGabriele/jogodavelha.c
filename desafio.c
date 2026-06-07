#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define JOGADOR_X 'X'
#define JOGADOR_O 'O'
#define EMPATE 'E'
#define CARACTERE_BRANCO '_'
#define SEM_GANHADOR 'N'

typedef struct{
    char tabuleiro[3][3];
    char jogadorAtual;
    int jogadas;
    char ganhador;
} jogoDaVelha;

void inicializarJogo(  jogoDaVelha *jogo);
void exibirTabuleiro( jogoDaVelha *jogo);
int verificarGanhador( jogoDaVelha *jogo);
void alternarJogador( jogoDaVelha *jogo);
int realizarJogada( jogoDaVelha *jogo, int posicao);
void verificaEntrada();

void inicializarJogo( jogoDaVelha *jogo){
    int linha, coluna;
    jogo -> jogadorAtual = JOGADOR_X;
    jogo -> ganhador = SEM_GANHADOR;
    jogo -> jogadas = 9;

    for(linha = 0; linha < 3; linha++){
        for(coluna = 0; coluna < 3; coluna++){
            jogo -> tabuleiro[linha][coluna] = CARACTERE_BRANCO;
        }
    }
}

 void exibirTabuleiro( jogoDaVelha *jogo){
    int linha, coluna;

    printf("\n");
    printf("  +---+---+---+\n");
    for(linha = 0; linha < 3; linha++){
        printf("  |");
        for(coluna = 0; coluna < 3; coluna++){
            if(jogo->tabuleiro[linha][coluna] == JOGADOR_X)
                printf(" X |");
            else if(jogo->tabuleiro[linha][coluna] == JOGADOR_O)
                printf(" O |");
            else
                printf(" . |");
        }
        printf("\n");
        if(linha < 2)
            printf("  +---+---+---+\n");
    }
    printf("  +---+---+---+\n");
    printf("\n");
}

void alternarJogador( jogoDaVelha *jogo){
    if(jogo -> jogadorAtual == JOGADOR_X){
       jogo -> jogadorAtual = JOGADOR_O;
    }
    else{
       jogo -> jogadorAtual = JOGADOR_X;
    }
}

int realizarJogada( jogoDaVelha *jogo, int posicao){
    if(!(posicao >= 1 && posicao <= 9)){
        printf("Posicao invalida! Digite um valor de 1 a 9!\n");
        return 0;
    }
    
    posicao = posicao -1;
    int linha, coluna;

    if(posicao < 3){
        linha = 0;
        coluna = posicao;
    }
    else if(posicao < 6){
        linha = 1;
        coluna = posicao - 3;
    }
    else{
        linha = 2;
        coluna = posicao - 6;
    }

    if(jogo -> tabuleiro[linha][coluna] != CARACTERE_BRANCO){
        printf("Digite uma posicao que ainda nao foi preenchida.\n");
        return 1;
    }

    jogo -> tabuleiro[linha][coluna]= jogo -> jogadorAtual;
    jogo -> jogadas -= 1;

    verificarGanhador(jogo);

    if(jogo -> ganhador == SEM_GANHADOR){
        alternarJogador(jogo);
    }

    return 2;
}

int verificarGanhador( jogoDaVelha *jogo){
    int linha, coluna;
 
    for(linha = 0; linha < 3; linha++){
        if(jogo -> tabuleiro[linha][0] != CARACTERE_BRANCO && jogo -> tabuleiro[linha][0] == jogo -> tabuleiro[linha][1] && jogo -> tabuleiro[linha][0] == jogo -> tabuleiro[linha][2]){
            jogo -> ganhador= jogo -> jogadorAtual;
            return 0;
        }
    }

    for(coluna = 0; coluna<3; coluna++){
        if(jogo->tabuleiro[0][coluna] != CARACTERE_BRANCO && jogo->tabuleiro[0][coluna] == jogo->tabuleiro[1][coluna] && jogo->tabuleiro[0][coluna] == jogo->tabuleiro[2][coluna]){
            jogo->ganhador= jogo->jogadorAtual;
            return 1;
        }
    }

    if(jogo -> tabuleiro[0][0] != CARACTERE_BRANCO && jogo -> tabuleiro[0][0] == jogo->tabuleiro[1][1] && jogo -> tabuleiro[0][0] == jogo->tabuleiro[2][2]){
        jogo -> ganhador= jogo->jogadorAtual;
        return 3;
    }

    if(jogo -> tabuleiro[0][2] != CARACTERE_BRANCO && jogo -> tabuleiro[0][2] == jogo->tabuleiro[1][1] && jogo -> tabuleiro[0][2] == jogo->tabuleiro[2][0]){
        jogo -> ganhador= jogo->jogadorAtual;
        return 4;
    }

    if(jogo -> jogadas == 0){
        jogo -> ganhador= EMPATE;
        return 5;
    }

    return 6;
}

void verificaEntrada(){
    int caractere;
    while((caractere = getchar()) != '\n' && caractere != EOF);
}

int main(){
    jogoDaVelha *jogo = (jogoDaVelha*) malloc (sizeof(jogoDaVelha));
    int posicao, ganha;

    inicializarJogo(jogo);

    printf("\n");
    printf("================================\n");
    printf("       JOGUIN DA VELHA  :)        \n");
    printf("================================\n");
    printf("O X comeca jogando.\n");
    printf("Use as posicoes 1 a 9!\n\n");

    while(jogo -> ganhador == SEM_GANHADOR){
        exibirTabuleiro(jogo);
        printf("Jogador %c, digite a posicao em que deseja jogar:\n", jogo -> jogadorAtual);

        if(scanf("%d", &posicao) != 1){
            printf("Entrada invalida. Digite um numero.\n");
           verificaEntrada();
            continue;
        }
       verificaEntrada();

        realizarJogada(jogo, posicao);
        exibirTabuleiro(jogo);
        ganha = verificarGanhador(jogo);
    }

    if(ganha != 5){
        printf("O jogador %c, venceu! Se garantiu :D\n", jogo -> jogadorAtual);
    }
    else{
        printf("Deu velha, mo paia ):<\n");
    }

    free(jogo);
    return 0;
}
