#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define HASH_SIZE 67

typedef struct AVLNode {
    char numero[15];
    char nome[50];
    char endereco[100];
    int altura;
    struct AVLNode* esquerda;   
    struct AVLNode* direita;
} AVLNode;

typedef struct HashTable {
    int ddd;
    AVLNode* raiz;
} HashTable;

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
    AVLNode* current = node;
    while (current->esquerda != NULL)
        current = current->esquerda;
    return current;
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
                temp = node;
                node = NULL;
            } else
                node =temp;

            free(temp);
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

HashTable* criarHashTable() {
    HashTable* hashTable = (HashTable*)malloc(HASH_SIZE * sizeof(HashTable));

    int i;
    for (i = 0; i < HASH_SIZE; i++) {
        hashTable[i].ddd = i + 1;
        hashTable[i].raiz = NULL;
    }

    return hashTable;
}

int calcularIndiceHash(int ddd) {
    return (ddd - 1) % HASH_SIZE;
}

void inserirHashTable(HashTable* hashTable, const char* numero, int ddd, const char* nome, const char* endereco) {
    int indice = calcularIndiceHash(ddd);
    AVLNode* raiz = hashTable[indice].raiz;

    if (raiz == NULL) {
        raiz = inserir(raiz, numero, nome, endereco);
        hashTable[indice].raiz = raiz;
    } else {
        AVLNode* node = encontrarNodo(raiz, numero);
        if (node == NULL)
            raiz = inserir(raiz, numero, nome, endereco);
        else {
            strcpy(node->nome, nome);
            strcpy(node->endereco, endereco);
        }
        hashTable[indice].raiz = raiz;
    }
}

void removerHashTable(HashTable* hashTable, const char* numero, int ddd) {
    int indice = calcularIndiceHash(ddd);
    AVLNode* raiz = hashTable[indice].raiz;

    if (raiz != NULL) {
        raiz = removerNodo(raiz, numero);
        hashTable[indice].raiz = raiz;
    }
}

AVLNode* encontrarHashTable(HashTable* hashTable, const char* numero, int ddd) {
    int indice = calcularIndiceHash(ddd);
    AVLNode* raiz = hashTable[indice].raiz;
    return encontrarNodo(raiz, numero);
}

void imprimirTabelaHash(HashTable* hashTable) {
    printf("Tabela Hash:\n");

    for (int i = 0; i < HASH_SIZE; i++) {
        printf("Posicao %d:\n", i);

        if (hashTable[i].raiz == NULL) {
            printf("Usuários não encontrados.\n\n");
        } else {
            imprimirEmOrdem(hashTable[i].raiz);
            printf("\n");
        }
    }
}

int main() {
    HashTable* hashTable = criarHashTable();

    inserirHashTable(hashTable, "12345678", 85, "Joao", "Rua A");
    inserirHashTable(hashTable, "56789101", 85, "Maria", "Rua B");
    inserirHashTable(hashTable, "90121314", 21, "Pedro", "Rua C");

    imprimirTabelaHash(hashTable);

    int ddd = 85;  // DDD da Ã¡rvore a ser impressa
    int indice = calcularIndiceHash(ddd);
    AVLNode* raiz = hashTable[indice].raiz;
    
    printf("\n------------1--------------\n");
    printf("Imprimir em pre-ordem:\n");
    imprimirPreOrdem(raiz);

    printf("------------2--------------\n");
    printf("Imprimir em ordem:\n");
    imprimirEmOrdem(raiz);

    printf("------------3--------------\n");
    printf("Imprimir em pos-ordem:\n");
    imprimirPosOrdem(raiz);
    printf("---------------------------\n\n");

    AVLNode* node = encontrarHashTable(hashTable, "90121314", 21);
    if (node != NULL) {
        printf("---CONTADO ENCONTRADO---\n");
        printf("Numero: %s\n", node->numero);
        printf("Nome: %s\n", node->nome);
        printf("Endereco: %s\n", node->endereco);
    }

    removerHashTable(hashTable, "56789101", 85);

    printf("\nApós a remoção:\n\n");
    imprimirTabelaHash(hashTable);

    return 0;
}   
/*char* numAleatorio(int ddd){
    int i;char num[10];
    //ddd de int para string
    num[0]='9';
    //Assegura que cada número gerado será diferente(NÃO TESTEI).
    srand(time(NULL));
    //Gera 8 número aleatórios
    for (i = 3; i < 10; i++) {
        num[i] = '0' + rand() % 10;
    }
    return num;
}*/
