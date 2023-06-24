#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "duplicata.h"

// Função hash
int hash(char* key) {
    int hash = 0;
    int i = 0;
    while (key[i] != '\0') {
        hash += key[i];
        i++;
    }
    return hash % MAX_SIZE;
}

HashDup* criarHashDup() {
    HashDup* hashDup = (HashDup*)malloc(sizeof(HashDup));
    for(int i=0;i<MAX_SIZE;i++){
        hashDup->tabela[i]=NULL;
    }
    return hashDup;
}

int insereHashDup(HashDup* hashDup, char* nome, char* numero) {
    int posNome = hash(nome);
    int posNumero = hash(numero);

    // Verificar duplicatas pelo nome
    Registro* atualNome = hashDup->tabela[posNome];
    while (atualNome != NULL) {
        if (strcmp(atualNome->nome, nome) == 0) {
            printf("Registro Duplicado (nome): %s\n", nome);
            return 0;
        }
        atualNome = atualNome->prox;
    }

    // Verificar duplicatas pelo número de telefone
    Registro* atualNum = hashDup->tabela[posNumero];
    while (atualNum != NULL) {
        if (strcmp(atualNum->numero, numero) == 0) {
            printf("Registro Duplicado (numero): %s\n", numero);
            return 0;
        }
        atualNum = atualNum->prox;
    }

    // Se não houver duplicatas, inserir o novo registro pelo nome
    Registro* novoRegistroNome = (Registro*)malloc(sizeof(Registro));
    strncpy(novoRegistroNome->nome, nome, sizeof(novoRegistroNome->nome));
    novoRegistroNome->prox = NULL;

    if (hashDup->tabela[posNome] == NULL) {
        hashDup->tabela[posNome] = novoRegistroNome;
    } else {
        Registro* atual = hashDup->tabela[posNome];
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novoRegistroNome;
    }

    // Inserir o novo registro pelo número de telefone
    Registro* novoRegistroNum = (Registro*)malloc(sizeof(Registro));
    strncpy(novoRegistroNum->nome, nome, sizeof(novoRegistroNum->nome));
    strncpy(novoRegistroNum->numero, numero, sizeof(novoRegistroNum->numero));
    novoRegistroNum->prox = NULL;

    if (hashDup->tabela[posNumero] == NULL) {
        hashDup->tabela[posNumero] = novoRegistroNum;
    } else {
        Registro* atual = hashDup->tabela[posNumero];
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novoRegistroNum;
    }

    return 1;
}

// Função para remover um elemento da tabela hash
void removerHashDup(HashDup* hashDup, char* nome, char* numero) {
    int posNome = hash(nome);
    int posNumero = hash(numero);

    // Remover pelo nome
    Registro* atualNome = hashDup->tabela[posNome];
    Registro* anteriorNome = NULL;

    while (atualNome != NULL) {
        if (strcmp(atualNome->nome, nome) == 0) {
            if (anteriorNome == NULL) {
                // É o primeiro elemento da lista encadeada
                hashDup->tabela[posNome] = atualNome->prox;
            } else {
                // É um elemento no meio ou final da lista encadeada
                anteriorNome->prox = atualNome->prox;
            }

            printf("Registro removido (nome): %s\n", nome);
            free(atualNome);
            break;
        }

        anteriorNome = atualNome;
        atualNome = atualNome->prox;
    }

    // Remover pelo número de telefone
    Registro* atualNum = hashDup->tabela[posNumero];
    Registro* anteriorNum = NULL;

    while (atualNum != NULL) {
        if (strcmp(atualNum->numero, numero) == 0) {
            if (anteriorNum == NULL) {
                // É o primeiro elemento da lista encadeada
                hashDup->tabela[posNumero] = atualNum->prox;
            } else {
                // É um elemento no meio ou final da lista encadeada
                anteriorNum->prox = atualNum->prox;
            }

            printf("Registro removido(numero): %s\n", numero);
            free(atualNum);
            break;
        }

        anteriorNum = atualNum;
        atualNum = atualNum->prox;
    }
}
int atualizarHashDup(HashDup* hashDup, char* nomeAntigo, char* numeroAntigo, char* novoNome, char* novoNumero) {
    removerHashDup(hashDup,nomeAntigo,numeroAntigo);
    if(insereHashDup(hashDup,novoNome,novoNumero)==1){
        return 1;
    }
    return 0;
}
