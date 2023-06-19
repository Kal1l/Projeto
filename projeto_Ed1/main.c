#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.c"
#include "ddd.c"

void preencheTabelaHash(Hash* ha) {
    for (int i = 0; i < 66; i++) {
        insereHash_EncSep(ha, ddds[i]);
    }
}


int main(){
    Hash *ha = criaHash(67);
    preencheTabelaHash(ha);
    imprimeHash(ha);
    liberaHash(ha);

    return 0;
}
