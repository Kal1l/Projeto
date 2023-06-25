#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arvAvl.h"

// Cria um novo nó com as informações do contato passadas como parâmetros
AVLNo* criarNo(const char* numero, const char* nome, const char* endereco) {
    // Aloca memória para o novo nó
    AVLNo* no = (AVLNo*)malloc(sizeof(AVLNo));
    // Copia as informações do contato para o nó
    strcpy(no->numero, numero);
    strcpy(no->nome, nome);
    strcpy(no->endereco, endereco);
    // Inicializa os demais campos do nó
    no->altura = 1;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

// Retorna a altura de um nó
int altura(AVLNo* no) {
    if (no == NULL)
        return 0;
    return no->altura;
}

// Retorna o máximo entre dois números
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Calcula o fator de balanceamento de um nó
int fatorBalanceamento(AVLNo* no) {
    if (no == NULL)
        return 0;
    return altura(no->esquerda) - altura(no->direita);
}

// Realiza uma rotação para a direita no nó 'y' e retorna o novo nó que será a raiz da subárvore
AVLNo* rotacaoDireita(AVLNo* y) {
    AVLNo* x = y->esquerda;
    AVLNo* T2 = x->direita;

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
AVLNo* rotacaoEsquerda(AVLNo* x) {
    AVLNo* y = x->direita;
    AVLNo* T2 = y->esquerda;

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
AVLNo* inserir(AVLNo* no, const char* numero, const char* nome, const char* endereco) {
    if (no == NULL)
        return criarNo(numero, nome, endereco);

    // Compara o número do contato com o número do nó atual
    int cmp = strcmp(numero, no->numero);

    if (cmp < 0)
        no->esquerda = inserir(no->esquerda, numero, nome, endereco);
    else if (cmp > 0)
        no->direita = inserir(no->direita, numero, nome, endereco);
    else {
        // O número já existe na árvore, atualiza o nome e o endereço
        strcpy(no->nome, nome);
        strcpy(no->endereco, endereco);
        return no;
    }

    // Atualiza a altura do nó atual
    no->altura = 1 + max(altura(no->esquerda), altura(no->direita));

    // Calcula o fator de balanceamento do nó atual
    int balanceamento = fatorBalanceamento(no);

    // Realiza as rotações necessárias para manter a propriedade de AVL
    if (balanceamento > 1 && strcmp(numero, no->esquerda->numero) < 0)
        return rotacaoDireita(no);

    if (balanceamento < -1 && strcmp(numero, no->direita->numero) > 0)
        return rotacaoEsquerda(no);

    if (balanceamento > 1 && strcmp(numero, no->esquerda->numero) > 0) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    if (balanceamento < -1 && strcmp(numero, no->direita->numero) < 0) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    // Retorna a raiz atualizada
    return no;
}

// Busca um nó na árvore AVL pelo número do contato e retorna o nó encontrado ou NULL se não encontrado(Busca Binária)
AVLNo* encontrarNo(AVLNo* no, const char* numero) {
    if (no == NULL || strcmp(no->numero, numero) == 0)
        return no;

    // Compara o número do contato com o número do nó atual
    int cmp = strcmp(numero, no->numero);

    if (cmp < 0)
        return encontrarNo(no->esquerda, numero);
    else
        return encontrarNo(no->direita, numero);
}

// Encontra o nó com o menor número na árvore AVL e retorna o nó encontrado
AVLNo* encontrarMenorNo(AVLNo* no) {
    AVLNo* atual = no;
    while (atual->esquerda != NULL)
        atual = atual->esquerda;
    return atual;
}

// Remove um nó da árvore AVL pelo número do contato e retorna a raiz atualizada
AVLNo* removerNo(AVLNo* no, const char* numero) {
    if (no == NULL)
        return no;

    // Compara o número do contato com o número do nó atual
    int cmp = strcmp(numero, no->numero);

    if (cmp < 0)
        no->esquerda = removerNo(no->esquerda, numero);
    else if (cmp > 0)
        no->direita = removerNo(no->direita, numero);
    else {
        if (no->esquerda == NULL || no->direita == NULL) {
            // O nó possui no máximo um filho, realiza a remoção
            AVLNo* temp = no->esquerda ? no->esquerda : no->direita;

            if (temp == NULL) {
                // O nó é uma folha, libera a memória e retorna NULL
                free(no);
                return NULL;
            } else {
                // O nó possui um filho, copia os valores do filho para o nó atual e realiza a remoção do filho
                strcpy(no->numero, temp->numero);
                strcpy(no->nome, temp->nome);
                strcpy(no->endereco, temp->endereco);
                no->esquerda = no->direita = NULL;
                free(temp);
            }
        } else {
            // O nó possui dois filhos, encontra o nó com o menor número na subárvore direita
            AVLNo* temp = encontrarMenorNo(no->direita);

            // Copia os valores do nó encontrado para o nó atual
            strcpy(no->numero, temp->numero);
            strcpy(no->nome, temp->nome);
            strcpy(no->endereco, temp->endereco);

            // Remove o nó encontrado da subárvore direita
            no->direita = removerNo(no->direita, temp->numero);
        }
    }

    if (no == NULL)
        return no;

    // Atualiza a altura do nó atual
    no->altura = 1 + max(altura(no->esquerda), altura(no->direita));
    
    // Calcula o fator de balanceamento do nó atual
    int balanceamento = fatorBalanceamento(no);

    // Realiza as rotações necessárias para manter a propriedade de AVL
    if (balanceamento > 1 && fatorBalanceamento(no->esquerda) >= 0)
        return rotacaoDireita(no);

    if (balanceamento > 1 && fatorBalanceamento(no->esquerda) < 0) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    if (balanceamento < -1 && fatorBalanceamento(no->direita) <= 0)
        return rotacaoEsquerda(no);

    if (balanceamento < -1 && fatorBalanceamento(no->direita) > 0) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    // Retorna a raiz atualizada
    return no;
}

// Imprime os contatos em pré-ordem (raiz, esquerda, direita)
void imprimirPreOrdem(AVLNo* no) {
    if (no == NULL)
        return;

    printf("Numero: %s\n", no->numero);
    printf("Nome: %s\n", no->nome);
    printf("Endereco: %s\n", no->endereco);
    printf("\n");

    imprimirPreOrdem(no->esquerda);
    imprimirPreOrdem(no->direita);
}

// Imprime os contatos em ordem crescente (esquerda, raiz, direita)
void imprimirEmOrdem(AVLNo* no) {
    if (no == NULL)
        return;

    imprimirEmOrdem(no->esquerda);

    printf("Numero: %s\n", no->numero);
    printf("Nome: %s\n", no->nome);
    printf("Endereco: %s\n", no->endereco);
    printf("\n");

    imprimirEmOrdem(no->direita);
}

// Imprime os contatos em pós-ordem (esquerda, direita, raiz)
void imprimirPosOrdem(AVLNo* no) {
    if (no == NULL)
        return;

    imprimirPosOrdem(no->esquerda);
    imprimirPosOrdem(no->direita);

    printf("Numero: %s\n", no->numero);
    printf("Nome: %s\n", no->nome);
    printf("Endereco: %s\n", no->endereco);
    printf("\n");
}

// Percorre a árvore em ordem e retorna a contagem total de nós
int contarNos(AVLNo* no) {
    if (no == NULL)
        return 0;

    // Retorna a contagem total de nós na subárvore
    return 1 + contarNos(no->esquerda) + contarNos(no->direita);
}

// Percorre a árvore em ordem e registra os nomes dos contatos
void registrarNomes(AVLNo* no, char** nomes, int* indice) {
    if (no == NULL)
        return;

    // Percorre a árvore em ordem e registra os nomes dos contatos
    registrarNomes(no->esquerda, nomes, indice);

    strcpy(nomes[*indice], no->nome);
    (*indice)++;

    registrarNomes(no->direita, nomes, indice);
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
void imprimirContatoPorNome(AVLNo* no, const char* nome) {
    if (no == NULL)
        return;

    imprimirContatoPorNome(no->esquerda, nome);

    int comparacao = strcmp(no->nome, nome);
    if (comparacao == 0) {
        printf("Numero: %s\n", no->numero);
        printf("Nome: %s\n", no->nome);
        printf("Endereco: %s\n", no->endereco);
        printf("\n");
        
    }

    imprimirContatoPorNome(no->direita, nome);
}

// Imprime os contatos em ordem alfabética por nome
void imprimirPorNomeOrdenado(AVLNo* no) {
    int tamanho = contarNos(no);

    char** nomes = (char**)malloc(tamanho * sizeof(char*));
    for (int i = 0; i < tamanho; i++) {
        nomes[i] = (char*)malloc(50 * sizeof(char));
    }

    int indice = 0;

    registrarNomes(no, nomes, &indice);

    ordenarNomes(nomes, tamanho);

    for (int i = 0; i < tamanho; i++) {
        imprimirContatoPorNome(no, nomes[i]);
    }

    for (int i = 0; i < tamanho; i++) {
        free(nomes[i]);
    }
    free(nomes);
}
