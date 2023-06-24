#ifndef INDICES_H
#define INDICES_H
typedef struct {
    char numeroTelefone[10];  // Estrutura para armazenar o número de telefone
} EntradaTelefone;
typedef struct {
    EntradaTelefone entradas[10000];  // Array de entradas telefônicas
    int quantidadeEntradas;  // Contador para controlar a quantidade de entradas
} IndiceInvertido;
IndiceInvertido* criarIndice();
void adicionarIndice(IndiceInvertido *indice, char *numeroTelefone);
void removerIndice(IndiceInvertido *indice, const char *numeroTelefone);
void BuscaAproximada(IndiceInvertido *indice, char *consulta) ;
#endif