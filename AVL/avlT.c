#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"avlT.h"
/*TODO LIST:
    -COLOCAR NA MAIN, UMA CHECAGEM SE A STRING DO NÚMERO POSSUI 12 NÚMEROS E UTILIZAR
    A FUNÇÃO DE VERIFICAÇÃO PRA VER SE SÃO TODOS NÚMEROS*/
typedef struct No{
    char* numero;
    char* nome;
    char* endereco;
    int alt;
    struct No *esq;
    struct No *dir;
}No;
//Verificação se a string não possui nenhuma letra
int char_nao_num(char* string){
    int i;
    for(i=0;string[i]!='\0';i++){
        if(!isdigit(string[i])){
            return 1;
        }
    }
    return 0;
}
//Retorna o maior entre dois números
int maximo(int a, int b) {
    return (a > b) ? a : b;
}
//Retorna altura da árvore
int altura(No* no) {
    if (no == NULL) {
        return 0;
    }
    return no->alt;
}
//Retorna o fator de balanceamento da árvore
int fator_balanceamento(No* no) {
    if (no == NULL) {
        return 0;
    }
    return altura(no->esq) - altura(no->dir);
}
//Cria uma nova árvore AVL
avlT* criar_AVL(){
    avlT* raiz = (avlT*)malloc(sizeof(avlT));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}
//Cria um novo nó na árvore com as informações do contato
No* criar_no(char* numero, char* nome, char* endereco) {
    No* novoNo=(No*)malloc(sizeof(No));
    novoNo->numero = strdup(numero);
    novoNo->nome = strdup(nome);
    novoNo->endereco = strdup(endereco);
    novoNo->alt=1;
    novoNo->esq=NULL;
    novoNo->dir=NULL;
    return novoNo;
}
//Rotação Simples à Direita
No* rotacao_direita(No* y) {
    No* x = y->esq;
    No* T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->alt = maximo(altura(y->esq), altura(y->dir)) + 1;
    x->alt = maximo(altura(x->esq), altura(x->dir)) + 1;

    return x;
}
//Rotação Simples à Esquerda
No* rotacao_esquerda(No* x) {
    No* y = x->dir;
    No* T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->alt = maximo(altura(x->esq), altura(x->dir)) + 1;
    y->alt = maximo(altura(y->esq), altura(y->dir)) + 1;

    return y;
}
//Rotação Dupla à Direita
void rotacao_dupla_direita(avlT* A){
    rotacao_esquerda(&(*A)->esq);
    rotacao_direita(A);
}
//Rotação Dupla à Esquerda
void rotacao_dupla_esquerda(avlT* A){
    rotacao_direita(&(*A)->dir);
    rotacao_esquerda(A);
}
No* insere_no(No* raiz, char* numero, char* nome, char* endereco) {
    if (raiz == NULL) {
        return criar_no(numero, nome, endereco);
    }
    if (strcmp(numero, raiz->numero) < 0) {
        raiz->esq = insere_no(raiz->esq, numero, nome, endereco);
    } else if (strcmp(numero, raiz->numero) > 0) {
        raiz->dir = insere_no(raiz->dir, numero, nome, endereco);
    } else {
        // O número já existe na árvore
        return raiz;
    }
    raiz->alt = 1 + maximo(altura(raiz->esq), altura(raiz->dir));
    int balanceamento = fator_balanceamento(raiz);
    // Casos de balanceamento
    if (balanceamento > 1 && strcmp(numero, raiz->esq->numero) < 0) {
        // Rotação simples à direita
        return rotacao_direita(raiz);
    }
    if (balanceamento < -1 && strcmp(numero, raiz->dir->numero) > 0) {
        // Rotação simples à esquerda
        return rotacao_esquerda(raiz);
    }
    if (balanceamento > 1 && strcmp(numero, raiz->esq->numero) > 0) {
        // Rotação dupla à esquerda-direita
        rotacao_dupla_direita(raiz);
    }
    if (balanceamento < -1 && strcmp(numero, raiz->dir->numero) < 0) {
        // Rotação dupla à direita-esquerda
        rotacao_dupla_esquerda(raiz);
    }
    return raiz;
}

//Busca avl(ESSA FUNÇÃO ESTÁ ERRADA/INCOMPLETA)
No* buscar_no(No* raiz, char* numero) {
    if (raiz == NULL || strcmp(raiz->numero, numero) == 0) {
        return raiz;
    }
    if (strcmp(numero, raiz->numero) < 0) {
        return buscar_no(raiz->esq, numero);
    }
    return buscar_no(raiz->dir, numero);
}

//Busca menor nó
No* no_minimo(No* raiz) {
    No* atual = raiz;
    while (atual->esq != NULL) {
        atual = atual->esq;
    }
    return atual;
}
No* remover_no(No* raiz, char* numero) {
    if (raiz == NULL) {
        return raiz;
    }
    if (strcmp(numero, raiz->numero) < 0) {
        raiz->esq = remover_no(raiz->esq, numero);
    } else if (strcmp(numero, raiz->numero) > 0) {
        raiz->dir = remover_no(raiz->dir, numero);
    } else {
        if (raiz->esq == NULL || raiz->dir == NULL) {
            No* temp = raiz->esq ? raiz->esq : raiz->dir;
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }
            free(temp->numero);
            free(temp->nome);
            free(temp->endereco);
            free(temp);
        } else {
            No* temp = no_minimo(raiz->dir);
            strcpy(raiz->numero, temp->numero);
            strcpy(raiz->nome, temp->nome);
            strcpy(raiz->endereco, temp->endereco);
            raiz->dir = remover_no(raiz->dir, temp->numero);
        }
    }
    if (raiz == NULL) {
        return raiz;
    }
    raiz->alt = 1 + maximo(altura(raiz->esq), altura(raiz->dir));
    int balanceamento = fator_balanceamento(raiz);

    // Casos de balanceamento
    if (balanceamento > 1 && strcmp(numero, raiz->esq->numero) < 0) {
        // Rotação simples à direita
        return rotacao_direita(raiz);
    }
    if (balanceamento < -1 && strcmp(numero, raiz->dir->numero) > 0) {
        // Rotação simples à esquerda
        return rotacao_esquerda(raiz);
    }
    if (balanceamento > 1 && strcmp(numero, raiz->esq->numero) > 0) {
        // Rotação dupla à esquerda-direita
        rotacao_dupla_direita(raiz);
    }
    if (balanceamento < -1 && strcmp(numero, raiz->dir->numero) < 0) {
        // Rotação dupla à direita-esquerda
        rotacao_dupla_esquerda(raiz);
    }
    return raiz;
}

//(FUNÇÃO INCOMPLETA: DIVIDIR O NÚMERO CERTINHO DESSA FORMA (xx)98765-4321)
void imprimir_no(No* no) {
    printf("Número: %s\n", no->numero);
    printf("Nome: %s\n", no->nome);
    printf("Endereço: %s\n", no->endereco);
    printf("\n");
}

void imprimir_emOrdem(No* raiz) {
    if (raiz != NULL) {
        imprimir_emOrdem(raiz->esq);
        imprimir_no(raiz);
        imprimir_emOrdem(raiz->dir);
    }
}

void imprimir_preOrdem(No* raiz) {
    if (raiz != NULL) {
        imprimir_no(raiz);
        imprimir_preOrdem(raiz->esq);
        imprimir_preOrdem(raiz->dir);
    }
}

void imprimir_posOrdem(No* raiz) {
    if (raiz != NULL) {
        imprimir_posOrdem(raiz->esq);
        imprimir_posOrdem(raiz->dir);
        imprimir_no(raiz);
    }
}

void liberar_avlT(No* raiz) {
    if (raiz != NULL) {
        liberar_avlT(raiz->esq);
        liberar_avlT(raiz->dir);
        free(raiz->numero);
        free(raiz->nome);
        free(raiz->endereco);
        free(raiz);
    }
}