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

bool processoInvalido(Processo* processo) {
    if(processo->ciclos < 0 || processo->tempo < 0.0f)
        return true;
    return false;
}

bool filaInvalida(FilaProcessos* fila) {
    if(filaInvalida(fila) || fila->tamanho < 0)
        return true;

    if(fila->tamanho == 0) {
        if(fila->primeiroProcesso != NULL || fila->ultimoProcesso != NULL)
            return true;
    } else {
        if(fila->primeiroProcesso == NULL || fila->ultimoProcesso == NULL)
            return true;
    }
    return false;
}

Processo* adicionaFila(FilaProcessos* fila, int id, float tempo, int prioridade, int ciclos) {
    if(filaInvalida(fila)) {
        printf("ERRO. FILA INVÁLIDA\n");
        return NULL;
    }

    Processo* processo = criaProcesso(id, tempo, prioridade, ciclos);
        
    if(fila->tamanho == 0) {
        fila->primeiroProcesso = fila->ultimoProcesso = processo;
    } else {
        fila->ultimoProcesso->prox = processo;
        fila->ultimoProcesso = processo;
    }
    fila->tamanho++;

    return processo;
}

FilaProcessos* destroiFila(FilaProcessos** fila) {
   if(filaInvalida(*fila)) {
        printf("ERRO. FILA INVÁLIDA\n");
        return NULL;
    }
    
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
    if(filaInvalida(fila)) {
        printf("ERRO. FILA INVÁLIDA\n");
    } else {
        fila->primeiroProcesso = fila->ultimoProcesso = NULL;
        fila->tamanho = 0;
    }
}

void imprimeLog(FilaProcessos *fila) {
    if(filaInvalida(fila)) {
        printf("ERRO. FILA INVÁLIDA\n");
    } else {
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
}

void imprimeProcesso(Processo* processo) {
    if(processoInvalido(processo)) {
        printf("ERRO. PROCESSO INVÁLIDO\n");
    } else {
        printf("\n\nID: %d\n", processo->id);
        printf("TEMPO: %.2f\n", processo->tempo);
        printf("PRIORIDADE: %d\n", processo->prioridade);
        printf("CICLOS: %d\n", processo->ciclos);
    }

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
    if(filaInvalida(fila)) {
        printf("ERRO. FILA INVÁLIDA\n");
        return NULL;
    }
    if(i >= fila->tamanho) {
        printf("ERRO. INDICE INVÁLIDO\n");
        return NULL;
    }

    Processo* _next = fila->primeiroProcesso;

    for(int j = 0; j < i; j++) {
        _next = _next->prox;
    }
    return _next;
}

bool resolveProcesso(FilaProcessos*fila, Processo* processo) {
    if(filaInvalida(fila)) {
        printf("ERRO. FILA INVÁLIDA\n");
        return NULL;
    }
    if(processoInvalido(processo)) {
        printf("ERRO. PROCESSO INVÁLIDO\n");
        return NULL;
    }
    
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

    return false;
}

bool existeProcessoValido(Processo** matrizDeProcessos, int quantidadeProcessos) {
    for(int i = 0; i < quantidadeProcessos; i++) {
        if(matrizDeProcessos[i]->ciclos > 0)
            return true;
    }
    return false;
}

void destroiMatrizAuxiliar(Processo** matrizAuxiliar, int n) {
    for(int i = 0; i < n; i++)
        free(matrizAuxiliar[i]);

    free(matrizAuxiliar);
}

void escalonador(FilaProcessos* fila, int quantidadeProcessos) {
    if(filaInvalida(fila)) {
        printf("ERRO. FILA INVÁLIDA\n");
    } else {
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
    
        destroiMatrizAuxiliar(matrizAuxiliar, quantidadeProcessos);
    }
}

