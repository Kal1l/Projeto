#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "indices.h"

// Função para criar uma estrutura de índice invertido vazia
// Retorna: a estrutura de índice invertido vazia
IndiceInvertido* criarIndice(){
    // Aloca memória para a estrutura de índice
    IndiceInvertido* indice=(IndiceInvertido*)malloc(sizeof(IndiceInvertido));
    indice->quantidadeEntradas=0;
    return indice;
}

// Função para adicionar uma entrada ao índice invertido
// Parâmetros: a estrutura de índice invertido e o número de telefone a ser adicionado
void adicionarIndice(IndiceInvertido *indice, char *numeroTelefone) {
    if (indice->quantidadeEntradas < 10000) {
        // Copia o número de telefone para a próxima posição disponível do array
        strcpy(indice->entradas[indice->quantidadeEntradas].numeroTelefone, numeroTelefone);
        indice->quantidadeEntradas++;  // Incrementa o contador de entradas
    } else {
        printf("O índice está cheio. Não é possível adicionar mais entradas.\n");
    }
}

// Função para remover uma entrada do índice invertido
// Parâmetros: a estrutura de índice invertido e o número de telefone a ser removido
void removerIndice(IndiceInvertido *indice, const char *numeroTelefone) {
    int i, j;

    for (i = 0; i < indice->quantidadeEntradas; i++) {
        if (strcmp(indice->entradas[i].numeroTelefone, numeroTelefone) == 0) {
            // Desloca as entradas subsequentes para preencher o espaço vazio da entrada removida
            for (j = i; j < indice->quantidadeEntradas - 1; j++) {
                strcpy(indice->entradas[j].numeroTelefone, indice->entradas[j + 1].numeroTelefone);
            }

            indice->quantidadeEntradas--;  // Decrementa o contador de entradas
            break;
        }
    }
}

// Função para realizar uma busca aproximada no índice invertido
// Parâmetros: a estrutura de índice invertid e a consulta a ser realizada
void BuscaAproximada(IndiceInvertido *indice, char *consulta) {
    int i;
    int encontrado = 0; // Variável para verificar se algum número foi encontrado

    for (i = 0; i < indice->quantidadeEntradas; i++) {
        // Verifica se a consulta está presente no número de telefone
        char *correspondencia = strstr(indice->entradas[i].numeroTelefone, consulta);
        if (correspondencia != NULL) {
            printf("Numero encontrado: %s\n", indice->entradas[i].numeroTelefone);
            encontrado = 1; // Define que um número foi encontrado
        }
    }
    if (!encontrado) {
        printf("Nenhum numero encontrado.\n");
    }
}

// Função para atualizar uma entrada do índice invertido
// Parâmetros: a estrutura de índice invertido, o novo número de telefone e o número de telefone antigo a ser atualizado
void atualizarIndice(IndiceInvertido* indice,char* novoNumeroTelefone, char* numeroTelefoneAntigo) {
    // Remove o número de telefone antigo e adiciona o novo número
    removerIndice(indice, numeroTelefoneAntigo);
    adicionarIndice(indice, novoNumeroTelefone);
}
