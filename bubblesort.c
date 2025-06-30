#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>


void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void odd_even_bubble_sort(int *arr, int n, int num_threads) {
    omp_set_num_threads(num_threads);
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            #pragma omp parallel for
            for (int j = 0; j < n - 1; j += 2) {
                if (arr[j] > arr[j + 1]) {
                    swap(&arr[j], &arr[j + 1]);
                }
            }
        } else {
            #pragma omp parallel for
            for (int j = 1; j < n - 1; j += 2) {
                if (arr[j] > arr[j + 1]) {
                    swap(&arr[j], &arr[j + 1]);
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <n>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Erro: n deve ser um número positivo\n");
        return 1;
    }
    srand(time(NULL));
    int *original = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        original[i] = rand() % (n * 10);
    }
    printf("==== BUBBLE SORT ODD-EVEN TRANSPOSITION ====\n");
    printf("Tamanho do array: %d elementos\n\n", n);
    int *arr1 = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr1[i] = original[i];
    double start_time = omp_get_wtime();
    odd_even_bubble_sort(arr1, n, 1);
    double end_time = omp_get_wtime();
    double time_1_thread = end_time - start_time;
    printf("1 THREAD:\n");
    printf("Tempo de execução: %.6f segundos\n", time_1_thread);
    printf("Speedup: 1.00\n");
    printf("Eficiência: 1.00\n\n");
    int *arr2 = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr2[i] = original[i];
    start_time = omp_get_wtime();
    odd_even_bubble_sort(arr2, n, 2);
    end_time = omp_get_wtime();
    double time_2_threads = end_time - start_time;
    double speedup_2 = time_1_thread / time_2_threads;
    double efficiency_2 = speedup_2 / 2.0;
    printf("2 THREADS:\n");
    printf("Tempo de execução: %.6f segundos\n", time_2_threads);
    printf("Speedup: %.2f\n", speedup_2);
    printf("Eficiência: %.2f\n\n", efficiency_2);
    int *arr4 = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr4[i] = original[i];
    start_time = omp_get_wtime();
    odd_even_bubble_sort(arr4, n, 4);
    end_time = omp_get_wtime();
    double time_4_threads = end_time - start_time;
    double speedup_4 = time_1_thread / time_4_threads;
    double efficiency_4 = speedup_4 / 4.0;
    printf("4 THREADS:\n");
    printf("Tempo de execução: %.6f segundos\n", time_4_threads);
    printf("Speedup: %.2f\n", speedup_4);
    printf("Eficiência: %.2f\n\n", efficiency_4);
    printf("Verificação (primeiros 20 elementos): ");
    for (int i = 0; i < (n < 20 ? n : 20); i++) {
        printf("%d ", arr4[i]);
    }
    printf("\n");
    free(original);
    free(arr1);
    free(arr2);
    free(arr4);   
    return 0;
}