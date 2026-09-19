# Gerador de Cartelas de Bingo

Programa em C que gera cartelas de bingo seguindo as regras oficiais do jogo: colunas B-I-N-G-O, faixas de valores por coluna, espaço livre central e números sem repetição dentro da mesma coluna.

## Sobre o projeto

Exercício da disciplina de Linguagem C (curso de Análise e Desenvolvimento de Sistemas), com foco em vetores, matrizes, funções, enumerações e structs.

## Regras implementadas

- Cartela 5x5, uma coluna para cada letra do BINGO
- Faixas de valores: B (1–15), I (16–30), N (31–45), G (46–60), O (61–75)
- Espaço livre no centro (linha 3, coluna 3)
- Nenhum número se repete dentro da mesma coluna

## Estrutura do código

- `enum Coluna` — representa o valor mínimo de cada coluna
- `struct Cartela` — armazena a matriz 5x5 de uma cartela
- Funções: `gerarNumero`, `numeroExiste`, `ordenarColuna`, `gerarCartela`, `cartelasIguais`, `gerarCartelasUnicas`, `imprimirCartela`

## Desafios extras implementados

1. Quantidade de cartelas definida pelo usuário
2. Múltiplas cartelas armazenadas (vetor de structs `Cartela`)
3. Uso de `struct` para representar a cartela
4. Números de cada coluna ordenados em ordem crescente
5. Garantia de que nenhuma cartela gerada é repetida

## Como compilar e executar

```bash
gcc -o bingo bingo.c
./bingo
```

O programa pergunta quantas cartelas você deseja gerar.

## Exemplo de saída

```
 B    I    N    G    O
 5   18   35   50   63
10   21   40   54   66
13   24    X   58   70
14   27   42   59   72
15   30   45   60   75
```

## Autor

Matheus Felipe
