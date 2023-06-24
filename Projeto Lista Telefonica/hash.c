#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arvAvl.h"
#include "hash.h"
#include "indices.h"

// Função para gerar um DDD aleatório
int gerarDDD() {
    int indice = rand() % num_ddds_brasileiros;
    return ddds_brasileiros[indice];
}

// Função para criar um novo nó da tabela hash
// Parâmetros: ddd - o DDD do nó, raiz - a raiz da árvore AVL associada ao nó
// Retorna o novo nó da tabela hash
HashNode* criarHashNode(int ddd, AVLNode* raiz) {
    HashNode* novoNo = (HashNode*)malloc(sizeof(HashNode));
    novoNo->ddd = ddd;
    novoNo->raiz = raiz;
    novoNo->proximo = NULL;
    return novoNo;
}

// Função para criar uma tabela hash vazia
HashTable* criarHashTable() {
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    hashTable->tamanho = HASH_SIZE;
    hashTable->tabela = (HashNode**)calloc(HASH_SIZE, sizeof(HashNode*));
    return hashTable;
}

// Função para calcular o índice da tabela hash para um determinado DDD
// Parâmetro: ddd - o DDD para o qual calcular o índice
// Retorna: o índice calculado
int calcularIndiceHash(int ddd) {
    return ddd % HASH_SIZE;
}

// Função para inserir um contato na tabela hash
// Parâmetros: a tabela hash, o número de telefone do contato, o DDD do contato, o nome do contato e o endereço do contato
void inserirContato(HashTable* hashTable, const char* numero, int ddd, const char* nome, const char* endereco) {
    int indice = calcularIndiceHash(ddd);

    // Verificar se o índice está vazio
    if (hashTable->tabela[indice] == NULL) {
        AVLNode* raiz = inserir(NULL, numero, nome, endereco);
        hashTable->tabela[indice] = criarHashNode(ddd, raiz);
    } else {
        HashNode* atual = hashTable->tabela[indice];

        // Percorrer a lista encadeada até encontrar um nó com o mesmo DDD
        while (atual->proximo != NULL && atual->ddd != ddd) {
            atual = atual->proximo;
        }

        // Caso já exista um nó com o mesmo DDD
        if (atual->ddd == ddd) {
            atual->raiz = inserir(atual->raiz, numero, nome, endereco);
        } else {
            AVLNode* raiz = inserir(NULL, numero, nome, endereco);
            HashNode* novoNo = criarHashNode(ddd, raiz);
            atual->proximo = novoNo;
        }
    }
}

// Função para remover um contato da tabela hash
// Parâmetros: a tabela hash, o número de telefone do contato e o DDD do contato
void removerContato(HashTable* hashTable, const char* numero, int ddd) {
    int indice = calcularIndiceHash(ddd);

    // Verificar se o índice está vazio
    if (hashTable->tabela[indice] == NULL)
        return;
    else {
        HashNode* atual = hashTable->tabela[indice];
        HashNode* anterior = NULL;

        // Percorrer a lista encadeada até encontrar um nó com o mesmo DDD
        while (atual != NULL) {
            if (atual->ddd == ddd) {
                AVLNode* arvoreAntes = encontrarArvoreNaTabela(hashTable, ddd);
                atual->raiz = removerNodo(atual->raiz, numero);
                AVLNode* arvoreDepois = encontrarArvoreNaTabela(hashTable, ddd);

                // Exibir a altura da árvore antes e depois da remoção
                printf("Altura da árvore antes da remoção: %d\n", altura(arvoreAntes));
                printf("Altura da árvore depois da remoção: %d\n", altura(arvoreDepois));

                // Se a árvore AVL estiver vazia, remover o nó da lista
                if (atual->raiz == NULL) {
                    if (anterior == NULL) {
                        hashTable->tabela[indice] = atual->proximo;
                    } else {
                        anterior->proximo = atual->proximo;
                        free(atual);
                    }
                }
                return;
            }
            anterior = atual;
            atual = atual->proximo;
        }
    }
}

// Função para gerar usuários aleatórios na tabela hash
// Parâmetros: a tabela hash, a quantidade de usuários a serem gerados e a estrutura de índices invertidos
void gerarUsuariosAleatorios(HashTable* hashTable, int quantidade, IndiceInvertido* indice) {
    const char* nomes[] = {"Alicia", "Francisco", "Carlos", "Davi", "Eva", "Kalil", "Graça", "Henrique", "Ivy", "Jackson"};
    const char* sobrenomes[] = {"Santos", "Rodrigues", "Amaral", "Jones", "Silva", "Davis", "Miller", "Wilson", "Moreira", "Holanda"};
    const char* enderecos[] = {"Rua Goiania", "Vila Arraial", "Jangurussu", "Praca D", "Estrada E", "Avenida F", "Rua G", "Travessa H", "Rua I", "Avenida J"};

    for (int i = 0; i < quantidade; i++) {
        int ddd_index = rand() % num_ddds_brasileiros;  // Escolhe um índice aleatório para o DDD brasileiro
        int ddd = ddds_brasileiros[ddd_index];         // Obtém o DDD correspondente ao índice aleatório

        const char* nome = nomes[rand() % 10];
        const char* sobrenome = sobrenomes[rand() % 10];
        const char* endereco = enderecos[rand() % 10];

        char* numero = gerarNumeroUnico(hashTable, ddd);

        char nomeCompleto[60];
        snprintf(nomeCompleto, sizeof(nomeCompleto), "%s %s", nome, sobrenome);

        inserirContato(hashTable, numero, ddd, nomeCompleto, endereco);
        adicionarIndice(indice, numero);
    }
}

// Função para encontrar um nó na tabela hash
// Parâmetros: a tabela hash, o número de telefone do contato e o DDD do contato
// Retorna: o nó da árvore AVL correspondente ao número de telefone e DDD fornecidos
AVLNode* encontrarHashTable(HashTable* hashTable, const char* numero, int ddd) {
    int indice = calcularIndiceHash(ddd);

    // Verificar se o índice está vazio
    if (hashTable->tabela[indice] == NULL)
        return NULL;
    else {
        HashNode* atual = hashTable->tabela[indice];

        // Percorrer a lista encadeada até encontrar um nó com o mesmo DDD
        while (atual != NULL) {
            if (atual->ddd == ddd) {
                AVLNode* result = encontrarNodo(atual->raiz, numero);
                if (result != NULL)
                    return result;
            }
            atual = atual->proximo;
        }
    }
    return NULL;
}

// Função para imprimir a tabela hash
// Passa a tabela como parâmetro
void imprimirTabelaHash(HashTable* hashTable) {
    printf("Tabela Hash:\n");

    for (int i = 0; i < HASH_SIZE; i++) {
        printf("Posicao %d:\n", i);

        if (hashTable->tabela[i] == NULL) {
            printf("Usuários não encontrados.\n\n");
        } else {
            HashNode* atual = hashTable->tabela[i];

            while (atual != NULL) {
                printf("DDD: %d\n", atual->ddd);
                if (atual->raiz == NULL) {
                    printf("Usuários não encontrados.\n");
                } else {
                    imprimirEmOrdem(atual->raiz);
                }
                atual = atual->proximo;
                printf("\n");
            }
        }
    }
}

// Função para gerar um número único
// Parâmetros: a tabela hash e o DDD para o qual gerar o número único
// Retorna: o número de telefone único gerado
char* gerarNumeroUnico(HashTable* hashTable, int ddd) {
    char* numero = malloc(10 * sizeof(char));
    numero[0] = '9';

    do {
        ddd = gerarDDD();
        sprintf(numero + 1, "%02d", ddd);

        for (int i = 3; i < 9; i++) {
            numero[i] = '0' + rand() % 10;
        }
        numero[9] = '\0';
    } while (encontrarHashTable(hashTable, numero, ddd));

    return numero;
}

// Função para encontrar uma árvore na tabela hash
// Parâmetros: a tabela hash e o DDD da árvore a ser encontrada
// Retorna: a raiz da árvore AVL correspondente ao DDD fornecido
AVLNode* encontrarArvoreNaTabela(HashTable* hashTable, int ddd) {
    int indice = calcularIndiceHash(ddd);

    // Verificar se o índice está vazio
    if (hashTable->tabela[indice] == NULL)
        return NULL;
    else {
        HashNode* atual = hashTable->tabela[indice];

        // Percorrer a lista encadeada até encontrar o nó com o mesmo DDD
        while (atual != NULL) {
            if (atual->ddd == ddd)
                return atual->raiz;

            atual = atual->proximo;
        }
    }

    return NULL;
}

// Função para imprimir as árvores da tabela hash
// Parâmetros: a tabela hash e a ordem de impressão das árvores (0 para em ordem, 1 para pré-ordem, 2 para pós-ordem)
void imprimirArvores(HashTable* hashTable, int ordenacao) {
    printf("Lista de árvores:\n");

    // Vetor para armazenar os DDDs presentes na tabela hash
    int ddds[HASH_SIZE];
    int count = 0;

    // Percorrer a tabela hash e preencher o vetor de DDDs
    for (int i = 0; i < HASH_SIZE; i++) {
        if (hashTable->tabela[i] != NULL) {
            HashNode* atual = hashTable->tabela[i];
            ddds[count] = atual->ddd;
            count++;
        }
    }

    // Ordenar os DDDs em ordem crescente
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (ddds[j] < ddds[i]) {
                int temp = ddds[i];
                ddds[i] = ddds[j];
                ddds[j] = temp;
            }
        }
    }

    // Percorrer os DDDs em ordem crescente
    for (int i = 0; i < count; i++) {
        int ddd = ddds[i];
        AVLNode* hashNode = encontrarArvoreNaTabela(hashTable, ddd);

        printf("DDD: %d\n", ddd);

        if (hashNode == NULL) {
            printf("Árvore vazia.\n");
        } else {
            if (ordenacao == 0) {
                imprimirEmOrdem(hashNode);
            } else if (ordenacao == 1) {
                imprimirPreOrdem(hashNode);
            } else if (ordenacao == 2) {
                imprimirPosOrdem(hashNode);
            }
        }
        printf("\n");
    }
}

// Função para atualizar os contatos na tabela e árvores 
void atualizarContato(HashTable* hashTable, char* numero, int ddd, char* nome, char* endereco,char* numeroAntigo) {
    removerContato(hashTable,numeroAntigo,ddd);
    inserirContato(hashTable,numero,ddd,nome,endereco);
}