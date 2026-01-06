#include "filaprocessos.h"
#include<stdio.h>
#include<stdlib.h>

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

void FilaProcessosPrint(FilaProcessos *fila) {
    if(fila->tamanho > 0) {
        Processo* processo = fila->primeiroProcesso;
    
        printf("\nfila ->");
        while(processo != NULL) {
            printf(" %d -> ", processo->id);
            processo = processo->prox; 
        }
    
        printf("END");
    } else {
        printf("\nFILA NÃO POSSUI PROCESSOS\n");
    }
}

FilaProcessos* criaFila() {
    FilaProcessos* fila = (FilaProcessos*)calloc(1, sizeof(FilaProcessos));
    fila->primeiroProcesso = fila->ultimoProcesso = NULL;
    fila->tamanho = 0;

    if(!fila) {
        printf("ERRO. FILA NÃO ALOCADA CORRETAMENTE\n");
        return NULL;
    }
    return fila;
}

Processo* criaProcesso(int id, float tempo, int prioridade, int ciclos) {
    if(tempo < 0 || ciclos < 0) {
        printf("PROCESSO INVÁLIDO\n");
        return NULL;
    }

    Processo* processo = (Processo*)calloc(1, sizeof(Processo));

    processo->id = id;
    processo->tempo = tempo;
    processo->prioridade = prioridade;
    processo->ciclos = ciclos;
    processo->prox = NULL;

    return processo;
}

FilaProcessos* destroiFila(FilaProcessos** fila) {
    if(!fila)
        return NULL;
    
    Processo* _proxProcesso = (*fila)->primeiroProcesso;
    Processo* _prevProcesso = NULL;

    while(_proxProcesso != NULL) {
        _prevProcesso = _proxProcesso;
        _proxProcesso = _proxProcesso->prox;
        free(_prevProcesso);
    }
    free(*fila);
    *fila = NULL;

    return NULL;
}

void resetaFila(FilaProcessos* fila) {
    if(!fila)
        return;
    
    fila->primeiroProcesso = fila->ultimoProcesso = NULL;
    fila->tamanho = 0;
}

Processo* adicionaFila(FilaProcessos* fila, int id, float tempo, int prioridade, int ciclos) {
    if(!fila) {
        printf("ERRO. FILA NÃO EXISTE\n");
        return NULL;
    }

    Processo* processo = criaProcesso(id, tempo, prioridade, ciclos);
    
    if(fila->tamanho == 0) {
        fila->primeiroProcesso = fila->ultimoProcesso = processo;
        fila->tamanho++;
    } else {
        fila->ultimoProcesso->prox = processo;
        fila->ultimoProcesso = processo;
        fila->tamanho++;
    }
}

void imprimeProcesso(Processo* processo) {
    printf("\n\nID: %d\n", processo->id);
    printf("TEMPO: %.2f\n", processo->tempo);
    printf("PRIORIDADE: %d\n", processo->prioridade);
    printf("CICLOS: %d\n", processo->ciclos);
}

void imprimeMatrizDeProcessos(Processo** matrizDeProcessos, int quantidadeProcessos) {
    for(int i = 0; i < quantidadeProcessos; i++) {
        printf("\nID: %d\n", matrizDeProcessos[i]->id);
        printf("TEMPO: %.2f\n", matrizDeProcessos[i]->tempo);
        printf("PRIORIDADE: %d\n", matrizDeProcessos[i]->prioridade);
        printf("CICLOS: %d\n", matrizDeProcessos[i]->ciclos);
    }
    printf("############################################################\n");
}

Processo* buscaProcesso(FilaProcessos* fila, int i) {
    Processo* _next = fila->primeiroProcesso; // USO DOIS PONTEIROS PRA EVITAR QUE O PROCESSO RETORNADO SEJA O i+1 ao invés do i
    Processo* _prev = NULL;

    for(int j = 0; j < i; j++) {
        _next = _next->prox;
    }
    return _next;
}

void merge(Processo** matrizAuxiliar, int inicio, int meio, int fim) {
    int tamanhoVetorEsquerda = meio - inicio + 1;
    int tamanhoVetorDireita = fim - meio;

    Processo** vetorEsquerda = (Processo**)calloc(tamanhoVetorEsquerda, sizeof(Processo));
    Processo** vetorDireita  = (Processo**)calloc(tamanhoVetorDireita, sizeof(Processo));

    int topoVetorEsquerda = 0;
    int topoVetorDireita  = 0;

    for(int i = 0; i < tamanhoVetorEsquerda; i++)
        vetorEsquerda[i] = matrizAuxiliar[i+inicio];

    for(int j = 0; j < tamanhoVetorDireita; j++)
        vetorDireita[j] = matrizAuxiliar[j + meio + 1];

    for(int k = inicio; k <= fim; k++) {
        if(topoVetorEsquerda >= tamanhoVetorEsquerda)
            matrizAuxiliar[k] = vetorDireita[topoVetorDireita++];
        else if(topoVetorDireita >= tamanhoVetorDireita)
            matrizAuxiliar[k] = vetorEsquerda[topoVetorEsquerda++];
        else if(vetorEsquerda[topoVetorEsquerda]->prioridade <= vetorDireita[topoVetorDireita]->prioridade && 
                vetorEsquerda[topoVetorEsquerda]->tempo <= vetorDireita[topoVetorDireita]->tempo)
            matrizAuxiliar[k] = vetorEsquerda[topoVetorEsquerda++];
        else 
            matrizAuxiliar[k] = vetorDireita[topoVetorDireita++];
    }

    free(vetorDireita);
    free(vetorEsquerda);
}

void mergeSort(Processo** matrizAuxiliar, int inicio, int fim) {
    if(inicio < fim) {
        int meio = (inicio + fim) / 2;

        mergeSort(matrizAuxiliar, inicio, meio);
        mergeSort(matrizAuxiliar, meio+1, fim);

        merge(matrizAuxiliar, inicio, meio, fim);
    }
}

void escalonador(FilaProcessos* fila, int quantidadeProcessos) {
    Processo** matrizAuxiliar = calloc(quantidadeProcessos, sizeof(Processo*));

    for(int i = 0; i < quantidadeProcessos; i++){
        matrizAuxiliar[i] = buscaProcesso(fila, i);
    }

    liberaFila(fila);
    mergeSort(matrizAuxiliar, 0, quantidadeProcessos-1);

    for(int j = 0; j < quantidadeProcessos; j++) {
        adicionaFila(
                        fila, 
                        matrizAuxiliar[j]->id,
                        matrizAuxiliar[j]->tempo,
                        matrizAuxiliar[j]->prioridade,
                        matrizAuxiliar[j]->ciclos
                    );
    }
}









