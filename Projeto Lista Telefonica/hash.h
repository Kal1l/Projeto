#ifndef HASH_H
#define HASH_H
#define HASH_SIZE 67
#include "indices.h"
#include "arvAvl.h"

// Definição da estrutura da posição na tabela hash, que guarda uma árvore AVL, com endereçamento separado
typedef struct HashNo {
    int ddd;
    AVLNo* raiz;
    struct HashNo* proximo;
} HashNo;

// Definição da estrutura da tabela hash principal
typedef struct TabelaHash {
    int tamanho;
    HashNo** tabela;
} TabelaHash;

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
HashNo* criarHashNo(int ddd,AVLNo* raiz);
// Função para criar uma tabela hash vazia
TabelaHash* criarTabelaHash();
//Função para calcular o índice da tabela hash para um determinado DDD
int calcularIndiceHash(int ddd);
// Função de hashing pelo método da multiplicação
int hashMult(int ddd);
// Função de hashing pelo método da dobra
int hashDobra(int ddd);
// Função para inserir um contato na tabela hash
void inserirContato(TabelaHash* tabelaHash, const char* numero,int ddd,const char* nome, const char* endereco);
// Função para remover um contato da tabela hash
void removerContato(TabelaHash* tabelaHash, const char* numero, int ddd);
// Função para gerar usuários aleatórios na tabela hash
void gerarUsuariosAleatorios(TabelaHash* tabelaHash, int quantidade,IndiceInvertido* indice);
// Busca sequencial
AVLNo* buscaSequencial(TabelaHash* tabelaHash, int ddd,char* numero);
// Função para encontrar um nó na tabela hash
AVLNo* encontrarContato(TabelaHash* tabelaHash, const char* numero, int ddd);
// Função para imprimir a tabela hash
void imprimirTabelaHash(TabelaHash* tabelaHash);
// Função para gerar um número único
char* gerarNumeroUnico(TabelaHash* tabelaHash,int ddd);
// Função para encontrar uma árvore na tabela hash
AVLNo* encontrarArvoreNaTabela(TabelaHash* tabelaHash, int ddd);
// Função para imprimir as árvores da tabela hash
void imprimirArvores(TabelaHash* tabelaHash, int ordenacao);
// Função para atualizar os contatos na tabela e árvores 
void atualizarContato(TabelaHash* tabelaHash, char* numero, int ddd, char* nome, char* endereco,char* numeroAntigo);

#endif