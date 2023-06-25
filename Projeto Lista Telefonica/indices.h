#ifndef INDICES_H
#define INDICES_H
#define MAX_SIZE 10000

// Definição da estrutura para armazenar o número de telefone
typedef struct {
    char numeroTelefone[10];  
} EntradaTelefone;

// Definição da estrutura do indice invertido
typedef struct {
    EntradaTelefone entradas[MAX_SIZE];  // Array de entradas telefônicas
    int quantidadeEntradas;  // Contador para controlar a quantidade de entradas
} IndiceInvertido;

// Cria um novo índice invertido vazio
IndiceInvertido* criarIndice();
 // Adiciona um número de telefone ao índice
void adicionarIndice(IndiceInvertido *indice, char *numeroTelefone);
// Remove um número de telefone do índice
void removerIndice(IndiceInvertido *indice, const char *numeroTelefone);
// Realiza uma busca aproximada no índice
void BuscaAproximada(IndiceInvertido *indice, char *consulta);
// Atualiza um número de telefone no índice
void atualizarIndice(IndiceInvertido* indice,char* novoNumeroTelefone, char* numeroTelefoneAntigo);
#endif