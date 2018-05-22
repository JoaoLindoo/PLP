#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Grupo :
 * João
 * Redson
 * Hector
 * Matheus
 * Luan
 */

int tabuleiro[12][12];
int tabuleiroCopia[12][12];
int estado = 5;
int pontuacao = 0;
int bombas = 50;
/*
 A variavel estado pode ter 4 valores:
    * 0: quando a posição já foi bombardeada
    * 1: quando a jogada é válida
    * 2: posição inválida (quando o usuário informa uma posição que não existe)
    * 5: valor de inicialização
 */


// retorna um numero aleatorio dentro do intervalo estabelecido
int numeroRandom(int inicio, int fim) {
    int intervalo = (fim - inicio) + 1;
    srand(clock());
    return inicio + (rand() % intervalo);
}

//garante que as estruturas fiquem separadas na matriz
int verifica(int tabuleiro[12][12], int linha, int coluna, int direcao, int tamanho) {
    if (direcao == 1) {
        if (tabuleiro[linha-1][coluna] != 0 || tabuleiro[linha+tamanho][coluna] != 0 || tabuleiro[linha-1][coluna-1] != 0 || tabuleiro[linha-1][coluna+1] != 0 || tabuleiro[linha+tamanho][coluna-1] != 0 || tabuleiro[linha+tamanho][coluna+1] != 0) {
            return 0;
        }
        for (int i=linha; i<linha+tamanho; i++) {
            if(tabuleiro[i][coluna] != 0 || tabuleiro[i][coluna+1] != 0 || tabuleiro[i][coluna-1] != 0) {
                return 0;
            }
        }
        return 1;
    }
    else {
        if (tabuleiro[linha][coluna-1] != 0 || tabuleiro[linha][coluna+tamanho] != 0 || tabuleiro[linha-1][coluna-1] != 0 || tabuleiro[linha+1][coluna-1] != 0 || tabuleiro[linha-1][coluna+tamanho] != 0 || tabuleiro[linha+1][coluna+tamanho] != 0) {
            return 0;
        }
        for (int i=coluna; i<coluna+tamanho; i++) {
            if(tabuleiro[linha][i] != 0 || tabuleiro[linha+1][i] != 0 || tabuleiro[linha-1][i] != 0) {
                return 0;
            }
        }
        return 1;
    }
}

void alocarCT(int tabuleiro[12][12]) {
    int linha = numeroRandom(0, 11);
    int coluna = numeroRandom(0, 11);
    if (tabuleiro[linha][coluna] != 0 || tabuleiro[linha+1][coluna] != 0 || tabuleiro[linha-1][coluna] != 0 || tabuleiro[linha][coluna+1] != 0 || tabuleiro[linha][coluna-1] != 0 || tabuleiro[linha-1][coluna-1] != 0 || tabuleiro[linha+1][coluna-1] != 0 || tabuleiro[linha+1][coluna+1] != 0 || tabuleiro[linha-1][coluna+1] != 0) {
        alocarCT(tabuleiro);
    }
    else {
        tabuleiro[linha][coluna] = 1;
    }
}

void alocarIAPA(int tabuleiro[12][12]) {
    int direcao = numeroRandom(1, 2);
    if (direcao == 1) {
        int linha = numeroRandom(0, 10);
        int coluna = numeroRandom(0, 11);
        if(verifica(tabuleiro, linha, coluna, direcao, 2) == 1) {
            for (int i=linha; i<linha+2; i++) {
                tabuleiro[i][coluna] = 2;
            }
        }
        else {
            alocarIAPA(tabuleiro);
        }
    }
    else {
        int linha = numeroRandom(0, 11);
        int coluna = numeroRandom(0, 10);
        if(verifica(tabuleiro, linha, coluna, direcao, 2) == 1) {
            for (int i=coluna; i<coluna+2; i++) {
                tabuleiro[linha][i] = 2;
            }
        }
        else {
            alocarIAPA(tabuleiro);
        }
    }
}

void alocarBMT(int tabuleiro[12][12]) {
    int direcao = numeroRandom(1, 2);// 1 para vertical, 2 para horizontal
    if (direcao == 1) {
        int linha = numeroRandom(0, 9);// gera uma valor aleatorio para a linha
        int coluna = numeroRandom(0, 11);// gera um valor aleatorio para a coluna
        if(verifica(tabuleiro, linha, coluna, direcao, 3) == 1) {
            for (int i=linha; i<linha+3; i++) {// alocação da estrutura na matriz
                tabuleiro[i][coluna] = 3;
            }
        }
        else {
            alocarBMT(tabuleiro);// chamada recursiva caso a estrutura não seja alocada na matriz
        }
    }
    else {
        int linha = numeroRandom(0, 11);
        int coluna = numeroRandom(0, 9);
        if(verifica(tabuleiro, linha, coluna, direcao, 3) == 1) {
            for (int i=coluna; i<coluna+3; i++) {
                tabuleiro[linha][i] = 3;
            }
        }
        else {
            alocarBMT(tabuleiro);
        }
    }
}

void alocarBPC(int tabuleiro[12][12]){
    int direcao = numeroRandom(1, 2);
    if (direcao == 1) {
        int linha = numeroRandom(0, 8);
        int coluna = numeroRandom(0, 11);
        for (int i=linha; i<linha+4; i++) {
            tabuleiro[i][coluna] = 4;
        }
    }
    else {
        int linha = numeroRandom(0, 11);
        int coluna = numeroRandom(0, 8);
        for (int i=coluna; i<coluna+4; i++) {
            tabuleiro[linha][i] = 4;
        }
    }
}


// alocação automática de estruturas na matriz
void alocar() {
    alocarBPC(tabuleiro);
    alocarBMT(tabuleiro);
    alocarBMT(tabuleiro);
    alocarIAPA(tabuleiro);
    alocarIAPA(tabuleiro);
    alocarCT(tabuleiro);
    alocarCT(tabuleiro);
    alocarCT(tabuleiro);
    alocarCT(tabuleiro);
}

void desenharInterface (int mostrarTerreno){
    int i, j;
    if( mostrarTerreno == 0){
        printf("################################################################\n");
        printf("#############       bombardment of the virus       #############\n");
        printf("################################################################\n\n");
        printf("      A    B    C    D    E    F    G    H    I    J    L    M\n");
        printf("----------------------------------------------------------------\n");
        for(i = 0; i <= 11 ; i++){
            if (i > 9) {
                printf("%i |", i);
            }
            else {
                printf("%i  |", i);
            }
            for(j = 0; j <= 11; j++){
                if(tabuleiroCopia[i][j] == 0) printf("  ~ |");
                if(tabuleiroCopia[i][j] == 1) printf("  1 |");
                if(tabuleiroCopia[i][j] == 2) printf("  2 |");
                if(tabuleiroCopia[i][j] == 3) printf("  3 |");
                if(tabuleiroCopia[i][j] == 4) printf("  4 |");

            }
            printf("\n");
        }
        printf("\n");
    }
}
int jogadas(char coluna, int linha){
    int colunaID;
    bombas--;
    if((coluna != 'A' && coluna != 'B' && coluna != 'C'
            && coluna != 'D' && coluna != 'E' && coluna != 'F' && coluna != 'G' && coluna != 'H' && coluna != 'I' && coluna != 'J' && coluna != 'L' && coluna != 'M')) {
        return 2 ; // Caso a coluna seria invalida
    }else if((linha != 0 && linha != 1 && linha != 2 && linha != 3 && linha != 4 && linha != 5 && linha !=6 && linha != 7 && linha != 8 && linha != 9 && linha != 10 && linha != 11)) {
        return 2; // Caso de linha invalida
    }else {
        // posição valida
        if(coluna == 'A') colunaID = 0;
        if(coluna == 'B') colunaID = 1;
        if(coluna == 'C') colunaID = 2;
        if(coluna == 'D') colunaID = 3;
        if(coluna == 'E') colunaID = 4;
        if(coluna == 'F') colunaID = 5;
        if(coluna == 'G') colunaID = 6;
        if(coluna == 'H') colunaID = 7;
        if(coluna == 'I') colunaID = 8;
        if(coluna == 'J') colunaID = 9;
        if(coluna == 'L') colunaID = 10;
        if(coluna == 'M') colunaID = 11;
        //posicao ja bombardeada
        if(tabuleiroCopia[linha][colunaID] != 0){
            return 0;
        }else {
        // Se existir base
            if(tabuleiro[linha][colunaID] != 0) {
                pontuacao ++;

                if(tabuleiro[linha][colunaID] == 1) {
                    tabuleiroCopia[linha][colunaID] = 1;
                }
                if(tabuleiro[linha][colunaID] == 2) {
                     tabuleiroCopia[linha][colunaID] = 2;
                }
                if(tabuleiro[linha][colunaID] == 3) {
                     tabuleiroCopia[linha][colunaID] = 3;
                }
                if(tabuleiro[linha][colunaID] == 4) {
                     tabuleiroCopia[linha][colunaID] = 4;

                }
            }else {
                tabuleiroCopia[linha][colunaID] = "X"; // Tiro no terreno
            }
            return 1;
        }
     }
}
void menuGrafico();
int main() {
    printf("SALVE O MUNDO \n\n");
    int i;
    int j;
    int linha;
    char coluna;
    alocar();
    while(pontuacao != 18 && bombas > 0) {
        desenharInterface(0);
        printf("COLUNA => ");
        scanf("%c", &coluna);
        printf("LINHA => ");
        scanf("%i", &linha);
        getchar();
        estado = jogadas(coluna,linha);
        system("clear");
    }

    return 0;
}
