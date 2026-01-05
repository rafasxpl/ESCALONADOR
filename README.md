# ESCALONADOR DE PROCESSOS
Dentro do Kernel de um sistema operacional, o escalonador decide quais processos terão acesso a CPU
e por quanto tempo eles irão executar. Neste trabalho você deverá criar um algoritmo que simule um
escalonador simples, levando em consideração a ordem de chegada dos processos, suas prioridades e a
quantidade de ciclos de CPU.
O escalonador deve atender primeiro os processos mais prioritários, seguindo a ordem de chegada deles.
Além disso, os processos não podem executar por mais que X ciclos na CPU, sendo reinseridos na fila de
processos se ainda faltarem ciclos. Neste trabalho, tomaremos X = 100