#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arvAvl.h"

// Cria um novo nó com as informações do contato passadas como parâmetros
AVLNode* criarNode(const char* numero, const char* nome, const char* endereco) {
    // Aloca memória para o novo nó
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    // Copia as informações do contato para o nó
    strcpy(node->numero, numero);
    strcpy(node->nome, nome);
    strcpy(node->endereco, endereco);
    // Inicializa os demais campos do nó
    node->altura = 1;
    node->esquerda = NULL;
    node->direita = NULL;
    return node;
}

// Retorna a altura de um nó
int altura(AVLNode* node) {
    if (node == NULL)
        return 0;
    return node->altura;
}

// Retorna o máximo entre dois números
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Calcula o fator de balanceamento de um nó
int fatorBalanceamento(AVLNode* node) {
    if (node == NULL)
        return 0;
    return altura(node->esquerda) - altura(node->direita);
}

// Realiza uma rotação para a direita no nó 'y' e retorna o novo nó que será a raiz da subárvore
AVLNode* rotacaoDireita(AVLNode* y) {
    AVLNode* x = y->esquerda;
    AVLNode* T2 = x->direita;

    // Realiza a rotação
    x->direita = y;
    y->esquerda = T2;

    // Atualiza as alturas dos nós afetados
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    // Retorna a nova raiz da subárvore
    return x;
}

// Realiza uma rotação para a esquerda no nó 'x' e retorna o novo nó que será a raiz da subárvore
AVLNode* rotacaoEsquerda(AVLNode* x) {
    AVLNode* y = x->direita;
    AVLNode* T2 = y->esquerda;

    // Realiza a rotação
    y->esquerda = x;
    x->direita = T2;

    // Atualiza as alturas dos nós afetados
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    // Retorna a nova raiz da subárvore
    return y;
}

// Insere um novo contato na árvore AVL e retorna a raiz atualizada
AVLNode* inserir(AVLNode* node, const char* numero, const char* nome, const char* endereco) {
    if (node == NULL)
        return criarNode(numero, nome, endereco);

    // Compara o número do contato com o número do nó atual
    int cmp = strcmp(numero, node->numero);

    if (cmp < 0)
        node->esquerda = inserir(node->esquerda, numero, nome, endereco);
    else if (cmp > 0)
        node->direita = inserir(node->direita, numero, nome, endereco);
    else {
        // O número já existe na árvore, atualiza o nome e o endereço
        strcpy(node->nome, nome);
        strcpy(node->endereco, endereco);
        return node;
    }

    // Atualiza a altura do nó atual
    node->altura = 1 + max(altura(node->esquerda), altura(node->direita));

    // Calcula o fator de balanceamento do nó atual
    int balanceamento = fatorBalanceamento(node);

    // Realiza as rotações necessárias para manter a propriedade de AVL
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

    // Retorna a raiz atualizada
    return node;
}

// Busca um nó na árvore AVL pelo número do contato e retorna o nó encontrado ou NULL se não encontrado
AVLNode* encontrarNodo(AVLNode* node, const char* numero) {
    if (node == NULL || strcmp(node->numero, numero) == 0)
        return node;

    // Compara o número do contato com o número do nó atual
    int cmp = strcmp(numero, node->numero);

    if (cmp < 0)
        return encontrarNodo(node->esquerda, numero);
    else
        return encontrarNodo(node->direita, numero);
}

// Encontra o nó com o menor número na árvore AVL e retorna o nó encontrados
AVLNode* encontrarMenorNodo(AVLNode* node) {
    AVLNode* atual = node;
    while (atual->esquerda != NULL)
        atual = atual->esquerda;
    return atual;
}

// Remove um nó da árvore AVL pelo número do contato e retorna a raiz atualizada
AVLNode* removerNodo(AVLNode* node, const char* numero) {
    if (node == NULL)
        return node;

    // Compara o número do contato com o número do nó atual
    int cmp = strcmp(numero, node->numero);

    if (cmp < 0)
        node->esquerda = removerNodo(node->esquerda, numero);
    else if (cmp > 0)
        node->direita = removerNodo(node->direita, numero);
    else {
        if (node->esquerda == NULL || node->direita == NULL) {
            // O nó possui no máximo um filho, realiza a remoção
            AVLNode* temp = node->esquerda ? node->esquerda : node->direita;

            if (temp == NULL) {
                // O nó é uma folha, libera a memória e retorna NULL
                free(node);
                return NULL;
            } else {
                // O nó possui um filho, copia os valores do filho para o nó atual e realiza a remoção do filho
                strcpy(node->numero, temp->numero);
                strcpy(node->nome, temp->nome);
                strcpy(node->endereco, temp->endereco);
                node->esquerda = node->direita = NULL;
                free(temp);
            }
        } else {
            // O nó possui dois filhos, encontra o nó com o menor número na subárvore direita
            AVLNode* temp = encontrarMenorNodo(node->direita);

            // Copia os valores do nó encontrado para o nó atual
            strcpy(node->numero, temp->numero);
            strcpy(node->nome, temp->nome);
            strcpy(node->endereco, temp->endereco);

            // Remove o nó encontrado da subárvore direita
            node->direita = removerNodo(node->direita, temp->numero);
        }
    }

    if (node == NULL)
        return node;

    // Atualiza a altura do nó atual
    node->altura = 1 + max(altura(node->esquerda), altura(node->direita));
    
    // Calcula o fator de balanceamento do nó atual
    int balanceamento = fatorBalanceamento(node);

    // Realiza as rotações necessárias para manter a propriedade de AVL
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

    // Retorna a raiz atualizada
    return node;
}

// Imprime os contatos em pré-ordem (raiz, esquerda, direita)
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

// Imprime os contatos em ordem crescente (esquerda, raiz, direita)
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

// Imprime os contatos em pós-ordem (esquerda, direita, raiz)
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

// Percorre a árvore em ordem e retorna a contagem total de nós
int contarNos(AVLNode* node) {
    if (node == NULL)
        return 0;

    // Retorna a contagem total de nós na subárvore
    return 1 + contarNos(node->esquerda) + contarNos(node->direita);
}

// Percorre a árvore em ordem e registra os nomes dos contatos
void registrarNomes(AVLNode* node, char** nomes, int* indice) {
    if (node == NULL)
        return;

    // Percorre a árvore em ordem e registra os nomes dos contatos
    registrarNomes(node->esquerda, nomes, indice);

    strcpy(nomes[*indice], node->nome);
    (*indice)++;

    registrarNomes(node->direita, nomes, indice);
}

// Ordena os nomes em ordem alfabética 
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

// Imprime as informações de um contato com base no nome
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

// Imprime os contatos em ordem alfabética por nome
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
