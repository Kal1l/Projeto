#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arvAvl.h"
#include "hash.h"

HashNode* criarHashNode(int ddd,AVLNode* raiz){
    HashNode* novoNo=(HashNode*)malloc(sizeof(HashNode));
    novoNo->ddd=ddd;
    novoNo->raiz=raiz;
    novoNo->proximo=NULL;
    return novoNo;
}
HashTable* criarHashTable() {
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    hashTable->tamanho=HASH_SIZE;
    hashTable->tabela = (HashNode**)calloc(HASH_SIZE , sizeof(HashNode*));
    return hashTable;
}
int calcularIndiceHash(int ddd) {
    return ddd  % HASH_SIZE;
}
// Função de hashing pelo método da multiplicação
int hashMultiplication(int ddd) {
    double A = 0.6180339887; // Constante de multiplicação (valor irracional)
    double val = ddd * A;
    val -= (int)val; // Extrair parte fracionária
    int hash = (int)(HASH_SIZE * val); // Multiplicar pela tabela hash size
    return hash;
}
// Função de hashing pelo método da dobra
int hashFolding(int ddd) {
    int hash = 0; 
    // Converter a chave em uma sequência de dígitos
    char dddStr[20];
    sprintf(dddStr, "%d", ddd);
    int len = strlen(dddStr);
    int halfLen = len / 2;
    // Somar os dígitos em pares (da esquerda para a direita)
    for (int i = 0; i < halfLen; i++) {
        int pairSum = (dddStr[i] - '0') + (dddStr[len - i - 1] - '0');
        hash += pairSum;
    }
    // Se a chave possuir um número ímpar de dígitos, somar o dígito do meio
    if (len % 2 != 0) {
        hash += dddStr[halfLen] - '0';
    }
    // Aplicar o módulo para obter o valor dentro do intervalo da tabela hash
    hash %= HASH_SIZE;
    return hash;
}
// Função para inserir um valor na tabela hash
void inserirContato(HashTable* hashTable, const char* numero,int ddd,const char* nome, const char* endereco) {
    int indice = calcularIndiceHash(ddd);
    // Verificar se o índice está vazio
    if(hashTable->tabela[indice]==NULL){
        AVLNode* raiz=inserir(NULL,numero,nome,endereco);
        hashTable->tabela[indice]=criarHashNode(ddd,raiz);
    }else{
        HashNode* atual=hashTable->tabela[indice];
        // Percorrer a lista encadeada até encontrar um nó com o mesmo DDD
        while(atual->proximo!=NULL && atual->ddd!=ddd)
            atual=atual->proximo;

         // Caso já exista um nó com o mesmo DDD
        if(atual->ddd==ddd)
            atual->raiz=inserir(atual->raiz,numero,nome,endereco);
        else{
            AVLNode* raiz=inserir(NULL,numero,nome,endereco);
            HashNode* novoNo=criarHashNode(ddd,raiz);
            atual->proximo=novoNo;
        }
    }
    printf("OK!\n");
}
// Função para deletar um valor da tabela hash
void removerContato(HashTable* hashTable, const char* numero, int ddd) {
    int indice = calcularIndiceHash(ddd);
    
    // Verificar se o índice está vazio
    if (hashTable->tabela[indice] == NULL)
        return;
    else {
        HashNode* atual = hashTable->tabela[indice];
        HashNode* anterior = NULL;
        
        // Percorrer a lista encadeada até encontrar um nó com o mesmo DDD
        while (atual != NULL) {
            if (atual->ddd == ddd) {
                AVLNode* arvoreAntes = encontrarArvoreNaTabela(hashTable, ddd);
                atual->raiz = removerNodo(atual->raiz, numero);
                AVLNode* arvoreDepois = encontrarArvoreNaTabela(hashTable, ddd);
                
                // Exibir a altura da árvore antes e depois da remoção
                printf("Altura da arvore antes da remocao: %d\n", altura(arvoreAntes));
                printf("Altura da arvore depois da remocao: %d\n", altura(arvoreDepois));
                
                // Se a árvore AVL estiver vazia, remover o nó da lista
                if (atual->raiz == NULL) {
                    if (anterior == NULL) {
                        hashTable->tabela[indice] = atual->proximo;
                    } else {
                        anterior->proximo = atual->proximo;
                        free(atual);
                    }
                }
                return;
            }
            anterior = atual;
            atual = atual->proximo;
        }
    }
}
void atualizarContato(HashTable* hashTable, char* numero, int ddd, char* nome, char* endereco,char* numeroAntigo) {
    removerContato(hashTable,numeroAntigo,ddd);
    inserirContato(hashTable,numero,ddd,nome,endereco);
}

// Busca sequencial
AVLNode* sequentialSearch(HashTable* hashTable, int ddd,char* numero) {
    int indice = calcularIndiceHash(ddd);

    // Verificar se o índice está vazio
    if (hashTable->tabela[indice] == NULL)
        return NULL;
    else {
        HashNode* atual = hashTable->tabela[indice];

        // Percorrer a lista encadeada até encontrar um nó com o mesmo DDD
        while (atual != NULL) {
            if (atual->ddd == ddd) {
                AVLNode* result = encontrarNodo(atual->raiz,numero);
                return result;
            }
            atual = atual->proximo;
        }
    }

    return NULL;
}
AVLNode* encontrarHashTable(HashTable* hashTable, const char* numero, int ddd) {
    int indice = calcularIndiceHash(ddd);

    // Verificar se o índice está vazio
    if (hashTable->tabela[indice] == NULL)
        return NULL;
    else {
        HashNode* atual=hashTable->tabela[indice];
        // Percorrer a lista encadeada até encontrar um nó com o mesmo DDD
        while (atual != NULL) {
            if (atual->ddd == ddd) {
                AVLNode* result = encontrarNodo(atual->raiz, numero);
                if (result != NULL)
                    return result;
            }
            atual = atual->proximo;
        }
    }
    return NULL;
}
void imprimirTabelaHash(HashTable* hashTable) {
    printf("Tabela Hash:\n");

    for (int i = 0; i < HASH_SIZE; i++) {
        printf("Posicao %d:\n", i);

        if (hashTable->tabela[i] == NULL) {
            printf("Usuarios nao encontrados.\n\n");
        } else {
            HashNode* atual = hashTable->tabela[i];

            while (atual != NULL) {
                printf("DDD: %d\n", atual->ddd);
                if (atual->raiz == NULL) {
                    printf("Usuarios nao encontrados.\n");
                } else {
                    imprimirEmOrdem(atual->raiz);
                }
                atual = atual->proximo;
                printf("\n");
            }
        }
    }
}
char* gerarNumeroUnico(HashTable* hashTable,int ddd){
    char* numero = malloc(10 * sizeof(char));
    numero[0]='9';
    do{
         for (int i = 1; i < 9; i++) {
            numero[i] = '0' + rand() % 10;
        }
        numero[9]='\0';
    }while(encontrarHashTable(hashTable,numero,ddd));
    return numero;
}
AVLNode* encontrarArvoreNaTabela(HashTable* hashTable, int ddd) {
    int indice = calcularIndiceHash(ddd);

    // Verificar se o índice está vazio
    if (hashTable->tabela[indice] == NULL)
        return NULL;
    else {
        HashNode* atual = hashTable->tabela[indice];
        
        // Percorrer a lista encadeada até encontrar o nó com o mesmo DDD
        while (atual != NULL) {
            if (atual->ddd == ddd)
                return atual->raiz;
            
            atual = atual->proximo;
        }
    }
    
    return NULL;
}
void imprimirArvores(HashTable* hashTable, int ordenacao) {
    printf("Lista de arvores:\n");

    // Vetor para armazenar os DDDs presentes na tabela hash
    int ddds[HASH_SIZE];
    int count = 0;

    // Percorrer a tabela hash e preencher o vetor de DDDs
    for (int i = 0; i < HASH_SIZE; i++) {
        if (hashTable->tabela[i] != NULL) {
            HashNode* atual = hashTable->tabela[i];
            ddds[count] = atual->ddd;
            count++;
        }
    }

    // Ordenar os DDDs em ordem crescente
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (ddds[j] < ddds[i]) {
                int temp = ddds[i];
                ddds[i] = ddds[j];
                ddds[j] = temp;
            }
        }
    }

    // Percorrer os DDDs em ordem crescente
    for (int i = 0; i < count; i++) {
        int ddd = ddds[i];
        AVLNode* hashNode = encontrarArvoreNaTabela(hashTable, ddd);

        if (hashNode != NULL) {
            printf("DDD: %d\n", ddd);  // Exibir o DDD da árvore

            AVLNode* raiz = hashNode;

            if (ordenacao == 1) {
                printf("Ordenacao por numero de telefone (Em-ordem):\n");
                imprimirEmOrdem(raiz);
            } else if (ordenacao == 2) {
                printf("Ordenacao por nome de usuario:\n");
                imprimirPorNomeOrdenado(raiz);
            }
            printf("\n");
        }
    }
}
