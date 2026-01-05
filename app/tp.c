#include "filaprocessos.h"
#include<stdio.h>
#include<stdlib.h>

int main() {
    FilaProcessos* fila = criaFila();

    int quantidadeProcessos = 0;
    int id = 0;
    float tempo = 0;
    int prioridade = 0;
    int ciclos = 0;

    scanf("%d", &quantidadeProcessos);

    for(int i = 0; i < quantidadeProcessos; i++) {
        scanf("%d%f%d%d", &id, &tempo, &prioridade, &ciclos);
        adicionaFila(fila, id, tempo, prioridade, ciclos);
    }

    escalonador(fila, quantidadeProcessos);

    destroiFila(&fila);
}