#include <stdio.h>

// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.


#define Tamanho_tabuleiro 10     // Tamanho do tabuleiro (10x10)
#define Tamanho_navio 3          // Tamanho dos navios (3 posições)
#define Agua 0                   // Representa água
#define Navio 3                  // Representa parte do navio

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[Tamanho_tabuleiro][Tamanho_tabuleiro]) {
    for (int i = 0; i < Tamanho_tabuleiro; i++) {
        for (int j = 0; j < Tamanho_tabuleiro; j++) {
            tabuleiro[i][j] = Agua;
        }
    }
}

// Função para exibir o tabuleiro no console com letras nas colunas
void exibirTabuleiro(int tabuleiro[Tamanho_tabuleiro][Tamanho_tabuleiro]) {
    printf("\n    ");
    for (int i = 0; i < Tamanho_tabuleiro; i++) {
        printf(" %c ", 'A' + i);  // Letras das colunas
    }
    printf("\n");

    for (int i = 0; i < Tamanho_tabuleiro; i++) {
        printf("%2d |", i);  // Números das linhas
        for (int j = 0; j < Tamanho_tabuleiro; j++) {
            printf(" %d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para verificar se o navio pode ser colocado
int podeColocarNavio(int tabuleiro[Tamanho_tabuleiro][Tamanho_tabuleiro], int linha, int coluna, char orientacao) {
    if (orientacao == 'H') { // Horizontal
        if (coluna + Tamanho_navio > Tamanho_tabuleiro) return 0;
        for (int i = 0; i < Tamanho_navio; i++) {
            if (tabuleiro[linha][coluna + i] == Navio) return 0; // Sobreposição
        }
    } else if (orientacao == 'V') { // Vertical
        if (linha + Tamanho_navio > Tamanho_tabuleiro) return 0;
        for (int i = 0; i < Tamanho_navio; i++) {
            if (tabuleiro[linha + i][coluna] == Navio) return 0;
        }
    }
    return 1;
}

// Função para posicionar o navio
void posicionarNavio(int tabuleiro[Tamanho_tabuleiro][Tamanho_tabuleiro], int linha, int coluna, char orientacao) {
    if (orientacao == 'H') {
        for (int i = 0; i < Tamanho_navio; i++) {
            tabuleiro[linha][coluna + i] = Navio;
        }
    } else if (orientacao == 'V') {
        for (int i = 0; i < Tamanho_navio; i++) {
            tabuleiro[linha + i][coluna] = Navio;
        }
    }
}

int main() {
    int tabuleiro[Tamanho_tabuleiro][Tamanho_tabuleiro];
    int navioH[Tamanho_navio] = {Navio, Navio, Navio}; // Navio horizontal
    int navioV[Tamanho_navio] = {Navio, Navio, Navio}; // Navio vertical

    // Inicializar tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Coordenadas dos navios (
    int linhaH = 2, colunaH = 4; // Coordenadas iniciais do navio horizontal
    int linhaV = 5, colunaV = 1; // Coordenadas iniciais do navio vertical

    // Verifica se os navios podem ser posicionados
    if (podeColocarNavio(tabuleiro, linhaH, colunaH, 'H')) {
        posicionarNavio(tabuleiro, linhaH, colunaH, 'H');
    } else {
        printf("Erro ao posicionar navio horizontal.\n");
        return 1;
    }

    if (podeColocarNavio(tabuleiro, linhaV, colunaV, 'V')) {
        posicionarNavio(tabuleiro, linhaV, colunaV, 'V');
    } else {
        printf("Erro ao posicionar navio vertical.\n");
        return 1;
    }

    // Exibir tabuleiro 
    printf("\n ------Tabuleiro Batalha naval------\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}


