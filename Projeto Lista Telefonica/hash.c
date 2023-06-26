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
HashNo* criarHashNo(int ddd, AVLNo* raiz) {
    HashNo* novoNo = (HashNo*)malloc(sizeof(HashNo));
    novoNo->ddd = ddd;
    novoNo->raiz = raiz;
    novoNo->proximo = NULL;
    return novoNo;
}

// Função para criar uma tabela hash vazia
TabelaHash* criarTabelaHash() {
    TabelaHash* tabelaHash = (TabelaHash*)malloc(sizeof(TabelaHash));
    tabelaHash->tamanho = HASH_SIZE;
    tabelaHash->tabela = (HashNo**)calloc(HASH_SIZE, sizeof(HashNo*));
    return tabelaHash;
}

// Função para calcular o índice da tabela hash para um determinado DDD
// Parâmetro: ddd - o DDD para o qual calcular o índice
// Retorna: o índice calculado
int calcularIndiceHash(int ddd) {
    return ddd % HASH_SIZE;
}
// Função de hashing pelo método da multiplicação
int hashMult(int ddd) {
    double A = 0.6180339887; // Constante de multiplicação (valor irracional)
    double val = ddd * A;
    val -= (int)val; // Extrair parte fracionária
    int hash = (int)(HASH_SIZE * val); // Multiplicar pela tabela hash size
    return hash;
}
// Função de hashing pelo método da dobra
int hashDobra(int ddd) {
    int hash = 0; 
    // Converter a chave em uma sequência de dígitos
    char dddStr[20];
    sprintf(dddStr, "%d", ddd);
    int len = strlen(dddStr);
    int meioTam = len / 2;
    // Somar os dígitos em pares (da esquerda para a direita)
    for (int i = 0; i < meioTam; i++) {
        int soma = (dddStr[i] - '0') + (dddStr[len - i - 1] - '0');
        hash += soma;
    }
    // Se a chave possuir um número ímpar de dígitos, somar o dígito do meio
    if (len % 2 != 0) {
        hash += dddStr[meioTam] - '0';
    }
    // Aplicar o módulo para obter o valor dentro do intervalo da tabela hash
    hash %= HASH_SIZE;
    return hash;
}

// Função para inserir um contato na tabela hash
// Parâmetros: a tabela hash, o número de telefone do contato, o DDD do contato, o nome do contato e o endereço do contato
void inserirContato(TabelaHash* tabelaHash, const char* numero, int ddd, const char* nome, const char* endereco) {
    int indice = calcularIndiceHash(ddd);
    //int indice= hashMult(ddd);
    //int indice=hashDobra(ddd);

    // Verificar se o índice está vazio
    if (tabelaHash->tabela[indice] == NULL) {
        AVLNo* raiz = inserir(NULL, numero, nome, endereco);
        tabelaHash->tabela[indice] = criarHashNo(ddd, raiz);
    } else {
        HashNo* atual = tabelaHash->tabela[indice];

        // Percorrer a lista encadeada até encontrar um nó com o mesmo DDD
        while (atual->proximo != NULL && atual->ddd != ddd) {
            atual = atual->proximo;
        }

        // Caso já exista um nó com o mesmo DDD
        if (atual->ddd == ddd) {
            atual->raiz = inserir(atual->raiz, numero, nome, endereco);
        } else {
            AVLNo* raiz = inserir(NULL, numero, nome, endereco);
            HashNo* novoNo = criarHashNo(ddd, raiz);
            atual->proximo = novoNo;
        }
    }
}

// Função para remover um contato da tabela hash
// Parâmetros: a tabela hash, o número de telefone do contato e o DDD do contato
void removerContato(TabelaHash* tabelaHash, const char* numero, int ddd) {
    int indice = calcularIndiceHash(ddd);
    //int indice= hashMult(ddd);
    //int indice=hashDobra(ddd);

    // Verificar se o índice está vazio
    if (tabelaHash->tabela[indice] == NULL)
        return;
    else {
        HashNo* atual = tabelaHash->tabela[indice];
        HashNo* anterior = NULL;

        // Percorrer a lista encadeada até encontrar um nó com o mesmo DDD
        while (atual != NULL) {
            if (atual->ddd == ddd) {
                AVLNo* arvoreAntes = encontrarArvoreNaTabela(tabelaHash, ddd);
                atual->raiz = removerNo(atual->raiz, numero);
                AVLNo* arvoreDepois = encontrarArvoreNaTabela(tabelaHash, ddd);

                // Exibir a altura da árvore antes e depois da remoção
                printf("Altura da arvore antes da remocao: %d\n", altura(arvoreAntes));
                printf("Altura da arvore depois da remocao: %d\n", altura(arvoreDepois));

                // Se a árvore AVL estiver vazia, remover o nó da lista
                if (atual->raiz == NULL) {
                    if (anterior == NULL) {
                        tabelaHash->tabela[indice] = atual->proximo;
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
void gerarUsuariosAleatorios(TabelaHash* tabelaHash, int quantidade, IndiceInvertido* indice) {
    const char* nomes[] = {"Alicia", "Francisco", "Carlos", "Davi", "Eva", "Kalil", "Graça", "Henrique", "Ivy", "Jackson"};
    const char* sobrenomes[] = {"Santos", "Rodrigues", "Amaral", "Jones", "Silva", "Davis", "Miller", "Wilson", "Moreira", "Holanda"};
    const char* enderecos[] = {"Rua Goiania", "Vila Arraial", "Jangurussu", "Praca D", "Estrada E", "Avenida F", "Rua G", "Travessa H", "Rua I", "Avenida J"};

    for (int i = 0; i < quantidade; i++) {
        int ddd_index = rand() % num_ddds_brasileiros;  // Escolhe um índice aleatório para o DDD brasileiro
        int ddd = ddds_brasileiros[ddd_index];         // Obtém o DDD correspondente ao índice aleatório

        const char* nome = nomes[rand() % 10];
        const char* sobrenome = sobrenomes[rand() % 10];
        const char* endereco = enderecos[rand() % 10];

        char* numero = gerarNumeroUnico(tabelaHash, ddd);

        char nomeCompleto[60];
        snprintf(nomeCompleto, sizeof(nomeCompleto), "%s %s", nome, sobrenome);

        inserirContato(tabelaHash, numero, ddd, nomeCompleto, endereco);
        adicionarIndice(indice, numero);
    }
}

// Busca sequencial
AVLNo* buscaSequencial(TabelaHash* tabelaHash, int ddd,char* numero) {
    int indice = calcularIndiceHash(ddd);
    //int indice= hashMult(ddd);
    //int indice=hashDobra(ddd);

    // Verificar se o índice está vazio
    if (tabelaHash->tabela[indice] == NULL)
        return NULL;
    else {
        HashNo* atual = tabelaHash->tabela[indice];

        // Percorrer a lista encadeada até encontrar um nó com o mesmo DDD
        while (atual != NULL) {
            if (atual->ddd == ddd) {
                AVLNo* resultado = encontrarNo(atual->raiz,numero);
                return resultado;
            }
            atual = atual->proximo;
        }
    }

    return NULL;
}
// Função para encontrar um nó na tabela hash
// Parâmetros: a tabela hash, o número de telefone do contato e o DDD do contato
// Retorna: o nó da árvore AVL correspondente ao número de telefone e DDD fornecidos
AVLNo* encontrarContato(TabelaHash* tabelaHash, const char* numero, int ddd) {
    int indice = calcularIndiceHash(ddd);
    //int indice= hashMult(ddd);
    //int indice=hashDobra(ddd);

    // Verificar se o índice está vazio
    if (tabelaHash->tabela[indice] == NULL)
        return NULL;
    else {
        HashNo* atual = tabelaHash->tabela[indice];

        // Percorrer a lista encadeada até encontrar um nó com o mesmo DDD
        while (atual != NULL) {
            if (atual->ddd == ddd) {
                AVLNo* resultado = encontrarNo(atual->raiz, numero);
                if (resultado != NULL)
                    return resultado;
            }
            atual = atual->proximo;
        }
    }
    return NULL;
}

// Função para imprimir a tabela hash
// Passa a tabela como parâmetr
void imprimirTabelaHash(TabelaHash* tabelaHash) {
    printf("Tabela Hash:\n");

    for (int i = 0; i < HASH_SIZE; i++) {
        printf("Posicao %d:\n", i);

        if (tabelaHash->tabela[i] == NULL) {
            printf("Usuarios nao encontrados.\n\n");
        } else {
            HashNo* atual = tabelaHash->tabela[i];

            while (atual != NULL) {
                printf("DDD: %d\n", atual->ddd);
                if (atual->raiz == NULL) {
                    printf("Usuarios nao encontrados.\n");
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
char* gerarNumeroUnico(TabelaHash* tabelaHash, int ddd) {
    char* numero = malloc(10 * sizeof(char));
    numero[0] = '9';

    do {
        ddd = gerarDDD();
        sprintf(numero + 1, "%02d", ddd);

        for (int i = 3; i < 9; i++) {
            numero[i] = '0' + rand() % 10;
        }
        numero[9] = '\0';
    } while (encontrarContato(tabelaHash, numero, ddd));

    return numero;
}

// Função para encontrar uma árvore na tabela hash
// Parâmetros: a tabela hash e o DDD da árvore a ser encontrada
// Retorna: a raiz da árvore AVL correspondente ao DDD fornecido
AVLNo* encontrarArvoreNaTabela(TabelaHash* tabelaHash, int ddd) {
    int indice = calcularIndiceHash(ddd);
    //int indice= hashMult(ddd);
    //int indice=hashDobra(ddd);

    // Verificar se o índice está vazio
    if (tabelaHash->tabela[indice] == NULL)
        return NULL;
    else {
        HashNo* atual = tabelaHash->tabela[indice];

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
// Parâmetros: a tabela hash e a ordem de impressão das árvores (1 para ordenar por número, 2 para ordenar por nome)
void imprimirArvores(TabelaHash* tabelaHash, int ordenacao) {
    printf("Lista de arvores:\n");

    // Vetor para armazenar os DDDs presentes na tabela hash
    int ddds[HASH_SIZE];
    int cont = 0;

    // Percorrer a tabela hash e preencher o vetor de DDDs
    for (int i = 0; i < HASH_SIZE; i++) {
        if (tabelaHash->tabela[i] != NULL) {
            HashNo* atual = tabelaHash->tabela[i];
            ddds[cont] = atual->ddd;
            cont++;
        }
    }

    // Ordenar os DDDs em ordem crescente
    for (int i = 0; i < cont - 1; i++) {
        for (int j = i + 1; j < cont; j++) {
            if (ddds[j] < ddds[i]) {
                int temp = ddds[i];
                ddds[i] = ddds[j];
                ddds[j] = temp;
            }
        }
    }

    // Percorrer os DDDs em ordem crescente
    for (int i = 0; i < cont; i++) {
        int ddd = ddds[i];
        AVLNo* hashNo = encontrarArvoreNaTabela(tabelaHash, ddd);

        if (hashNo != NULL) {
            printf("DDD: %d\n", ddd);  // Exibir o DDD da árvore

            AVLNo* raiz = hashNo;

            if (ordenacao == 1) {
                printf("Ordenacao por numero de telefone (Em-ordem):\n");
                imprimirEmOrdem(raiz);
            } else if (ordenacao == 2) {
                printf("Ordenacao por nome de usuario:\n");
                imprimirPorNomeOrdenado(raiz);
            }
            printf("\n");
        }
    }
}

// Função para atualizar os contatos na tabela e árvores 
void atualizarContato(TabelaHash* tabelaHash, char* numero, int ddd, char* nome, char* endereco,char* numeroAntigo) {
    removerContato(tabelaHash,numeroAntigo,ddd);
    inserirContato(tabelaHash,numero,ddd,nome,endereco);
}
