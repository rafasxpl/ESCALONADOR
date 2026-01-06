#include "insertion.h"
#include<stdio.h>

void printVetor(int* v, int size) {
    if(size <= 0) {
        printf("\n\nVETOR INVÁLIDO\n\n");
        return;
    }

    for(int i = 0; i < size; i++) {
        printf(" %d ", v[i]);
    }

    printf("\n");
}

void insertionSort(Processo** matrizAuxiliar, int tamanho) {
    if(tamanho <= 0) {
        printf("\n\nVETOR INVÁLIDO. INSERTION SORT\n\n");
        return;
    }

    Processo* aux;
    
    for(int i = 0; i < tamanho; i++) {
        int j = i - 1;
        aux = matrizAuxiliar[i];

        while(j >= 0 && aux->prioridade <= matrizAuxiliar[j]->prioridade) {
            matrizAuxiliar[j+1] = matrizAuxiliar[j];
            j--;
        }
        matrizAuxiliar[j+1] = aux;
    }
}

