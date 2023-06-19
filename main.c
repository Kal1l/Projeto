#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>

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

