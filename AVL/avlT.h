#ifndef AVLT_H
#define AVLT_H

typedef struct No* avlT;

avlT* cria_avlT();
int altura(struct No* no);
int inserir_no(avlT* raiz, char* numero, char* nome, char* endereco);
struct No* buscar_no(struct No* raiz, char* numero);
struct No* remover_no(struct No* raiz, char* numero);
void imprimir_preOrdem(struct No* raiz);
void imprimir_emOrdem(struct No* raiz);
void imprimir_posOrdem(struct No* raiz);
void liberar_avlT(struct No* raiz);

#endif
