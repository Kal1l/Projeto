#ifndef AVLT_H
#define AVLT_H

typedef struct No* avlT;

avlT* cria_avlT();
int altura(No*no);
int inserir_no(avlT*raiz,char* numero, char* nome, char* endereco);//*
No* buscar_no(No*raiz,char* numero);
No* remover_no(No*raiz,char* numero);
void imprimir_preOrdem(No *raiz);
void imprimir_emOrdem(No *raiz);
void imprimir_posOrdem(No *raiz);
void liberar_avlT(No*raiz);
#endif