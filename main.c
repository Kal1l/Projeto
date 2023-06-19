#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include "AVL/avlT.h"
#include "hash/hash.h"

int separar_ddd(char* numero){
    int i;char* aux=NULL;
    //copia os dois primeiros elementos
    strncpy(aux,numero,2);
    //converte ddd de string pra int
    int ddd=atoi(aux);
    return ddd;
}

char* numAleatorio(int ddd){
    int i;char num[12];
    //Assegura que cada número gerado será diferente(NÃO TESTEI).
    srand(time(NULL));

    //ddd de int para string
    snprintf(num, sizeof(num), "%d", ddd);
    num[2]='9';

    //Gera 8 número aleatórios
    for (i = 3; i < 12; i++) {
        num[i] = '0' + rand() % 10;
    }
    return num;
}

int novo_num(char* nome,char* numero,char* endereco){

    
}
int main(){
    int opc;
    printf("Seleciona a operacao desejada:\n1-Adiciona novo numero\n2-Remove numero\n3-Busca Aproximada\n4-Listagem de numeros(por ddd)\n");
    return 0;
}