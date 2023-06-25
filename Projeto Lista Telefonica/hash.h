#ifndef HASH_H
#define HASH_H
#define HASH_SIZE 67
#include "indices.h"
#include "arvAvl.h"

// Definição da estrutura da posição na tabela hash, que guarda uma árvore AVL, com endereçamento separado
typedef struct HashNode {
    int ddd;
    AVLNode* raiz;
    struct HashNode* proximo;
} HashNode;

// Definição da estrutura da tabela hash principal
typedef struct HashTable {
    int tamanho;
    HashNode** tabela;
} HashTable;

// Pré-set de todos os DDD brasileiros, para teste
const int ddds_brasileiros[] = {
    11, 12, 13, 14, 15, 16, 17, 18, 19, 21,
    22, 24, 27, 28, 31, 32, 33, 34, 35, 37,
    38, 41, 42, 43, 44, 45, 46, 47, 48, 49,
    51, 53, 54, 55, 61, 62, 63, 64, 65, 66,
    67, 68, 69, 71, 73, 74, 75, 77, 79, 81,
    82, 83, 84, 85, 86, 87, 88, 89, 91, 92,
    93, 94, 95, 96, 97, 98, 99
};

// Constante criada para não precisar utilizar o array na função gerarDDD
const int num_ddds_brasileiros = sizeof(ddds_brasileiros) / sizeof(ddds_brasileiros[0]);
// Função para gerar usuários aleatórios na tabela hash
int gerarDDD();
// Função para criar um novo nó da tabela hash
HashNode* criarHashNode(int ddd,AVLNode* raiz);
// Função para criar uma tabela hash vazia
HashTable* criarHashTable();
//Função para calcular o índice da tabela hash para um determinado DDD
int calcularIndiceHash(int ddd);
// Função de hashing pelo método da multiplicação
int hashMult(int ddd);
// Função de hashing pelo método da dobra
int hashDobra(int ddd);
// Função para inserir um contato na tabela hash
void inserirContato(HashTable* hashTable, const char* numero,int ddd,const char* nome, const char* endereco);
// Função para remover um contato da tabela hash
void removerContato(HashTable* hashTable, const char* numero, int ddd);
// Função para gerar usuários aleatórios na tabela hash
void gerarUsuariosAleatorios(HashTable* hashTable, int quantidade,IndiceInvertido* indice);
// Busca sequencial
AVLNode* buscaSequencial(HashTable* hashTable, int ddd,char* numero);
// Função para encontrar um nó na tabela hash
AVLNode* encontrarHashTable(HashTable* hashTable, const char* numero, int ddd);
// Função para imprimir a tabela hash
void imprimirTabelaHash(HashTable* hashTable);
// Função para gerar um número único
char* gerarNumeroUnico(HashTable* hashTable,int ddd);
// Função para encontrar uma árvore na tabela hash
AVLNode* encontrarArvoreNaTabela(HashTable* hashTable, int ddd);
// Função para imprimir as árvores da tabela hash
void imprimirArvores(HashTable* hashTable, int ordenacao);
// Função para atualizar os contatos na tabela e árvores 
void atualizarContato(HashTable* hashTable, char* numero, int ddd, char* nome, char* endereco,char* numeroAntigo);

#endif