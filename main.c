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

/*
 A variavel estado pode ter 4 valores:
    * 0: quando a posição já foi bombardeada
    * 1: quando a jogada é válida
    * 2: posição inválida (quando o usuário informa uma posição que não existe)
    * 5: valor de inicialização
 */
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
            }
            printf("\n");
        }
        printf("\n");
    }
}
int jogadas(char coluna, int linha){
    if((coluna != 'A' && coluna != 'B' && coluna != 'C'
            && coluna != 'D' && coluna != 'E' && coluna != 'F' && coluna != 'G' && coluna != 'H' && coluna != 'I' && coluna != 'J' && coluna != 'L' && coluna != 'M')) {
        return 2 ; // Caso a coluna seria invalida
    }else if((linha != 0 && linha != 1 && linha != 2 && linha != 3 && linha != 4 && linha != 5 && linha !=6 && linha != 7 && linha != 8 && linha != 9 && linha != 10 && linha != 11)) {
        return 2; // Caso de linha invalida
    }else {

    }
}

// retorna um numero aleatorio dentro do intervalo estabelecido
int numeroRandom(int inicio, int fim) {
    srand(clock());
    int numero = inicio + (rand() % fim);
    return numero;
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

void alocarCT(int tabuleiro[12][12], int inicio) {
    int linha = numeroRandom(0, 11);
    int coluna = numeroRandom(0, 11);
    inicio = 0;
    if (inicio > 11) {
        inicio = 0;
    }
    if (tabuleiro[linha][coluna] != 0 || tabuleiro[linha+1][coluna] != 0 || tabuleiro[linha-1][coluna] != 0 || tabuleiro[linha][coluna+1] != 0 || tabuleiro[linha][coluna-1] != 0 || tabuleiro[linha-1][coluna-1] != 0 || tabuleiro[linha+1][coluna-1] != 0 || tabuleiro[linha+1][coluna+1] != 0 || tabuleiro[linha-1][coluna+1] != 0) {
        inicio += 3;
        alocarCT(tabuleiro, inicio);
    }
    else {
        tabuleiro[linha][coluna] = 1;
    }
}

void alocarIAPA(int tabuleiro[12][12], int inicio) {
    int direcao = numeroRandom(1, 2);
    inicio = 0;
    if (inicio > 8) {
        inicio = 0;
    }
    if (direcao == 1) {
        int linha = numeroRandom(0, 10);
        int coluna = numeroRandom(inicio, 11);
        if(verifica(tabuleiro, linha, coluna, direcao, 2) == 1) {
            for (int i=linha; i<linha+2; i++) {
                tabuleiro[i][coluna] = 2;
            }
        }
        else {
            inicio += 3;
            alocarIAPA(tabuleiro, inicio);
        }
    }
    else {
        int linha = numeroRandom(0, 11);
        int coluna = numeroRandom(inicio, 10);
        if(verifica(tabuleiro, linha, coluna, direcao, 2) == 1) {
            for (int i=coluna; i<coluna+2; i++) {
                tabuleiro[linha][i] = 2;
            }
        }
        else {
            inicio += 3;
            alocarIAPA(tabuleiro, inicio);
        }
    }
}

void alocarBMT(int tabuleiro[12][12], int inicio) {
    int direcao = numeroRandom(1, 2);// 1 para vertical, 2 para horizontal
    inicio = 0;// contador para alterar o intervalo dos valores linha/coluna, garantindo maior distribuição na matriz
    if (inicio > 9) {// garante que o contador esteja no limite para que a estrutura não ultrapasse a matriz
        inicio = 0;
    }
    if (direcao == 1) {
        int linha = numeroRandom(0, 9);// gera uma valor aleatorio para a linha
        int coluna = numeroRandom(inicio, 11);// gera um valor aleatorio para a coluna
        if(verifica(tabuleiro, linha, coluna, direcao, 3) == 1) {
            for (int i=linha; i<linha+3; i++) {// alocação da estrutura na matriz
                tabuleiro[i][coluna] = 3;
            }
        }
        else {
            inicio += 3;
            alocarBMT(tabuleiro, inicio);// chamada recursiva caso a estrutura não seja alocada na matriz
        }
    }
    else {
        int linha = numeroRandom(0, 11);
        int coluna = numeroRandom(inicio, 9);
        if(verifica(tabuleiro, linha, coluna, direcao, 3) == 1) {
            for (int i=coluna; i<coluna+3; i++) {
                tabuleiro[linha][i] = 3;
            }
        }
        else {
            inicio += 3;
            alocarBMT(tabuleiro, inicio);
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
    alocarBMT(tabuleiro, 0);
    alocarBMT(tabuleiro, 0);
    alocarIAPA(tabuleiro, 0);
    alocarIAPA(tabuleiro, 0);
    alocarCT(tabuleiro, 0);
    alocarCT(tabuleiro, 0);
    alocarCT(tabuleiro, 0);
    alocarCT(tabuleiro, 0);
}

int main() {
    alocar();
    desenharInterface(0);
    return 0;
}
