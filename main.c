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


int tabuleiro[8][8];
int tabuleiroCopia[8][8];
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
        printf("#################################################\n");
        printf("#####        bombardment of the virus       #####\n");
        printf("#################################################\n\n");
        printf("      A    B    C    D    E    F    G    H\n");
        printf("--------------------------------------------\n");
        for(i = 0; i <= 7 ; i++){
            printf("%i  |", i);
            for(j = 0; j <= 7; j++){
                if(tabuleiroCopia[i][j] == 0) printf("  ~ |");
            }
            printf("\n");
        }
        printf("\n");
    }
}
int jogadas(char coluna, int linha){
    if((coluna != 'A' && coluna != 'B' && coluna != 'C'
            && coluna != 'D' && coluna != 'E' && coluna != 'F' && coluna != 'G' && coluna != 'H')) {
        return 2 ; // Caso a coluna seria invalida
    }else if((linha != 0 && linha != 1 && linha != 2 && linha != 3 && linha != 4 && linha != 5 && linha !=6 && linha != 7)) {
        return 2; // Caso de linha invalida
    }else {

    }
}

int numeroRadom(int inicio, int fim){
    int numero;
    return numero;
}
void alocarCT(){

}
void alocarIAPA() {

}
void alocarBMT() {

}
void alocarBPO() {

}
int main() {
    desenharInterface(0);
    return 0;
}