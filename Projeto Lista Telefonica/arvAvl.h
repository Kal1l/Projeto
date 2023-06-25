#ifndef ARVAVL_H
#define ARVAVL_H

// Definição da estrutura de um nó da árvore AVL
typedef struct AVLNo {
    char numero[10];
    char nome[50];
    char endereco[100];
    int altura;
    struct AVLNo* esquerda;   
    struct AVLNo* direita;
} AVLNo;

// Cria um novo nó com as informações do contato passadas como parâmetros
AVLNo* criarNo(const char* numero, const char* nome, const char* endereco);
// Retorna a altura de um nó
int altura(AVLNo* no);
// Retorna o máximo entre dois números
int max(int a, int b);
// Calcula o fator de balanceamento de um nó
int fatorBalanceamento(AVLNo* no);
// Realiza uma rotação para a direita no nó 'y' e retorna o novo nó que será a raiz da subárvore
AVLNo* rotacaoDireita(AVLNo* y);
// Realiza uma rotação para a esquerda no nó 'x' e retorna o novo nó que será a raiz da subárvore
AVLNo* rotacaoEsquerda(AVLNo* x);
// Insere um novo contato na árvore AVL e retorna a raiz atualizada
AVLNo* inserir(AVLNo* no, const char* numero, const char* nome, const char* endereco);
// Busca um contato na árvore com base no número e retorna o nó correspondente, ou NULL se não encontrado
AVLNo* encontrarNo(AVLNo* no, const char* numero);
// Encontra o nó com o menor número na árvore e retorna o nó correspondente
AVLNo* encontrarMenorNo(AVLNo* no) ;
// Remove um nó com base no número e retorna a raiz atualizada
AVLNo* removerNo(AVLNo* no, const char* numero);
// Imprime os contatos na árvore em pré-ordem
void imprimirPreOrdem(AVLNo* no);
// Imprime os contatos na árvore em-ordem
void imprimirEmOrdem(AVLNo* no) ;
// Imprime os contatos na árvore em pós-ordem
void imprimirPosOrdem(AVLNo* no);
// Conta o número de nós na árvore
int contarNos(AVLNo* no);
// Armazena os nomes dos contatos em um array de strings 'nomes' e atualiza o índice
void registrarNomes(AVLNo* no, char** nomes, int* indice);
// Ordena os nomes dos contatos em ordem alfabética
void ordenarNomes(char** nomes, int tamanho);
// Imprime o contato com um determinado nome
void imprimirContatoPorNome(AVLNo* no, const char* nome);
// Imprime os contatos em ordem alfabética pelo nome
void imprimirPorNomeOrdenado(AVLNo* no);
#endif