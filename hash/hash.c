#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"hash.h"

struct hash{
    int qtd, TABLE_SIZE;
    struct arvore **itens;
};

Hash* criaHash(int tamanho){
    Hash* ha = (Hash*)malloc(sizeof(Hash));
    if(ha != NULL){
        ha->TABLE_SIZE = tamanho;
        ha->itens = (struct arvore**)malloc(tamanho*sizeof(struct arvore*));
        if(ha->itens == NULL){
            free(ha);
            return NULL;
        }
        ha->qtd = 0;
        for(int i = 0; i<ha->TABLE_SIZE; i++)
            ha->itens[i] = NULL;
    }
    return ha;
}

void liberaHash(Hash* ha){
    if(ha != NULL){
        for(int i = 0; i<ha->TABLE_SIZE; i++){
            if(ha->itens[i] != NULL)
                free(ha->itens[i]);
        }
        free(ha->itens);
        free(ha);
    }
}

int chaveDivisao(int chave, int TABLE_SIZE){
    return (chave & 0x7FFFFFFF) % TABLE_SIZE;
}

int valorString(char *str){
    int valor = 7;
    int tam = strlen(str);
    for(int i = 0; i<tam; i++)
        valor = 31 * valor + (int) str[i];
    return valor;
}

int insereHash_EncSep(Hash* ha, struct arvore ar){
    if(ha == NULL || ha->qtd == ha->TABLE_SIZE)
        return 0;

    int chave = ar.ddd;
    int pos = chaveDivisao(chave, ha->TABLE_SIZE);
    struct arvore* novo = (struct arvore*)malloc(sizeof(struct arvore));
    if(novo == NULL)
       return 0;
    *novo = ar;
    novo->prox = NULL;
    if(ha->itens[pos] == NULL){
        ha->itens[pos] = novo;
    }else{
        struct arvore* aux = ha->itens[pos];
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
    ha->qtd++;
    return 1;
}

int buscaHash_EncSep(Hash* ha, int mat){
    if(ha == NULL){
       printf("Erro: Tabela Hash não criada!\n");
       return 0;
    }
    int pos = chaveDivisao(mat, ha->TABLE_SIZE);
    if(ha->itens[pos] == NULL){
        printf("DDD: %d não encontrado(a) na tabela!\n", mat);
        return 0;
    }
    struct arvore* aux = ha->itens[pos];
    while(aux != NULL){
        if(mat == aux->ddd){
           printf("\n===DDD ENCONTRADO===\n");
            printf("Posição: %d\n", pos);
            printf("DDD: %d\n", aux->ddd);
            printf("Região: %s\n", aux->regiao);
             printf("-----------------\n\n");
            return 1;
        }
        aux = aux->prox;

    }
    return 0;
}

void imprimeHash(Hash* ha){
    if(ha == NULL){
        printf("Erro: Tabela Hash não criada!\n");
        return ;
    }
    if(ha->qtd == 0){
        printf("Erro: Tabela Hash vazia!\n");
        return;
    }
    printf("\n====TABELA HASH====\n");
    for(int i = 0; i<ha->TABLE_SIZE; i++){
        printf("Posição: %d\n", i);
        struct arvore *aux = ha->itens[i];
        while(aux != NULL){
            printf("DDD: %d\n", aux->ddd);
            printf("Região: %s\n", aux->regiao);
            printf("\n");
            aux = aux->prox;
        }
        printf("-------------------\n");
    }

}

