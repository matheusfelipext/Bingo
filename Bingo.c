/*
 * Gerador de Cartelas de Bingo
 * Exercicio: vetores, matrizes, strings, funcoes e enumeracoes
 * Repositorio: https://github.com/matheusfelipext/exercicios_c
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LINHAS 5
#define COLUNAS 5
#define TAMANHO_FAIXA 15   /* cada coluna cobre 15 numeros (ex.: B = 1 a 15) */

/* Enum representando o valor MINIMO de cada coluna do BINGO */
typedef enum {
    B = 1,
    I = 16,
    N = 31,
    G = 46,
    O = 61
} Coluna;

/* Struct que representa uma cartela (Desafio 3) */
typedef struct {
    int numeros[LINHAS][COLUNAS];
} Cartela;

/* ---------- Prototipos ---------- */
int  gerarNumero(int minimo, int maximo);
int  numeroExiste(int coluna[LINHAS], int quantidade, int numero);
void ordenarColuna(int coluna[LINHAS], int quantidade);
void gerarCartela(Cartela *cartela);
void imprimirCartela(Cartela cartela);
int  cartelasIguais(Cartela a, Cartela b);
void gerarCartelasUnicas(Cartela cartelas[], int quantidade);

int main(void) {
    srand((unsigned int) time(NULL));

    int quantidade;
    printf("=== Gerador de Cartelas de Bingo ===\n");
    printf("Quantas cartelas deseja gerar? ");
    if (scanf("%d", &quantidade) != 1 || quantidade <= 0) {
        printf("Quantidade invalida.\n");
        return 1;
    }

    /* Desafio 1: quantidade informada pelo usuario   */
    /* Desafio 2/3: vetor de structs Cartela (cada uma guarda sua matriz 5x5) */
    Cartela *cartelas = malloc((size_t) quantidade * sizeof(Cartela));
    if (cartelas == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    gerarCartelasUnicas(cartelas, quantidade); /* Desafio 5: sem cartelas repetidas */

    for (int i = 0; i < quantidade; i++) {
        printf("\nCartela %d\n", i + 1);
        imprimirCartela(cartelas[i]);
    }

    free(cartelas);
    return 0;
}

/* Gera um numero aleatorio no intervalo [minimo, maximo] */
int gerarNumero(int minimo, int maximo) {
    return (rand() % (maximo - minimo + 1)) + minimo;
}

/* Verifica se "numero" ja foi sorteado para a coluna que esta sendo montada */
int numeroExiste(int coluna[LINHAS], int quantidade, int numero) {
    for (int i = 0; i < quantidade; i++) {
        if (coluna[i] == numero) {
            return 1;
        }
    }
    return 0;
}

/* Desafio 4: ordena os numeros de uma coluna em ordem crescente (bubble sort) */
void ordenarColuna(int coluna[LINHAS], int quantidade) {
    for (int i = 0; i < quantidade - 1; i++) {
        for (int j = 0; j < quantidade - 1 - i; j++) {
            if (coluna[j] > coluna[j + 1]) {
                int aux = coluna[j];
                coluna[j] = coluna[j + 1];
                coluna[j + 1] = aux;
            }
        }
    }
}

/* Monta uma cartela completa respeitando faixas, sem repeticao e com o espaco livre central */
void gerarCartela(Cartela *cartela) {
    int baseColuna[COLUNAS] = {B, I, N, G, O};

    for (int col = 0; col < COLUNAS; col++) {
        int minimo = baseColuna[col];
        int maximo = baseColuna[col] + TAMANHO_FAIXA - 1;

        int numerosColuna[LINHAS];
        int total = 0;

        for (int linha = 0; linha < LINHAS; linha++) {
            if (linha == 2 && col == 2) {
                continue; /* linha 3, coluna 3 (1-indexado) = espaco livre */
            }

            int numero;
            do {
                numero = gerarNumero(minimo, maximo);
            } while (numeroExiste(numerosColuna, total, numero));

            numerosColuna[total++] = numero;
        }

        ordenarColuna(numerosColuna, total);

        int indice = 0;
        for (int linha = 0; linha < LINHAS; linha++) {
            if (linha == 2 && col == 2) {
                cartela->numeros[linha][col] = 0; /* espaco livre */
            } else {
                cartela->numeros[linha][col] = numerosColuna[indice++];
            }
        }
    }
}

/* Compara duas cartelas numero a numero */
int cartelasIguais(Cartela a, Cartela b) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (a.numeros[i][j] != b.numeros[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

/* Desafio 5: gera "quantidade" cartelas garantindo que nenhuma se repita */
void gerarCartelasUnicas(Cartela cartelas[], int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        int repetida;
        do {
            gerarCartela(&cartelas[i]);
            repetida = 0;
            for (int j = 0; j < i; j++) {
                if (cartelasIguais(cartelas[i], cartelas[j])) {
                    repetida = 1;
                    break;
                }
            }
        } while (repetida);
    }
}

/* Imprime a cartela com cabecalho B I N G O e "X" no espaco livre */
void imprimirCartela(Cartela cartela) {
    printf(" B    I    N    G    O\n");
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (cartela.numeros[i][j] == 0) {
                printf(" X   ");
            } else {
                printf("%2d   ", cartela.numeros[i][j]);
            }
        }
        printf("\n");
    }
}
