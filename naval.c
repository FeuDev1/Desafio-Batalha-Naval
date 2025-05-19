#include <stdio.h>

// Constantes para tamanho do tabuleiro e dos navios
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// Função para imprimir o tabuleiro
void imprimirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Tabuleiro:\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Declaração do tabuleiro 10x10 e inicialização com 0 (água)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Coordenadas iniciais para o navio horizontal (linha, coluna)
    int linha_horizontal = 2;
    int coluna_horizontal = 4;

    // Coordenadas iniciais para o navio vertical (linha, coluna)
    int linha_vertical = 5;
    int coluna_vertical = 1;

    // Validação: verifica se o navio horizontal cabe no tabuleiro
    if (coluna_horizontal + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        printf("Erro: navio horizontal fora do limite do tabuleiro.\n");
        return 1;
    }

    // Validação: verifica se o navio vertical cabe no tabuleiro
    if (linha_vertical + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        printf("Erro: navio vertical fora do limite do tabuleiro.\n");
        return 1;
    }

    // Validação: verifica se há sobreposição entre os navios
    int sobreposicao = 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (linha_horizontal == linha_vertical + i &&
            coluna_horizontal + i == coluna_vertical) {
            sobreposicao = 1;
            break;
        }
    }

    if (sobreposicao) {
        printf("Erro: os navios se sobrepõem.\n");
        return 1;
    }

    // Posiciona o navio horizontal (valor 3)
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha_horizontal][coluna_horizontal + i] = 3;
    }

    // Posiciona o navio vertical (valor 3)
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha_vertical + i][coluna_vertical] = 3;
    }

    // Exibe o tabuleiro com os navios posicionados
    imprimirTabuleiro(tabuleiro);

    return 0;
}