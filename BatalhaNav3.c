#include <stdio.h>
#include <stdlib.h>  // Para a função abs()

#define Tamanho_tabuleiro 10
#define Tamanho_navio 3
#define Agua 0
#define Navio 3
#define Habilidade 5
#define Tamanho_habilidade 5  // Tamanho das matrizes de habilidade (5x5)

void inicializarTabuleiro(int tabuleiro[Tamanho_tabuleiro][Tamanho_tabuleiro]) {
    for (int i = 0; i < Tamanho_tabuleiro; i++) {
        for (int j = 0; j < Tamanho_tabuleiro; j++) {
            tabuleiro[i][j] = Agua;
        }
    }
}

void exibirTabuleiro(int tabuleiro[Tamanho_tabuleiro][Tamanho_tabuleiro]) {
    printf("\n    ");
    for (int i = 0; i < Tamanho_tabuleiro; i++) {
        printf(" %c ", 'A' + i);
    }
    printf("\n");

    for (int i = 0; i < Tamanho_tabuleiro; i++) {
        printf("%2d |", i);
        for (int j = 0; j < Tamanho_tabuleiro; j++) {
            if (tabuleiro[i][j] == Agua)
                printf(" ~ ");
            else if (tabuleiro[i][j] == Navio)
                printf(" N ");
            else if (tabuleiro[i][j] == Habilidade)
                printf(" * ");
        }
        printf("\n");
    }
}

// Gera a matriz da habilidade Cone (forma de V invertido)
void gerarMatrizCone(int matriz[Tamanho_habilidade][Tamanho_habilidade]) {
    for (int i = 0; i < Tamanho_habilidade; i++) {
        for (int j = 0; j < Tamanho_habilidade; j++) {
            if (i >= j - 2 && i >= 2 - j)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Gera a matriz da habilidade Cruz
void gerarMatrizCruz(int matriz[Tamanho_habilidade][Tamanho_habilidade]) {
    for (int i = 0; i < Tamanho_habilidade; i++) {
        for (int j = 0; j < Tamanho_habilidade; j++) {
            if (i == Tamanho_habilidade / 2 || j == Tamanho_habilidade / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Gera a matriz da habilidade Octaedro (formato de losango)
void gerarMatrizOctaedro(int matriz[Tamanho_habilidade][Tamanho_habilidade]) {
    for (int i = 0; i < Tamanho_habilidade; i++) {
        for (int j = 0; j < Tamanho_habilidade; j++) {
            if (abs(i - 2) + abs(j - 2) <= 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Aplica uma matriz de habilidade ao tabuleiro com ponto de origem central
void aplicarHabilidade(int tabuleiro[Tamanho_tabuleiro][Tamanho_tabuleiro],
                       int habilidade[Tamanho_habilidade][Tamanho_habilidade],
                       int origem_linha, int origem_coluna) {
    for (int i = 0; i < Tamanho_habilidade; i++) {
        for (int j = 0; j < Tamanho_habilidade; j++) {
            if (habilidade[i][j] == 1) {
                int l = origem_linha + i - Tamanho_habilidade / 2;
                int c = origem_coluna + j - Tamanho_habilidade / 2;
                if (l >= 0 && l < Tamanho_tabuleiro && c >= 0 && c < Tamanho_tabuleiro) {
                    if (tabuleiro[l][c] != Navio)
                        tabuleiro[l][c] = Habilidade;
                }
            }
        }
    }
}

int podeColocarNavio(int tabuleiro[Tamanho_tabuleiro][Tamanho_tabuleiro], int linha, int coluna, char orientacao) {
    for (int i = 0; i < Tamanho_navio; i++) {
        int l = linha, c = coluna;

        if (orientacao == 'H') c += i;
        else if (orientacao == 'V') l += i;
        else if (orientacao == 'D') { l += i; c += i; }
        else if (orientacao == 'd') { l += i; c -= i; }

        if (l < 0 || l >= Tamanho_tabuleiro || c < 0 || c >= Tamanho_tabuleiro) return 0;
        if (tabuleiro[l][c] == Navio) return 0;
    }
    return 1;
}

void posicionarNavio(int tabuleiro[Tamanho_tabuleiro][Tamanho_tabuleiro], int linha, int coluna, char orientacao) {
    for (int i = 0; i < Tamanho_navio; i++) {
        int l = linha, c = coluna;

        if (orientacao == 'H') c += i;
        else if (orientacao == 'V') l += i;
        else if (orientacao == 'D') { l += i; c += i; }
        else if (orientacao == 'd') { l += i; c -= i; }

        tabuleiro[l][c] = Navio;
    }
}

int main() {
    int tabuleiro[Tamanho_tabuleiro][Tamanho_tabuleiro];
    inicializarTabuleiro(tabuleiro);

    // Posicionamento dos navios
    if (podeColocarNavio(tabuleiro, 1, 1, 'H')) posicionarNavio(tabuleiro, 1, 1, 'H');
    if (podeColocarNavio(tabuleiro, 4, 7, 'V')) posicionarNavio(tabuleiro, 4, 7, 'V');
    if (podeColocarNavio(tabuleiro, 0, 6, 'D')) posicionarNavio(tabuleiro, 0, 6, 'D');
    if (podeColocarNavio(tabuleiro, 5, 2, 'd')) posicionarNavio(tabuleiro, 5, 2, 'd');

    // Matrizes de habilidades
    int cone[Tamanho_habilidade][Tamanho_habilidade];
    int cruz[Tamanho_habilidade][Tamanho_habilidade];
    int octaedro[Tamanho_habilidade][Tamanho_habilidade];

    gerarMatrizCone(cone);
    gerarMatrizCruz(cruz);
    gerarMatrizOctaedro(octaedro);

    // Aplicação das habilidades
    aplicarHabilidade(tabuleiro, cone, 2, 2);
    aplicarHabilidade(tabuleiro, cruz, 6, 6);
    aplicarHabilidade(tabuleiro, octaedro, 8, 3);

    printf("\n------Tabuleiro Batalha Naval------\n");
    exibirTabuleiro(tabuleiro);
    printf("\n----Fim de jogo----\n");
    printf("\nLegenda: ~ = Água | N = Navio | * = Área Afetada\n");

    return 0;
}

