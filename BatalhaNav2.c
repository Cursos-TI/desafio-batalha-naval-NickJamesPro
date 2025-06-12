#include <stdio.h>

#define Tamanho_tabuleiro 10
#define Tamanho_navio 3
#define Agua 0
#define Navio 3

// Inicializa o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[Tamanho_tabuleiro][Tamanho_tabuleiro]) {
    for (int i = 0; i < Tamanho_tabuleiro; i++) {
        for (int j = 0; j < Tamanho_tabuleiro; j++) {
            tabuleiro[i][j] = Agua;
        }
    }
}

// Exibeição do tabuleiro
void exibirTabuleiro(int tabuleiro[Tamanho_tabuleiro][Tamanho_tabuleiro]) {
    printf("\n    ");
    for (int i = 0; i < Tamanho_tabuleiro; i++) {
        printf(" %c ", 'A' + i);
    }
    printf("\n");

    for (int i = 0; i < Tamanho_tabuleiro; i++) {
        printf("%2d |", i);
        for (int j = 0; j < Tamanho_tabuleiro; j++) {
            printf(" %d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Verifica se o navio pode ser posicionado
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

// Posição do navio no tabuleiro
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

    // Coordenadas iniciais dos navios 
    int linhaH = 1, colunaH = 1;   // Horizontal
    int linhaV = 4, colunaV = 7;   // Vertical
    int linhaD1 = 0, colunaD1 = 6; // Diagonal principal (↘)
    int linhaD2 = 5, colunaD2 = 2; // Diagonal secundária (↙)

    // Posiciona e valida os navios
    if (podeColocarNavio(tabuleiro, linhaH, colunaH, 'H'))
        posicionarNavio(tabuleiro, linhaH, colunaH, 'H');
    else {
        printf("Erro ao posicionar navio horizontal.\n");
        return 1;
    }

    if (podeColocarNavio(tabuleiro, linhaV, colunaV, 'V'))
        posicionarNavio(tabuleiro, linhaV, colunaV, 'V');
    else {
        printf("Erro ao posicionar navio vertical.\n");
        return 1;
    }

    if (podeColocarNavio(tabuleiro, linhaD1, colunaD1, 'D'))
        posicionarNavio(tabuleiro, linhaD1, colunaD1, 'D');
    else {
        printf("Erro ao posicionar navio diagonal ↘.\n");
        return 1;
    }

    if (podeColocarNavio(tabuleiro, linhaD2, colunaD2, 'd'))
        posicionarNavio(tabuleiro, linhaD2, colunaD2, 'd');
    else {
        printf("Erro ao posicionar navio diagonal ↙.\n");
        return 1;
    }

    // Exibir tabuleiro final
    printf("\n------Tabuleiro Batalha Naval------:\n");
    exibirTabuleiro(tabuleiro);
    printf("\n-------Navios posicionados com sucesso!-------\n");

    return 0;
}
