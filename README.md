# SIMULAÇÃO DE ESCALONADOR DE PROCESSOS

Este repositório contém a implementação do Trabalho Prático II da disciplina de Estruturas de Dados I (UFOP). O objetivo é simular o funcionamento de um escalonador de processos dentro do Kernel de um sistema operacional, utilizando TADS (Tipos Abstratos de Dados), Filas e Algoritmos de Ordenação.

## 📋 Sobre o projeto

O programa simula um escalonador simples que gerencia o acesso de processos à CPU. Ele decide a ordem de execução com base em prioridade e ordem de chegada, respeitando um limite de tempo (Quantum) por execução

Dentro do Kernel de um sistema operacional, o escalonador decide quais processos terão acesso a CPU e por quanto tempo eles irão executar. Neste trabalho foi criado um algoritmo que simula um escalonador simples, levando em consideração a ordem de chegada dos processos, suas prioridades e a quantidade de ciclos de CPU.

O escalonador atende primeiro os processos mais prioritários, seguindo a ordem de chegada deles. Além disso, os processos não podem executar por mais que X ciclos na CPU, sendo reinseridos na fila de processos se ainda faltarem ciclos. Neste trabalho, tomamos X = 100.

Com isso em mãos, formulamos as regras:
- **Prioridade**: Processos com menor valor numérico de prioridade são atendidos primeiro .
- **Desempate**: Caso as prioridades sejam iguais, o critério de desempate é o tempo de chegada (somente na ordenação inicial)
- **Quantum**: Cada processo pode executar por no máximo 100 ciclos (X=100) consecutivamente.
- **Reinserção**: Se um processo não terminar em 100 ciclos, ele é interrompido e reinserido na fila com sua prioridade decrementada (valor numérico +1). Na reinserção, o tempo de chegada original é ignorado.

## ⚙️ Estrutura do projeto
O código foi modularizado conforme especificado, separando interface e implementação:

`app/` - Contém o arquivo main que chama as funções criadas
`binaries` - Guarda os executáveis gerados a partir da compilação de `./app/tp.c`
`include/` - Contém os arquivos de cabeçalho com as assinaturas das funções
`src/` - Guarda as implementações dos arquivos `.h` de `./include`
`obj/` - Possui os arquivos objeto `.o` gerados a partir da compilação dos arquivos de implementação de `./src/`
`Makefile` - Usado pra compilar e executar o projeto de forma mais simples


## 📄 Formato de entrada e saída dos dados

**Entrada**
A primeira linha contém o número `N` de processos. As linhas seguintes contêm 4 valores: `ID`, `Tempo de Chegada`, `Prioridade` e `Ciclos Totais`.

Exemplo:
```bash
4
1001 1.0 10 50
2002 2.0 1 50
3003 3.0 5 50
4004 0.5 5 50
```

**Saída (Log)**
O programa imprime a ordem de execução, a prioridade no momento da execução e quantos ciclos foram consumidos naquela rodada.

Exemplo:
```bash
Log CPU:
4004 5 50
2002 1 50
3003 5 50
1001 10 50
```

## 🔍Verificação de Memória
O projeto foi desenvolvido com foco em gerenciamento eficiente de memória. Para verificar a ausência de memory leaks, utilize o Valgrind conforme sugerido na especificação
```bash
valgrind --leak-check=full ./binaries/tp < input.txt
```