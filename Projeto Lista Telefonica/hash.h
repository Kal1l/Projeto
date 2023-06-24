#ifndef HASH_H
#define HASH_H
#define HASH_SIZE 67
#include "indices.h"
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

const int ddds_brasileiros[] = {
    11, 12, 13, 14, 15, 16, 17, 18, 19, 21,
    22, 24, 27, 28, 31, 32, 33, 34, 35, 37,
    38, 41, 42, 43, 44, 45, 46, 47, 48, 49,
    51, 53, 54, 55, 61, 62, 63, 64, 65, 66,
    67, 68, 69, 71, 73, 74, 75, 77, 79, 81,
    82, 83, 84, 85, 86, 87, 88, 89, 91, 92,
    93, 94, 95, 96, 97, 98, 99
};

const int num_ddds_brasileiros = sizeof(ddds_brasileiros) / sizeof(ddds_brasileiros[0]);

int gerarDDD();
HashNode* criarHashNode(int ddd,AVLNode* raiz);
HashTable* criarHashTable();
int calcularIndiceHash(int ddd);
void inserirContato(HashTable* hashTable, const char* numero,int ddd,const char* nome, const char* endereco);
void removerContato(HashTable* hashTable, const char* numero, int ddd);
void gerarUsuariosAleatorios(HashTable* hashTable, int quantidade,IndiceInvertido* indice);
AVLNode* encontrarHashTable(HashTable* hashTable, const char* numero, int ddd);
void imprimirTabelaHash(HashTable* hashTable);
char* gerarNumeroUnico(HashTable* hashTable,int ddd);
AVLNode* encontrarArvoreNaTabela(HashTable* hashTable, int ddd);
void imprimirArvores(HashTable* hashTable, int ordenacao);
void atualizarContato(HashTable* hashTable, char* numero, int ddd, char* nome, char* endereco,char* numeroAntigo);

#endif