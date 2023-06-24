#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.c"
#include "arvAvl.c"
#include "indices.c"
#include "duplicata.c"

int main() {
    HashTable* tabela = criarHashTable();
    IndiceInvertido* indice=criarIndice();
    HashDup* duplicata = criarHashDup();

    int opcao;
    int ddd;
    char numero[10], nome[50], endereco[100];
    char busca[10]; char numeroAntigo[10];
    
    do {
        int flag=0;
        printf("\n-  Teste -");
        printf("\n1. Inserir novo telefone");
        printf("\n2. Atualizar contato");
        printf("\n3. Pesquisar telefone");
        printf("\n4. Remover telefone");
        printf("\n5. Ver Tabela Hash");
        printf("\n6. Listar numeros de um DDD");
        printf("\n7. Listar todos os numeros por DDD");
        printf("\n8. Busca Aproximada");
        printf("\n9. Gerar Registros Aleatorios");
        printf("\n10. Sair");
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
                printf("OK!\n");
                break;
            case 2:
                printf("Digite o DDD: ");
                scanf("%d", &ddd);
                getchar();
                printf("Digite o nÃºmero do contato que deseja atualizar: ");
                fgets(numeroAntigo, sizeof(numeroAntigo), stdin);
                numeroAntigo[strcspn(numeroAntigo, "\n")] = '\0';
                AVLNode* noP = encontrarHashTable(tabela, numeroAntigo, ddd);
                
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
                    printf("Digite o numero de telefone atualizado: ");
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

                printf("Digite o nome atualizado: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                
                printf("Digite o endereco atualizado: ");
                fgets(endereco, sizeof(endereco), stdin);
                endereco[strcspn(endereco, "\n")] = '\0';
                
                if(atualizarHashDup(duplicata,noP->nome,noP->numero,nome,numero)){
                    flag=1;
                }
                }
                
                atualizarIndice(indice,numero,noP->numero);
                atualizarContato(tabela,numero,ddd,nome,endereco,numeroAntigo);
                printf("CONTATO ATUALIZADO!\n");
                break;
            case 3:
                printf("\nDigite o DDD do numero a ser pesquisado: ");
                scanf("%d", &ddd);
                getchar();

                printf("\nDigite o numero de telefone a ser pesquisado: ");
                fgets(numero, sizeof(numero), stdin);
                numero[strcspn(numero, "\n")] = '\0';

                AVLNode* noS = encontrarHashTable(tabela, numero, ddd);
                if(noS != NULL){
                    printf("\n---CONTADO ENCONTRADO---\n");
                    printf("Numero: %s\n", noS->numero);
                    printf("Nome: %s\n", noS->nome);
                    printf("Endereco: %s\n", noS->endereco);

                }
                else{
                    printf("Contato nao encontrado!\n");
                }
                break;
            case 4:
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
                    removerHashDup(duplicata, noS->nome, numero);
                    printf("\nNumero excluido com sucesso!\n");
                } else {
                    printf("\nNumero nao encontrado :(\n");
                }
                break;
            case 5:
                imprimirTabelaHash(tabela);
                break;
            case 6:
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
            case 7:
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
            case 8:
                printf("\nDigite o numero a ser pesquisado: ");
                fgets(busca,sizeof(busca), stdin);
                busca[strcspn(busca, "\n")] = '\0';
                BuscaAproximada(indice,busca);
                break;
            case 9:
                gerarUsuariosAleatorios(tabela,100, indice);
                printf("\nRegistros criados com sucesso");
                break;
            case 10:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpcao invalida. Por favor, escolha uma opcao valida.\n");
                break;
        }
    } while (opcao != 10);

    return 0;
} 