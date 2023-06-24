#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.c"
#include "arvAvl.c"
#include "indices.c"
#include "duplicata.c"
/*typedef struct Registro {
    char dado[50];
    struct Registro* prox;
} Registro;
typedef struct HashDup {
    Registro* tabela[20000];
} HashDup;
// Função hash
int valorString(char *str){
    int i;int valor=7;
    int tam = strlen(str);
    for (i=0;i<tam;i++)
        valor= 31 * valor + (int)str[i];
    return valor;
}
HashDup* criarHashDup() {
    HashDup* hashDup = malloc(sizeof(HashDup));
    for (int i = 0; i < 20000; i++) {
        hashDup->tabela[i] = NULL;
    }
    return hashDup;
}
int inserirHashDup(HashDup* hashDup, char* dado) {
    int indice = hash(dado);

    // Verifica se já existe uma duplicata
    Registro* atual = hashDup->tabela[indice];
    while (atual != NULL) {
        if (strcmp(atual->dado, dado) == 0) {
            printf("Duplicata encontrada: %s\n", dado);
            return 0;
        }
        atual = atual->prox;
    }

    // Cria um novo nó para o elemento
    Registro* novo = malloc(sizeof(Registro));
    strcpy(novo->dado, dado);
    novo->prox = hashDup->tabela[indice];
    hashDup->tabela[indice] = novo;
    return 1;
}

void removerHashDup(HashDup* hashDup, char* dado) {
    int indice = hash(dado);

    Registro* atual = hashDup->tabela[indice];
    Registro* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dado, dado) == 0) {
            if (anterior == NULL) {
                hashDup->tabela[indice] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            printf("Elemento removido: %s\n", dado);
            return;
        }

        anterior = atual;
        atual = atual->prox;
    }

    printf("Elemento não encontrado: %s\n", dado);
}*/
int main() {
    HashTable* tabela = criarHashTable();
    IndiceInvertido* indice=criarIndice();
    HashDup* duplicata = criarHashDup();

    int opcao;
    int ddd;
    char numero[10], nome[50], endereco[100];
    char busca[10];
    
    do {
        int flag=0;
        printf("\n-  Teste -");
        printf("\n1. Inserir novo telefone");
        printf("\n2. Pesquisar telefone");
        printf("\n3. Remover telefone");
        printf("\n4. Ver Tabela Hash");
        printf("\n5. Listar numeros de um DDD");
        printf("\n6. Listar todos os numeros por DDD");
        printf("\n7. Busca Aproximada");
        printf("\n8. Sair");
        printf("\n\nDigite a opcao desejada: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Digite o DDD: ");
                scanf("%d", &ddd);
                getchar();
                
                while(flag==0){
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
                if(insereHashDup(duplicata, nome, numero) ==1){
                    flag=1;
                }
                }
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
                    printf("Contato nÃ£o encontrado!\n");
                }
                break;
            case 3:
                printf("\nDigite o DDD do numero a ser removido: ");
                scanf("%d", &ddd);
                getchar();

                printf("\nDigite o numero de telefone a ser removido: ");
                fgets(numero, sizeof(numero), stdin);
                numero[strcspn(numero, "\n")] = '\0';

                AVLNode* noE = encontrarHashTable(tabela, numero, ddd);
                if (noE != NULL) {
                    removerContato(tabela, numero, ddd);
                    removerIndice(indice, numero);
                    removerHashDup(duplicata, noE->nome, numero);
                    printf("\nNumero excluido com sucesso!\n");
                } else {
                    printf("\nNumero nao encontrado :(\n");
                }
                break;
            case 4:
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
                            break;
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
                fgets(busca,sizeof(busca), stdin);
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