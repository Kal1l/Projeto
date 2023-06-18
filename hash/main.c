#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"hash.c"

int main(){
    Hash *ha = criaHash(13);
    struct arvore a1, a2, a3, a4, a5;
    a1.ddd = 85;
    strcpy(a1.regiao, "Ceará (Fortaleza)");
    a2.ddd = 11;
    strcpy(a2.regiao, "São Paulo (Capital)");
    a3.ddd = 81;
    strcpy(a3.regiao, "Recife");
    a4.ddd = 21;
    strcpy(a4.regiao, "Rio de Janeiro (Capital)");
    a5.ddd = 7; // usei o 7 apenas para colidir com o 85 do Ceará
    strcpy(a5.regiao, "Minas Gerais (Belo Horizonte)");

    insereHash_EncSep(ha, a1);
    insereHash_EncSep(ha, a2);
    insereHash_EncSep(ha, a3);
    insereHash_EncSep(ha, a4);
    insereHash_EncSep(ha, a5);
    imprimeHash(ha);
    buscaHash_EncSep(ha, 85);
    buscaHash_EncSep(ha, 54);
    buscaHash_EncSep(ha, 31);
    buscaHash_EncSep(ha, 7);

    liberaHash(ha);

    return 0;
}
