#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define OCUPADO 3
#define AFETADO 5
#define TAMANHO_HABILIDADE 5

// Função para imprimir o tabuleiro com símbolos
void imprimirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%d ", j);
    }
    printf("\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d: ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0) printf(". ");
            else if (tabuleiro[i][j] == OCUPADO) printf("N "); // Navio
            else if (tabuleiro[i][j] == AFETADO) printf("* "); // Área de habilidade
            else printf("? "); // Valor inesperado
        }
        printf("\n");
    }
}

// Cria matriz de cone (5x5)
void criarCone(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            matriz[i][j] = 0;
            // O cone expande para baixo com base no índice da linha
            int meio = TAMANHO_HABILIDADE / 2;
            if (i >= 0 && j >= meio - i && j <= meio + i) {
                matriz[i][j] = 1;
            }
        }
    }
}

// Cria matriz de cruz (5x5)
void criarCruz(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            matriz[i][j] = (i == TAMANHO_HABILIDADE / 2 || j == TAMANHO_HABILIDADE / 2) ? 1 : 0;
        }
    }
}

// Cria matriz de octaedro (losango 5x5)
void criarOctaedro(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            matriz[i][j] = 0;
            int dist = abs(i - TAMANHO_HABILIDADE / 2) + abs(j - TAMANHO_HABILIDADE / 2);
            if (dist <= TAMANHO_HABILIDADE / 2) {
                matriz[i][j] = 1;
            }
        }
    }
}

// Sobrepõe matriz de habilidade no tabuleiro com origem (linha, coluna)
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                       int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                       int origem_linha, int origem_coluna) {
    int offset = TAMANHO_HABILIDADE / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int linha_tab = origem_linha - offset + i;
            int col_tab = origem_coluna - offset + j;

            // Verifica limites
            if (linha_tab >= 0 && linha_tab < TAMANHO_TABULEIRO &&
                col_tab >= 0 && col_tab < TAMANHO_TABULEIRO &&
                habilidade[i][j] == 1 &&
                tabuleiro[linha_tab][col_tab] == 0) { // Não sobrescreve navio
                tabuleiro[linha_tab][col_tab] = AFETADO;
            }
        }
    }
}

// Posiciona navios no tabuleiro (sem sobreposição para simplicidade)
void posicionarNavios(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Navio horizontal (0,0)
    for (int i = 0; i < TAMANHO_NAVIO; i++)
        tabuleiro[0][i] = OCUPADO;

    // Navio vertical (4,5)
    for (int i = 0; i < TAMANHO_NAVIO; i++)
        tabuleiro[4 + i][5] = OCUPADO;

    // Navio diagonal ↘ (6,6)
    for (int i = 0; i < TAMANHO_NAVIO; i++)
        tabuleiro[6 + i][6 + i] = OCUPADO;

    // Navio diagonal ↙ (2,8)
    for (int i = 0; i < TAMANHO_NAVIO; i++)
        tabuleiro[2 + i][8 - i] = OCUPADO;
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Posicionar os navios
    posicionarNavios(tabuleiro);

    // Matrizes de habilidades
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    // Criar as áreas de efeito
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Aplicar habilidades no tabuleiro em diferentes posições
    aplicarHabilidade(tabuleiro, cone, 2, 2);       // Cone no canto superior esquerdo
    aplicarHabilidade(tabuleiro, cruz, 5, 5);       // Cruz no centro
    aplicarHabilidade(tabuleiro, octaedro, 7, 2);   // Octaedro canto inferior esquerdo

    // Exibir o tabuleiro final
    imprimirTabuleiro(tabuleiro);

    return 0;
}