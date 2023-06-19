#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "avlT.h"

typedef struct No {
    char* numero;
    char* nome;
    char* endereco;
    int alt;
    struct No* esq;
    struct No* dir;
} No;

int char_nao_num(char* string) {
    int i;
    for (i = 0; string[i] != '\0'; i++) {
        if (!isdigit(string[i])) {
            return 1;
        }
    }
    return 0;
}

int maximo(int a, int b) {
    return (a > b) ? a : b;
}

int altura(struct No* no) {
    if (no == NULL) {
        return 0;
    }
    return no->alt;
}

int fator_balanceamento(struct No* no) {
    if (no == NULL) {
        return 0;
    }
    return altura(no->esq) - altura(no->dir);
}

avlT* cria_avlT() {
    avlT* raiz = (avlT*)malloc(sizeof(avlT));
    if (raiz != NULL)
        *raiz = NULL;
    return raiz;
}

struct No* criar_no(char* numero, char* nome, char* endereco) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->numero = strdup(numero);
    novoNo->nome = strdup(nome);
    novoNo->endereco = strdup(endereco);
    novoNo->alt = 1;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    return novoNo;
}

struct No* rotacao_direita(struct No* y) {
    struct No* x = y->esq;
    struct No* T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->alt = maximo(altura(y->esq), altura(y->dir)) + 1;
    x->alt = maximo(altura(x->esq), altura(x->dir)) + 1;

    return x;
}

struct No* rotacao_esquerda(struct No* x) {
    struct No* y = x->dir;
    struct No* T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->alt = maximo(altura(x->esq), altura(x->dir)) + 1;
    y->alt = maximo(altura(y->esq), altura(y->dir)) + 1;

    return y;
}

void rotacao_dupla_direita(avlT* A) {
    (*A)->esq = rotacao_esquerda((*A)->esq);
    (*A) = rotacao_direita(*A);
}

void rotacao_dupla_esquerda(avlT* A) {
    (*A)->dir = rotacao_direita((*A)->dir);
    (*A) = rotacao_esquerda(*A);
}

int inserir_no(avlT* raiz, char* numero, char* nome, char* endereco) {
    if (char_nao_num(numero)) {
        return 0;
    }

    if (*raiz == NULL) {
        *raiz = criar_no(numero, nome, endereco);
        return 1;
    }

    if (strcmp(numero, (*raiz)->numero) < 0) {
        if (!inserir_no(&(*raiz)->esq, numero, nome, endereco)) {
            return 0;
        }
    } else if (strcmp(numero, (*raiz)->numero) > 0) {
        if (!inserir_no(&(*raiz)->dir, numero, nome, endereco)) {
            return 0;
        }
    } else {
        return 0; // Não permite inserir elementos com chaves duplicadas
    }

    (*raiz)->alt = 1 + maximo(altura((*raiz)->esq), altura((*raiz)->dir));

    int fb = fator_balanceamento(*raiz);

    if (fb > 1 && strcmp(numero, (*raiz)->esq->numero) < 0) {
        *raiz = rotacao_direita(*raiz);
    }

    if (fb < -1 && strcmp(numero, (*raiz)->dir->numero) > 0) {
        *raiz = rotacao_esquerda(*raiz);
    }

    if (fb > 1 && strcmp(numero, (*raiz)->esq->numero) > 0) {
        rotacao_dupla_direita(raiz);
    }

    if (fb < -1 && strcmp(numero, (*raiz)->dir->numero) < 0) {
        rotacao_dupla_esquerda(raiz);
    }

    return 1;
}

struct No* busca_no(struct No* raiz, char* numero) {
    if (raiz == NULL || strcmp(raiz->numero, numero) == 0) {
        return raiz;
    }

    if (strcmp(raiz->numero, numero) < 0) {
        return busca_no(raiz->dir, numero);
    }

    return busca_no(raiz->esq, numero);
}

struct No* busca_menor_no(struct No* raiz) {
    struct No* atual = raiz;
    while (atual->esq != NULL) {
        atual = atual->esq;
    }
    return atual;
}

struct No* remover_no(struct No* raiz, char* numero) {
    if (raiz == NULL) {
        return raiz;
    }

    if (strcmp(numero, raiz->numero) < 0) {
        raiz->esq = remover_no(raiz->esq, numero);
    } else if (strcmp(numero, raiz->numero) > 0) {
        raiz->dir = remover_no(raiz->dir, numero);
    } else {
        if ((raiz->esq == NULL) || (raiz->dir == NULL)) {
            struct No* temp = raiz->esq ? raiz->esq : raiz->dir;

            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }
            free(temp);
        } else {
            struct No* temp = busca_menor_no(raiz->dir);
            raiz->numero = temp->numero;
            raiz->nome = temp->nome;
            raiz->endereco = temp->endereco;
            raiz->dir = remover_no(raiz->dir, temp->numero);
        }
    }

    if (raiz == NULL) {
        return raiz;
    }

    raiz->alt = 1 + maximo(altura(raiz->esq), altura(raiz->dir));

    int fb = fator_balanceamento(raiz);

    if (fb > 1 && fator_balanceamento(raiz->esq) >= 0) {
        raiz = rotacao_direita(raiz);
    }

    if (fb > 1 && fator_balanceamento(raiz->esq) < 0) {
        rotacao_dupla_direita(&raiz);
    }

    if (fb < -1 && fator_balanceamento(raiz->dir) <= 0) {
        raiz = rotacao_esquerda(raiz);
    }

    if (fb < -1 && fator_balanceamento(raiz->dir) > 0) {
        rotacao_dupla_esquerda(&raiz);
    }

    return raiz;
}

void imprimir_preOrdem(struct No* raiz) {
    if (raiz != NULL) {
        printf("Número: %s, Nome: %s, Endereço: %s\n", raiz->numero, raiz->nome, raiz->endereco);
        imprimir_preOrdem(raiz->esq);
        imprimir_preOrdem(raiz->dir);
    }
}

void imprimir_emOrdem(struct No* raiz) {
    if (raiz != NULL) {
        imprimir_emOrdem(raiz->esq);
        printf("Número: %s, Nome: %s, Endereço: %s\n", raiz->numero, raiz->nome, raiz->endereco);
        imprimir_emOrdem(raiz->dir);
    }
}

void imprimir_posOrdem(struct No* raiz) {
    if (raiz != NULL) {
        imprimir_posOrdem(raiz->esq);
        imprimir_posOrdem(raiz->dir);
        printf("Número: %s, Nome: %s, Endereço: %s\n", raiz->numero, raiz->nome, raiz->endereco);
    }
}

void liberar_avlT(struct No* raiz) {
    if (raiz != NULL) {
        liberar_avlT(raiz->esq);
        liberar_avlT(raiz->dir);
        free(raiz->numero);
        free(raiz->nome);
        free(raiz->endereco);
        free(raiz);
    }
}
