#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

struct arvore{
    int ddd;
    char regiao[50];
    struct arvore *prox;
};

typedef struct hash Hash;

Hash* criaHash(int tamanho);
void liberaHash(Hash* ha);
int valorString(char* str);
int insereHash_EncSep(Hash* ha, struct arvore ar);
int buscaHash_EncSep(Hash* ha, int mat);
void imprimeHash(Hash* ha);

#endif /* HASH_H_INCLUDED */