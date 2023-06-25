#ifndef DUPLICATA_H
#define DUPLICATA_H

#define MAX_SIZE 20000

// Definição da estrutura de um nó da árvore Duplicata
typedef struct Registro {
    char nome[50];
    char numero[20];
    struct Registro* prox;
} Registro;

// Definição da estrutura da tabela Hash Duplicata
typedef struct HashDup {
    Registro* tabela[MAX_SIZE];
} HashDup;

// Função de hashing para tabela duplicata
int hash(char* key);
// Inicializa uma nova tabela duplicata
HashDup* criarHashDup();
// insere um novo elemento direto na tabela
int insereHashDup(HashDup* hashDup, char* nome, char* numero);
// remove um novo elemento direto da tabela
void removerHashDup(HashDup* hashDup, char* nome, char* numero);
// atualiza um elemento direto na tabela
int atualizarHashDup(HashDup* hashDup, char* nomeAntigo, char* numeroAntigo, char* novoNome, char* novoNumero);

#endif