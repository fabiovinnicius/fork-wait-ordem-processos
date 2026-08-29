/*
 * Testa a hipótese de que a ordem de criação de processos filhos (fork())
 * determina a ordem em que eles terminam e são coletados pelo processo pai
 * (wait()).
 *
 * Uso:
 *   ./experiment [numero_de_filhos]
 *
 * Código de saída:
 *   0 -> ordem de término coincidiu com a ordem de criação
 *   1 -> ordem de término foi diferente
 *   2 -> erro de uso (número de filhos inválido)
 */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define MAX_FILHOS 20
#define TEMPO_MIN_US 10000   // 10 ms
#define TEMPO_MAX_US 210000  // 210 ms

int main(int argc, char *argv[]) {
    int n = (argc > 1) ? atoi(argv[1]) : 5;
    if (n < 1 || n > MAX_FILHOS) {
        fprintf(stderr, "Uso: %s <numero_de_filhos (1-%d)>\n", argv[0], MAX_FILHOS);
        return 2;
    }

    pid_t pid_criacao[MAX_FILHOS];   // PID de cada filho, na ordem em que foi criado
    pid_t pid_termino[MAX_FILHOS];   // PID de cada filho, na ordem em que terminou

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(1);
        }

        if (pid == 0) {
            /*processo filho
            OBS: cada filho precisa semear o gerador de numeros aleatorios de forma INDEPENDENTE, depois do fork(). Se o pai chamasse srand() uma unica vez antes do loop, todos os filhos herdariam o mesmo estado do PRNG (copy-on-write) e sorteariam exatamente o mesmo valor -- um erro sutil que invalidaria a premissa de tempos de execucao independentes.*/
            struct timespec ts;
            clock_gettime(CLOCK_REALTIME, &ts);
            srand((unsigned int)ts.tv_nsec ^ getpid());

            int intervalo = TEMPO_MAX_US - TEMPO_MIN_US;
            int tempo_us = (rand() % intervalo) + TEMPO_MIN_US;

            struct timespec espera;
            espera.tv_sec = tempo_us / 1000000;
            espera.tv_nsec = (tempo_us % 1000000) * 1000L;
            nanosleep(&espera, NULL);
            // o codigo de saida carrega o indice de criacao (0..n-1)
            // para o pai conseguir identificar quem terminou
            _exit(i);
        } else {
            // processo pai
            pid_criacao[i] = pid;
        }
    }

    // pai aguarda os filhos SEM especificar ordem -> wait() generico
    for (int i = 0; i < n; i++) {
        int status;
        pid_t pid_terminado = wait(&status);
        int indice_criacao = WEXITSTATUS(status);
        pid_termino[i] = pid_terminado;

        printf("[%d] terminou -> PID=%d | era o %dº filho criado\n",
               i + 1, pid_terminado, indice_criacao + 1);
    }

    int mesma_ordem = 1;
    for (int i = 0; i < n; i++) {
        if (pid_termino[i] != pid_criacao[i]) {
            mesma_ordem = 0;
            break;
        }
    }

    printf("RESULTADO: %s\n", mesma_ordem ? "ORDEM PRESERVADA" : "ORDEM DIFERENTE");
    return mesma_ordem ? 0 : 1; // usado pelo script de analise estatistica
}