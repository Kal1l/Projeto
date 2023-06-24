#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "indices.h"

IndiceInvertido* criarIndice(){
    IndiceInvertido* indice=(IndiceInvertido*)malloc(sizeof(IndiceInvertido));
    indice->quantidadeEntradas=0;
    return indice;
}
void adicionarIndice(IndiceInvertido *indice, char *numeroTelefone) {
    if (indice->quantidadeEntradas < 10000) {
        // Copia o número de telefone para a próxima posição disponível do array
        strcpy(indice->entradas[indice->quantidadeEntradas].numeroTelefone, numeroTelefone);
        indice->quantidadeEntradas++;  // Incrementa o contador de entradas
    } else {
        printf("O índice está cheio. Não é possível adicionar mais entradas.\n");
    }
}
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
void BuscaAproximada(IndiceInvertido *indice, char *consulta) {
    int i;
    int encontrado = 0; // Variável para verificar se algum número foi encontrado

    for (i = 0; i < indice->quantidadeEntradas; i++) {
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