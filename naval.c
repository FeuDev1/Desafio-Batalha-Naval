#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define OCUPADO 3

// Função para imprimir o tabuleiro de forma visual
void imprimirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%d ", j);
    }
    printf("\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d: ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função genérica para verificar se um navio pode ser colocado
int podeColocarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                     int linha, int coluna, int direcao, int diagonal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int li = linha;
        int co = coluna;

        // Direção: 0 = horizontal, 1 = vertical
        // Diagonal: 0 = não diagonal, 1 =  (diagonal principal), 2 =  (diagonal secundária)
        if (diagonal == 0) {
            li = (direcao == 0) ? linha : linha + i;
            co = (direcao == 0) ? coluna + i : coluna;
        } else if (diagonal == 1) { 
            li = linha + i;
            co = coluna + i;
        } else if (diagonal == 2) { 
            li = linha + i;
            co = coluna - i;
        }

        // Valida limites
        if (li >= TAMANHO_TABULEIRO || li < 0 || co >= TAMANHO_TABULEIRO || co < 0) {
            return 0;
        }

        // Verifica sobreposição
        if (tabuleiro[li][co] != 0) {
            return 0;
        }
    }
    return 1;
}

// Função para posicionar navio no tabuleiro
void colocarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                  int linha, int coluna, int direcao, int diagonal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int li = linha;
        int co = coluna;

        if (diagonal == 0) {
            li = (direcao == 0) ? linha : linha + i;
            co = (direcao == 0) ? coluna + i : coluna;
        } else if (diagonal == 1) {
            li = linha + i;
            co = coluna + i;
        } else if (diagonal == 2) {
            li = linha + i;
            co = coluna - i;
        }

        tabuleiro[li][co] = OCUPADO;
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // ---- NAVIOS HORIZONTAIS/VERTICAIS ----

    // Navio 1: horizontal, começa na (0,0)
    if (podeColocarNavio(tabuleiro, 0, 0, 0, 0)) {
        colocarNavio(tabuleiro, 0, 0, 0, 0);
    }

    // Navio 2: vertical, começa na (4, 5)
    if (podeColocarNavio(tabuleiro, 4, 5, 1, 0)) {
        colocarNavio(tabuleiro, 4, 5, 1, 0);
    }

    // ---- NAVIOS DIAGONAIS ----

    // Navio 3: diagonal , começa em (6, 6)
    if (podeColocarNavio(tabuleiro, 6, 6, 0, 1)) {
        colocarNavio(tabuleiro, 6, 6, 0, 1);
    }

    // Navio 4: diagonal , começa em (2, 8)
    if (podeColocarNavio(tabuleiro, 2, 8, 0, 2)) {
        colocarNavio(tabuleiro, 2, 8, 0, 2);
    }

    // Exibir o tabuleiro final
    imprimirTabuleiro(tabuleiro);

    return 0;
}