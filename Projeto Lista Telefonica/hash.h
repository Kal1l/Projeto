#ifndef HASH_H
#define HASH_H
#define HASH_SIZE 67
#include "arvAvl.h"

typedef struct HashNode {
    int ddd;
    AVLNode* raiz;
    struct HashNode* proximo;
} HashNode;

typedef struct HashTable {
    int tamanho;
    HashNode** tabela;
} HashTable;

HashNode* criarHashNode(int ddd,AVLNode* raiz);
HashTable* criarHashTable();
int calcularIndiceHash(int ddd);
void inserirContato(HashTable* hashTable, const char* numero,int ddd,const char* nome, const char* endereco);
void removerContato(HashTable* hashTable, const char* numero, int ddd);
AVLNode* encontrarHashTable(HashTable* hashTable, const char* numero, int ddd);
void imprimirTabelaHash(HashTable* hashTable);
char* gerarNumeroUnico(HashTable* hashTable,int ddd);
AVLNode* encontrarArvoreNaTabela(HashTable* hashTable, int ddd);
void imprimirArvores(HashTable* hashTable, int ordenacao);
#endif