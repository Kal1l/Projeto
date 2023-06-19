#include <stdio.h>
#include "avlT.c"

int main() {
    avlT* arvore = cria_avlT();

    inserir_no(arvore, "123", "João", "Rua A");
    inserir_no(arvore, "456", "Maria", "Rua B");
    inserir_no(arvore, "789", "Pedro", "Rua C");

    printf("Imprimindo em ordem:\n");
    imprimir_emOrdem(*arvore);

    remover_no(*arvore, "456");

    printf("\nImprimindo em ordem após remover o nó com número 456:\n");
    imprimir_emOrdem(*arvore);

    liberar_avlT(*arvore);

    return 0;
}
