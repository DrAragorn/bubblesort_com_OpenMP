#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>


// ---- Troca os valores de posição, um com o outro ----
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void odd_even_bubble_sort(int *arr, int n, int num_threads) {
    // ---- Definindo quantidade de threads ----
    omp_set_num_threads(num_threads);
    // ---- Divisão em duplas dos valores das listas. Após as threads ordenarem dentro das duplas, move-se para a próxima etapa, fazendo primeiro a etapa par, depois a ímpar, e assim repetindo até a lista estar ordenada ----
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            // ---- No paralelismo apenas dentro do for ----
            #pragma omp parallel for
            // ---- Etapa par do sorting ----
            for (int j = 0; j < n - 1; j += 2) {
                if (arr[j] > arr[j + 1]) {
                    swap(&arr[j], &arr[j + 1]);
                }
            }
        } else {
            // ---- No paralelismo apenas dentro do for ----
            #pragma omp parallel for
            // ---- Etapa ímpar do sorting ----
            for (int j = 1; j < n - 1; j += 2) {
                if (arr[j] > arr[j + 1]) {
                    swap(&arr[j], &arr[j + 1]);
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    // ---- Passando o argumento n para variavel int ----
    int n = atoi(argv[1]);
    srand(time(NULL));
    int *arr_original = (int*)malloc(n * sizeof(int));
    // ---- Criando lista de números aleatórios ----
    // ---- Cada número aleatório está de 0 até 10n ----
    for (int i = 0; i < n; i++) {
        arr_original[i] = rand() % (n * 10);
    }
    printf("==== BUBBLE SORT ODD-EVEN TRANSPOSITION ====\n");
    printf("Tamanho do array: %d elementos\n\n", n);
    int *arr1 = (int*)malloc(n * sizeof(int));
    // ---- Copiando o conteúdo da lista original para uma auxiliar, para manter a original para os próximos usos com mais threds ----
    for (int i = 0; i < n; i++) arr1[i] = arr_original[i];
    // ---- Marcação do tempo na ordenação com 1 thread ----
    double start_time = omp_get_wtime();
    odd_even_bubble_sort(arr1, n, 1);
    double end_time = omp_get_wtime();
    // ---- Métricas da execução com 1 thread ----
    double time_1_thread = end_time - start_time;
    printf("1 THREAD:\n");
    printf("Tempo de execução: %.6f segundos\n\n", time_1_thread);
    int *arr2 = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr2[i] = arr_original[i];
    // ---- Marcação do tempo na ordenação com 2 threads ----
    start_time = omp_get_wtime();
    odd_even_bubble_sort(arr2, n, 2);
    end_time = omp_get_wtime();
    // ---- Métricas da execução com 2 threads ----
    double time_2_threads = end_time - start_time;
    double speedup_2 = time_1_thread / time_2_threads;
    double efficiency_2 = speedup_2 / 2.0;
    printf("2 THREADS:\n");
    printf("Tempo de execução: %.6f segundos\n", time_2_threads);
    printf("Speedup: %.2f\n", speedup_2);
    printf("Eficiência: %.2f\n\n", efficiency_2);
    int *arr4 = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr4[i] = arr_original[i];
    // ---- Marcação do tempo na ordenação com 4 threads ----
    start_time = omp_get_wtime();
    odd_even_bubble_sort(arr4, n, 4);
    end_time = omp_get_wtime();
    // ---- Métricas da execução com 4 threads ----
    double time_4_threads = end_time - start_time;
    double speedup_4 = time_1_thread / time_4_threads;
    double efficiency_4 = speedup_4 / 4.0;
    printf("4 THREADS:\n");
    printf("Tempo de execução: %.6f segundos\n", time_4_threads);
    printf("Speedup: %.2f\n", speedup_4);
    printf("Eficiência: %.2f\n\n", efficiency_4);
    printf("\n");
    free(arr_original);
    free(arr1);
    free(arr2);
    free(arr4);   
    return 0;
}