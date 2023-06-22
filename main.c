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
    int ddd,regiao;
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
        hashTable[i].regiao = NULL;
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
    hashTable[indice].regiao=ddd;
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
            printf("Usuarios nao encontrados.\n\n");
        } else {
            printf("DDD:%d\n",hashTable[i].regiao);
            imprimirEmOrdem(hashTable[i].raiz);
            printf("\n");
        }
    }
}
char* gerarNumeroUnico(HashTable* hashTable,int ddd){
    char* numero = malloc(9 * sizeof(char));
    numero[0]='9';
    do{
         for (int i = 1; i < 9; i++) {
            numero[i] = '0' + rand() % 10;
        }
        numero[9]='\0';
    }while(encontrarHashTable(hashTable,numero,ddd));
    return numero;
}


int main() {
    HashTable tabela[HASH_SIZE];
    int i;

    for (i = 0; i < HASH_SIZE; i++) {
        tabela[i].ddd = i + 1;
        tabela[i].raiz = NULL;
    }

    int opcao;
    int ddd;
    char numero[10], nome[50], endereco[100];

    do {
        printf("-  Teste -");
        printf("\n1. Inserir novo telefone");
        printf("\n2. Pesquisar telefone");
        printf("\n3. Remover telefone");
        printf("\n4. Ver Tabela Hash");
        printf("\n5. Sair");
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
                    fgets(numero, sizeof(numero), stdin);
                    numero[strcspn(numero, "\n")] = '\0';
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

                inserirHashTable(tabela, numero, ddd, nome, endereco);
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
                break;
            case 3:
                printf("\nDigite o DDD do numero a ser removido: ");
                scanf("%d", &ddd);
                getchar();

                printf("\nDigite o numero de telefone a ser removido: ");
                fgets(numero, sizeof(numero), stdin);
                numero[strcspn(numero, "\n")] = '\0';

                removerHashTable(tabela, numero, ddd);
                AVLNode* noE = encontrarHashTable(tabela, numero, ddd);
                if(noE == NULL){
                    printf("\nNumero excluído com sucesso!\n");
                } else {
                    printf("\nNumero nao encontrado :(\n");
                }
                break;
            case 4:
                printf("---Tabela Hash---");
                imprimirTabelaHash(tabela);
                break;
            case 5:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpcao invalida. Por favor, escolha uma opcao valida.\n");
                break;
        }
    } while (opcao != 5);

    return 0;
} 
