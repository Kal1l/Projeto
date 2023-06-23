#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 67


typedef struct AVLNode {
    char numero[10];
    char nome[50];
    char endereco[100];
    int altura;
    struct AVLNode* esquerda;   
    struct AVLNode* direita;
} AVLNode;

typedef struct HashNode {
    int ddd;
    AVLNode* raiz;
    struct HashNode* proximo;
} HashNode;

typedef struct HashTable {
    int tamanho;
    HashNode** tabela;
} HashTable;

// Estrutura de um nó da lista encadeada do índice invertido
typedef struct IndiceNode {
    char numero[10];
    struct Node* proximo;
} IndiceNode;

AVLNode* encontrarArvoreNaTabela(HashTable* hashTable, int ddd);//?

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
//indice invertido
typedef struct {
    char numeroTelefone[10];  // Estrutura para armazenar o número de telefone
} EntradaTelefone;

typedef struct {
    EntradaTelefone entradas[10000];  // Array de entradas telefônicas
    int quantidadeEntradas;  // Contador para controlar a quantidade de entradas
} IndiceInvertido;

IndiceInvertido* criarIndice(){
    IndiceInvertido* indice=(IndiceInvertido*)malloc(sizeof(IndiceInvertido));
    indice->quantidadeEntradas=0;
    return indice;
}
void adicionarIndice(IndiceInvertido *indice, char *numeroTelefone) {
    if (indice->quantidadeEntradas < 10000) {
        // Copia o número de telefone para a próxima posição disponível do array
        strcpy(indice->entradas[indice->quantidadeEntradas].numeroTelefone, numeroTelefone);
        indice->quantidadeEntradas++;  // Incrementa o contador de entradas
    } else {
        printf("O índice está cheio. Não é possível adicionar mais entradas.\n");
    }
}
void removerIndice(IndiceInvertido *indice, const char *numeroTelefone) {
    int i, j;

    for (i = 0; i < indice->quantidadeEntradas; i++) {
        if (strcmp(indice->entradas[i].numeroTelefone, numeroTelefone) == 0) {

            // Desloca as entradas subsequentes para preencher o espaço vazio da entrada removida
            for (j = i; j < indice->quantidadeEntradas - 1; j++) {
                strcpy(indice->entradas[j].numeroTelefone, indice->entradas[j + 1].numeroTelefone);
            }

            indice->quantidadeEntradas--;  // Decrementa o contador de entradas
            break;
        }
    }
}

HashNode* criarHashNode(int ddd,AVLNode* raiz){
    HashNode* novoNo=(HashNode*)malloc(sizeof(HashNode));
    novoNo->ddd=ddd;
    novoNo->raiz=raiz;
    novoNo->proximo=NULL;
    return novoNo;
}
HashTable* criarHashTable() {
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    hashTable->tamanho=HASH_SIZE;
    hashTable->tabela = (HashNode**)calloc(HASH_SIZE , sizeof(HashNode*));
    return hashTable;
}
int calcularIndiceHash(int ddd) {
    return ddd  % HASH_SIZE;
}

// Função para inserir um valor na tabela hash
void inserirContato(HashTable* hashTable, const char* numero,int ddd,const char* nome, const char* endereco) {
    int indice = calcularIndiceHash(ddd);
    // Verificar se o índice está vazio
    if(hashTable->tabela[indice]==NULL){
        AVLNode* raiz=inserir(NULL,numero,nome,endereco);
        hashTable->tabela[indice]=criarHashNode(ddd,raiz);
    }else{
        HashNode* atual=hashTable->tabela[indice];
        // Percorrer a lista encadeada até encontrar um nó com o mesmo DDD
        while(atual->proximo!=NULL && atual->ddd!=ddd)
            atual=atual->proximo;

         // Caso já exista um nó com o mesmo DDD
        if(atual->ddd==ddd)
            atual->raiz=inserir(atual->raiz,numero,nome,endereco);
        else{
            AVLNode* raiz=inserir(NULL,numero,nome,endereco);
            HashNode* novoNo=criarHashNode(ddd,raiz);
            atual->proximo=novoNo;
        }
    }
    printf("OK!\n");
}

// Função para deletar um valor da tabela hash
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
                printf("Altura da arvore antes da remocao: %d\n", altura(arvoreAntes));
                printf("Altura da arvore depois da remocao: %d\n", altura(arvoreDepois));
                
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
AVLNode* encontrarHashTable(HashTable* hashTable, const char* numero, int ddd) {
    int indice = calcularIndiceHash(ddd);

    // Verificar se o índice está vazio
    if (hashTable->tabela[indice] == NULL)
        return NULL;
    else {
        HashNode* atual=hashTable->tabela[indice];
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
void imprimirTabelaHash(HashTable* hashTable) {
    printf("Tabela Hash:\n");

    for (int i = 0; i < HASH_SIZE; i++) {
        printf("Posicao %d:\n", i);

        if (hashTable->tabela[i] == NULL) {
            printf("Usuarios nao encontrados.\n\n");
        } else {
            HashNode* atual = hashTable->tabela[i];

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
char* gerarNumeroUnico(HashTable* hashTable,int ddd){
    char* numero = malloc(10 * sizeof(char));
    numero[0]='9';
    do{
         for (int i = 1; i < 9; i++) {
            numero[i] = '0' + rand() % 10;
        }
        numero[9]='\0';
    }while(encontrarHashTable(hashTable,numero,ddd));
    return numero;
}
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

void imprimirArvores(HashTable* hashTable, int ordenacao) {
    printf("Lista de arvores:\n");

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

        if (hashNode != NULL) {
            printf("DDD: %d\n", ddd);  // Exibir o DDD da árvore

            AVLNode* raiz = hashNode;

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
void BuscaAproximada(IndiceInvertido *indice, char *consulta) {
    int i;

    for (i = 0; i < indice->quantidadeEntradas; i++) {
        char *correspondencia = strstr(indice->entradas[i].numeroTelefone, consulta);
        if (correspondencia != NULL) {
            printf("Numero encontrados: %s\n", indice->entradas[i].numeroTelefone);
        }
        else{
            printf("Nenhum numero encontrado.");
        }
    }
}

int main() {
    HashTable* tabela = criarHashTable();
    IndiceInvertido* indice=criarIndice();

    int opcao;
    int ddd;
    char numero[10], nome[50], endereco[100];
    char* busca=(char*)malloc(10*sizeof(char));
    do {
        printf("\n-  Teste -");
        printf("\n1. Inserir novo telefone");
        printf("\n2. Pesquisar telefone");
        printf("\n3. Remover telefone");
        printf("\n4. Ver Tabela Hash");
        printf("\n5. Listar numeros de um DDD");
        printf("\n6. Listar todos os numeros por DDD");
        printf("\n7. Sair");
        printf("\n\nDigite a opcao desejada: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Digite o DDD: ");
                scanf("%d", &ddd);
                getchar();

                char* num1=malloc(9 * sizeof(char));
                char* num2=malloc(9 * sizeof(char));
                char* num3=malloc(9 * sizeof(char));
                
                num1=gerarNumeroUnico(tabela,ddd);
                num2=gerarNumeroUnico(tabela,ddd);
                num3=gerarNumeroUnico(tabela,ddd);
                char op_num;

                printf("Selecione um dos numeros abaixo(Para inserir o numero voce mesmo, insira qualquer outro valor):\n");
                printf("1-%s;\n",num1);
                printf("2-%s;\n",num2);
                printf("3-%s;\n",num3);
                scanf(" %c", &op_num);
                getchar();
                
                if(op_num=='1'){ 
                    strcpy(numero,num1);
                }else if(op_num=='2'){
                    strcpy(numero,num2);
                }else if(op_num=='3'){
                    strcpy(numero,num3);
                }else{
                    printf("Digite o numero de telefone: ");
                    fgets(numero,10, stdin);
                    numero[strcspn(numero, "\n")] = '\0';
                    getchar();
                }
                free(num1);
                num1=NULL;
                free(num2);
                num2=NULL;
                free(num3);
                num3=NULL;

                printf("Digite o nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                
                printf("Digite o endereco: ");
                fgets(endereco, sizeof(endereco), stdin);
                endereco[strcspn(endereco, "\n")] = '\0';

                inserirContato(tabela, numero, ddd, nome, endereco);
                adicionarIndice(indice,numero);
                break;
            case 2:
                printf("\nDigite o DDD do numero a ser pesquisado: ");
                scanf("%d", &ddd);
                getchar();

                printf("\nDigite o numero de telefone a ser pesquisado: ");
                fgets(numero, sizeof(numero), stdin);
                numero[strcspn(numero, "\n")] = '\0';

                AVLNode* noP = encontrarHashTable(tabela, numero, ddd);
                if(noP != NULL){
                    printf("\n---CONTADO ENCONTRADO---\n");
                    printf("Numero: %s\n", noP->numero);
                    printf("Nome: %s\n", noP->nome);
                    printf("Endereco: %s\n", noP->endereco);

                }
                else{
                    printf("Contato não encontrado!\n");
                }
                break;
            case 3:
                printf("\nDigite o DDD do numero a ser removido: ");
                scanf("%d", &ddd);
                getchar();

                printf("\nDigite o numero de telefone a ser removido: ");
                fgets(numero, sizeof(numero), stdin);
                numero[strcspn(numero, "\n")] = '\0';

                removerContato(tabela, numero, ddd);
                AVLNode* noE = encontrarHashTable(tabela, numero, ddd);
                if(noE == NULL){
                    removerIndice(indice,numero);
                    printf("\nNumero excluido com sucesso!\n");
                } else {
                    printf("\nNumero nao encontrado :(\n");
                }
                break;
            case 4:
                printf("---Tabela Hash---");
                imprimirTabelaHash(tabela);
                break;
            case 5:
                printf("Digite o DDD: ");
                scanf("%d", &ddd);
                getchar();
                AVLNode* arvore = encontrarArvoreNaTabela(tabela, ddd);
    
                if (arvore == NULL)
                    printf("Arvore nao encontrada para o DDD especificado.\n");
                else {
                    printf("\nArvore encontrada para o DDD %d.\n", ddd);
                    int opcao;

                    do{
                        printf("Deseja lista-la em: \n");
                        printf("\n1. Pre-Ordem");
                        printf("\n2. Em-Ordem");
                        printf("\n3. Pos-Ordem");
                        printf("\n4. Sair para o Menu principal\n");
                        scanf("%d", &opcao);
                
                        switch (opcao)
                        {
                            case 1:
                            imprimirPreOrdem(arvore);
                            break;
                            case 2:
                            imprimirEmOrdem(arvore);
                            break;
                            case 3:
                            imprimirPosOrdem(arvore);
                            default:
                            printf("\nOpcao invalida. Por favor, escolha uma opcao valida.\n");
                            break;
                        }
                    } while(opcao != 4);
                }
                break;
            case 6:
                printf("Escolha uma das opcoes de listagem\n");
                int opcao;

                do{
                    printf("\n1. Listar os contatos por numero");
                    printf("\n2. Listar os contatos por nome");
                    printf("\n3. Sair para o Menu principal\n");
                    scanf("%d", &opcao);
                    
                    switch (opcao)
                    {
                    case 1:
                        imprimirArvores(tabela, 1);
                        break;
                    case 2:
                        imprimirArvores(tabela, 2);
                        break;
                    default:
                        printf("\nOpcao invalida. Por favor, escolha uma opcao valida.\n");
                        break;
                    }
                } while(opcao != 3);
                break;
            case 7:
                printf("\nDigite o numero a ser pesquisado: ");
                fgets(busca, sizeof(strlen(busca)), stdin);
                busca[strcspn(busca, "\n")] = '\0';
                BuscaAproximada(indice,busca);
                break;
            case 8:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpcao invalida. Por favor, escolha uma opcao valida.\n");
                break;
        }
    } while (opcao != 8);

    return 0;
} 