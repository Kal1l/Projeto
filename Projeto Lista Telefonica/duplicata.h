#ifndef DUPLICATA_H
#define DUPLICATA_H
typedef struct Registro {
    char nome[50];
    char numero[20];
    struct Registro* prox;
} Registro;

typedef struct HashDup {
    Registro* tabela[20000];
} HashDup;
int hash(char* key);
HashDup* criarHashDup();
int insereHashDup(HashDup* hashDup, char* nome, char* numero);
void removerHashDup(HashDup* hashDup, char* nome, char* numero);
int atualizarHashDup(HashDup* hashDup, char* nomeAntigo, char* numeroAntigo, char* novoNome, char* novoNumero);
#endif