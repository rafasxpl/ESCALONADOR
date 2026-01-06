#ifndef STRUCTS_H
#define STRUCTS_H

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

#endif 