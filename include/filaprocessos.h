#ifndef FILA_H
#define FILA_H

typedef struct _processo Processo;
typedef struct _filaProcessos FilaProcessos;

// CRIA FILA_PROCESSOS
FilaProcessos* criaFila();

// CRIA PROCESSO
Processo* criaProcesso(int id, float tempo, int prioridade, int ciclos);

// DESTROI FILA_PROCESSOS E OS SEUS RESPECTIVOS PROCESSOS
FilaProcessos* destroiFila(FilaProcessos** fila);

// ADICIONA PROCESSO À FILA_PROCESSOS
Processo* adicionaFila(FilaProcessos* fila, int id, float tempo, int prioridade, int ciclos);

// IMPRIME O LOG DA CPU
void imprimeLog(FilaProcessos *fila);

// EXIBE O CONTEÚDO DE UM PROCESSO
void imprimeProcesso(Processo* processo);

// BUSCA UM CERTO PROCESSO COM BASE NA POSIÇÃO NA FILA
Processo* buscaProcesso(FilaProcessos* fila, int i);

// CHAMA A FUNÇÃO QUE SIMULA O ESCALONADOR
void escalonador(FilaProcessos* fila, int quantidadeProcessos);

#endif