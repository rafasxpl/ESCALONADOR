#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "filaprocessos.h"
#include "merge.h"
#include "insertion.h"
#include "structs.h"

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

void imprimeLog(FilaProcessos *fila) {
    if(fila->tamanho > 0) {
        Processo* processo = fila->primeiroProcesso;
    
        printf("\n");
        while(processo != NULL) {
            printf("%d %d %d\n", processo->id, processo->prioridade, processo->ciclos);
            processo = processo->prox; 
        }
    } else {
        printf("\nFILA NÃO POSSUI PROCESSOS\n");
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

bool resolveProcesso(FilaProcessos*fila, Processo* processo) {
    int x = 100;
    if(processo->ciclos > 0 && processo->ciclos <= 100) {
        adicionaFila(
            fila,
            processo->id,
            processo->tempo,
            processo->prioridade,
            processo->ciclos
        );
        processo->ciclos -= x;
        fila->tamanho++;
        return true;
    }
    
    
    adicionaFila(
        fila,
        processo->id,
        processo->tempo,
        processo->prioridade,
        x
    );
    
    processo->ciclos -= x;
    processo->prioridade++;
    fila->tamanho++;

    return false;
}

bool existeProcessoValido(Processo** matrizDeProcessos, int quantidadeProcessos) {
    for(int i = 0; i < quantidadeProcessos; i++) {
        if(matrizDeProcessos[i]->ciclos > 0)
            return true;
    }
    return false;
}

void escalonador(FilaProcessos* fila, int quantidadeProcessos) {
    Processo** matrizAuxiliar = calloc(quantidadeProcessos, sizeof(Processo*));

    for(int i = 0; i < quantidadeProcessos; i++){
        matrizAuxiliar[i] = buscaProcesso(fila, i);
    }

    resetaFila(fila);
    mergeSort(matrizAuxiliar, 0, quantidadeProcessos-1);

    bool result = false;
    int indiceProcessoValido = 0;

    while(existeProcessoValido(matrizAuxiliar, quantidadeProcessos)) {
        for(int i = 0; i < quantidadeProcessos; i++) {
            if(matrizAuxiliar[i]->ciclos > 0) {
                indiceProcessoValido = i;
                break;
            }    
        }
        result = resolveProcesso(fila, matrizAuxiliar[indiceProcessoValido]);

        if(result == false) {
            insertionSort(matrizAuxiliar, quantidadeProcessos);
        }
    }
    imprimeLog(fila);
}

