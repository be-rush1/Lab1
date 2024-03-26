#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 10 // Tamanho do vetor
#define M 2  // Número de threads

// Estrutura para os argumentos da função das threads
typedef struct {
    int *vetor;
    int inicio;
    int fim;
} ThreadArgs;

// Função que eleva ao quadrado cada elemento do vetor
void *elevaAoQuadrado(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    for (int i = args->inicio; i < args->fim; i++) {
        args->vetor[i] *= args->vetor[i];
    }
    pthread_exit(NULL);
}

int main() {
    int vetor[N];
    pthread_t threads[M];
    ThreadArgs thread_args[M];

    // Preenche o vetor com valores aleatórios
    printf("Vetor original:\n");
    for (int i = 0; i < N; i++) {
        vetor[i] = rand() % 100; // Números aleatórios entre 0 e 99
        printf("%d ", vetor[i]);
    }
    printf("\n");

    // Cria as threads
    for (int i = 0; i < M; i++) {
        thread_args[i].vetor = vetor;
        thread_args[i].inicio = i * (N / M);
        thread_args[i].fim = (i + 1) * (N / M);
        pthread_create(&threads[i], NULL, elevaAoQuadrado, (void *)&thread_args[i]);
    }

    // Espera todas as threads terminarem
    for (int i = 0; i < M; i++) {
        pthread_join(threads[i], NULL);
    }

    // Imprime o vetor após elevar ao quadrado
    printf("Vetor elevado ao quadrado:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    return 0;
}
