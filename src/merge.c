#include<stdlib.h>
#include "merge.h"
#include "structs.h"

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
        if(topoVetorEsquerda >= tamanhoVetorEsquerda) {
            matrizAuxiliar[k] = vetorDireita[topoVetorDireita++];
        } else if(topoVetorDireita >= tamanhoVetorDireita) {
            matrizAuxiliar[k] = vetorEsquerda[topoVetorEsquerda++];
        } else if(vetorEsquerda[topoVetorEsquerda]->prioridade == vetorDireita[topoVetorDireita]->prioridade){
            if(vetorEsquerda[topoVetorEsquerda]->tempo < vetorDireita[topoVetorDireita]->tempo){
                matrizAuxiliar[k] = vetorEsquerda[topoVetorEsquerda++];
            } else {
                matrizAuxiliar[k] = vetorDireita[topoVetorDireita++];
            }
        } else if(vetorEsquerda[topoVetorEsquerda]->prioridade < vetorDireita[topoVetorDireita]->prioridade) {
            matrizAuxiliar[k] = vetorEsquerda[topoVetorEsquerda++];
        } else {
                matrizAuxiliar[k] = vetorDireita[topoVetorDireita++];
        }
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
