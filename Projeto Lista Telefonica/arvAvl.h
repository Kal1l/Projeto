#ifndef ARVAVL_H
#define ARVAVL_H

typedef struct AVLNode {
    char numero[10];
    char nome[50];
    char endereco[100];
    int altura;
    struct AVLNode* esquerda;   
    struct AVLNode* direita;
} AVLNode;

AVLNode* criarNode(const char* numero, const char* nome, const char* endereco);
int altura(AVLNode* node);
int max(int a, int b);
int fatorBalanceamento(AVLNode* node);
AVLNode* rotacaoDireita(AVLNode* y);
AVLNode* rotacaoEsquerda(AVLNode* x);
AVLNode* inserir(AVLNode* node, const char* numero, const char* nome, const char* endereco);
AVLNode* encontrarNodo(AVLNode* node, const char* numero);
AVLNode* encontrarMenorNodo(AVLNode* node) ;
AVLNode* removerNodo(AVLNode* node, const char* numero);
void imprimirPreOrdem(AVLNode* node);
void imprimirEmOrdem(AVLNode* node) ;
void imprimirPosOrdem(AVLNode* node);
int contarNos(AVLNode* node);
void registrarNomes(AVLNode* node, char** nomes, int* indice);
void ordenarNomes(char** nomes, int tamanho);
void imprimirContatoPorNome(AVLNode* node, const char* nome);
void imprimirPorNomeOrdenado(AVLNode* node);
#endif