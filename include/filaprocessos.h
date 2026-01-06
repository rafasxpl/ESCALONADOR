#ifndef FILA_H
#define FILA_H

typedef struct _processo Processo;
typedef struct _filaProcessos FilaProcessos;

typedef struct _processo {
    int id;
    float tempo;
    int prioridade;
    int ciclos;
    struct _processo* prox;
} Processo;

typedef struct _filaProcessos {
    Processo* primeiroProcesso;
    Processo* ultimoProcesso;
    int tamanho;    
} FilaProcessos;

// CRIA FILA_PROCESSOS
FilaProcessos* criaFila();

// CRIA PROCESSO
Processo* criaProcesso(int id, float tempo, int prioridade, int ciclos);

// DESTROI FILA_PROCESSOS
FilaProcessos* destroiFila(FilaProcessos** fila);

// RESETA A FILA (FAZ COM QUE NÃO APONTE A NENHUM PROCESSO), MAS NÃO A DESTROI
void resetaFila(FilaProcessos* fila);

// ADICIONA PROCESSO À FILA_PROCESSOS
Processo* adicionaFila(FilaProcessos* fila, int id, float tempo, int prioridade, int ciclos);

// IMPRIME O LOG DA CPU
void imprimeLog();

// EXIBE O CONTEÚDO DA FILA DE PROCESSOS
void FilaProcessosPrint(FilaProcessos *fila);

// EXIBE O CONTEÚDO DE UM PROCESSO
void imprimeProcesso(Processo* processo);

// BUSCA UM CERTO PROCESSO COM BASE NA POSIÇÃO NA FILA
Processo* buscaProcesso(FilaProcessos* fila, int i);

void escalonador(FilaProcessos* fila, int quantidadeProcessos);

#endif