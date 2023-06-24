#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arvAvl.h"


AVLNode* criarNode(const char* numero, const char* nome, const char* endereco) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    strcpy(node->numero, numero);
    strcpy(node->nome, nome);
    strcpy(node->endereco, endereco);
    node->altura = 1;
    node->esquerda = NULL;
    node->direita = NULL;
    return node;
}
int altura(AVLNode* node) {
    if (node == NULL)
        return 0;
    return node->altura;
}
int max(int a, int b) {
    return (a > b) ? a : b;
}
int fatorBalanceamento(AVLNode* node) {
    if (node == NULL)
        return 0;
    return altura(node->esquerda) - altura(node->direita);
}
AVLNode* rotacaoDireita(AVLNode* y) {
    AVLNode* x = y->esquerda;
    AVLNode* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}
AVLNode* rotacaoEsquerda(AVLNode* x) {
    AVLNode* y = x->direita;
    AVLNode* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    return y;
}
AVLNode* inserir(AVLNode* node, const char* numero, const char* nome, const char* endereco) {
    if (node == NULL)
        return criarNode(numero, nome, endereco);

    int cmp = strcmp(numero, node->numero);

    if (cmp < 0)
        node->esquerda = inserir(node->esquerda, numero, nome, endereco);
    else if (cmp > 0)
        node->direita = inserir(node->direita, numero, nome, endereco);
    else {
        strcpy(node->nome, nome);
        strcpy(node->endereco, endereco);
        return node;
    }

    node->altura = 1 + max(altura(node->esquerda), altura(node->direita));

    int balanceamento = fatorBalanceamento(node);

    if (balanceamento > 1 && strcmp(numero, node->esquerda->numero) < 0)
        return rotacaoDireita(node);

    if (balanceamento < -1 && strcmp(numero, node->direita->numero) > 0)
        return rotacaoEsquerda(node);

    if (balanceamento > 1 && strcmp(numero, node->esquerda->numero) > 0) {
        node->esquerda = rotacaoEsquerda(node->esquerda);
        return rotacaoDireita(node);
    }

    if (balanceamento < -1 && strcmp(numero, node->direita->numero) < 0) {
        node->direita = rotacaoDireita(node->direita);
        return rotacaoEsquerda(node);
    }

    return node;
}
AVLNode* encontrarNodo(AVLNode* node, const char* numero) {
    if (node == NULL || strcmp(node->numero, numero) == 0)
        return node;

    int cmp = strcmp(numero, node->numero);

    if (cmp < 0)
        return encontrarNodo(node->esquerda, numero);
    else
        return encontrarNodo(node->direita, numero);
}
AVLNode* encontrarMenorNodo(AVLNode* node) {
    AVLNode* atual = node;
    while (atual->esquerda != NULL)
        atual = atual->esquerda;
    return atual;
}
AVLNode* removerNodo(AVLNode* node, const char* numero) {
    if (node == NULL)
        return node;

    int cmp = strcmp(numero, node->numero);

    if (cmp < 0)
        node->esquerda = removerNodo(node->esquerda, numero);
    else if (cmp > 0)
        node->direita = removerNodo(node->direita, numero);
    else {
        if (node->esquerda == NULL || node->direita == NULL) {
            AVLNode* temp = node->esquerda ? node->esquerda : node->direita;

            if (temp == NULL) {
                free(node);
                return NULL;
            } else {
                strcpy(node->numero, temp->numero);
                strcpy(node->nome, temp->nome);
                strcpy(node->endereco, temp->endereco);
                node->esquerda = node->direita = NULL;
                free(temp);
            }
        } else {
            AVLNode* temp = encontrarMenorNodo(node->direita);

            strcpy(node->numero, temp->numero);
            strcpy(node->nome, temp->nome);
            strcpy(node->endereco, temp->endereco);
            node->direita = removerNodo(node->direita, temp->numero);
        }
    }

    if (node == NULL)
        return node;

    node->altura = 1 + max(altura(node->esquerda), altura(node->direita));

    int balanceamento = fatorBalanceamento(node);

    if (balanceamento > 1 && fatorBalanceamento(node->esquerda) >= 0)
        return rotacaoDireita(node);

    if (balanceamento > 1 && fatorBalanceamento(node->esquerda) < 0) {
        node->esquerda = rotacaoEsquerda(node->esquerda);
        return rotacaoDireita(node);
    }

    if (balanceamento < -1 && fatorBalanceamento(node->direita) <= 0)
        return rotacaoEsquerda(node);

    if (balanceamento < -1 && fatorBalanceamento(node->direita) > 0) {
        node->direita = rotacaoDireita(node->direita);
        return rotacaoEsquerda(node);
    }

    return node;
}

void imprimirPreOrdem(AVLNode* node) {
    if (node == NULL)
        return;

    printf("Numero: %s\n", node->numero);
    printf("Nome: %s\n", node->nome);
    printf("Endereco: %s\n", node->endereco);
    printf("\n");

    imprimirPreOrdem(node->esquerda);
    imprimirPreOrdem(node->direita);
}
void imprimirEmOrdem(AVLNode* node) {
    if (node == NULL)
        return;

    imprimirEmOrdem(node->esquerda);

    printf("Numero: %s\n", node->numero);
    printf("Nome: %s\n", node->nome);
    printf("Endereco: %s\n", node->endereco);
    printf("\n");

    imprimirEmOrdem(node->direita);
}
void imprimirPosOrdem(AVLNode* node) {
    if (node == NULL)
        return;

    imprimirPosOrdem(node->esquerda);
    imprimirPosOrdem(node->direita);

    printf("Numero: %s\n", node->numero);
    printf("Nome: %s\n", node->nome);
    printf("Endereco: %s\n", node->endereco);
    printf("\n");
}
int contarNos(AVLNode* node) {
    if (node == NULL)
        return 0;

    return 1 + contarNos(node->esquerda) + contarNos(node->direita);
}
void registrarNomes(AVLNode* node, char** nomes, int* indice) {
    if (node == NULL)
        return;

    registrarNomes(node->esquerda, nomes, indice);

    strcpy(nomes[*indice], node->nome);
    (*indice)++;

    registrarNomes(node->direita, nomes, indice);
}
void ordenarNomes(char** nomes, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (strcmp(nomes[j], nomes[j + 1]) > 0) {
                char temp[50];
                strcpy(temp, nomes[j]);
                strcpy(nomes[j], nomes[j + 1]);
                strcpy(nomes[j + 1], temp);
            }
        }
    }
}
void imprimirContatoPorNome(AVLNode* node, const char* nome) {
    if (node == NULL)
        return;

    imprimirContatoPorNome(node->esquerda, nome);

    int comparacao = strcmp(node->nome, nome);
    if (comparacao == 0) {
        printf("Numero: %s\n", node->numero);
        printf("Nome: %s\n", node->nome);
        printf("Endereco: %s\n", node->endereco);
        printf("\n");
        
    }

    imprimirContatoPorNome(node->direita, nome);
}
void imprimirPorNomeOrdenado(AVLNode* node) {
    int tamanho = contarNos(node);

    char** nomes = (char**)malloc(tamanho * sizeof(char*));
    for (int i = 0; i < tamanho; i++) {
        nomes[i] = (char*)malloc(50 * sizeof(char));
    }

    int indice = 0;

    registrarNomes(node, nomes, &indice);

    ordenarNomes(nomes, tamanho);

    for (int i = 0; i < tamanho; i++) {
        imprimirContatoPorNome(node, nomes[i]);
    }

    for (int i = 0; i < tamanho; i++) {
        free(nomes[i]);
    }
    free(nomes);
}