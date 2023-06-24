#ifndef ARVAVL_H
#define ARVAVL_H

// Definição da estrutura de um nó da árvore AVL
typedef struct AVLNode {
    char numero[10];
    char nome[50];
    char endereco[100];
    int altura;
    struct AVLNode* esquerda;   
    struct AVLNode* direita;
} AVLNode;

// Cria um novo nó com as informações do contato passadas como parâmetros
AVLNode* criarNode(const char* numero, const char* nome, const char* endereco);
// Retorna a altura de um nó
int altura(AVLNode* node);
// Retorna o máximo entre dois números
int max(int a, int b);
// Calcula o fator de balanceamento de um nó
int fatorBalanceamento(AVLNode* node);
// Realiza uma rotação para a direita no nó 'y' e retorna o novo nó que será a raiz da subárvore
AVLNode* rotacaoDireita(AVLNode* y);
// Realiza uma rotação para a esquerda no nó 'x' e retorna o novo nó que será a raiz da subárvore
AVLNode* rotacaoEsquerda(AVLNode* x);
// Insere um novo contato na árvore AVL e retorna a raiz atualizada
AVLNode* inserir(AVLNode* node, const char* numero, const char* nome, const char* endereco);
// Busca um contato na árvore com base no número e retorna o nó correspondente, ou NULL se não encontrado
AVLNode* encontrarNodo(AVLNode* node, const char* numero);
// Encontra o nó com o menor número na árvore e retorna o nó correspondente
AVLNode* encontrarMenorNodo(AVLNode* node) ;
// Remove um nó com base no número e retorna a raiz atualizada
AVLNode* removerNodo(AVLNode* node, const char* numero);
// Imprime os contatos na árvore em pré-ordem
void imprimirPreOrdem(AVLNode* node);
// Imprime os contatos na árvore em-ordem
void imprimirEmOrdem(AVLNode* node) ;
// Imprime os contatos na árvore em pós-ordem
void imprimirPosOrdem(AVLNode* node);
// Conta o número de nós na árvore
int contarNos(AVLNode* node);
// Armazena os nomes dos contatos em um array de strings 'nomes' e atualiza o índice
void registrarNomes(AVLNode* node, char** nomes, int* indice);
// Ordena os nomes dos contatos em ordem alfabética
void ordenarNomes(char** nomes, int tamanho);
// Imprime o contato com um determinado nome
void imprimirContatoPorNome(AVLNode* node, const char* nome);
// Imprime os contatos em ordem alfabética pelo nome
void imprimirPorNomeOrdenado(AVLNode* node);
#endif