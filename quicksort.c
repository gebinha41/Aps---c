#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quickSort(double *arr, int esq, int dir);
int particionar(double *arr, int esq, int dir);
void imprimirArray(double *arr, int tamanho);

int main() {
    int tamanho;
    printf("Digite o número de elementos: ");
    scanf("%d", &tamanho);

    double *numeros = (double *)malloc(tamanho * sizeof(double));
    if (numeros == NULL) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        return 1;
    }

    // Gerar números aleatórios
    srand(time(NULL));
    for (int i = 0; i < tamanho; i++) {
        numeros[i] = (double)(rand() % 100); // números entre 0 e 99
    }

    printf("Array original:\n");
    imprimirArray(numeros, tamanho);

    clock_t inicio = clock();
    quickSort(numeros, 0, tamanho - 1);
    clock_t fim = clock();

    printf("Array ordenado:\n");
    imprimirArray(numeros, tamanho);

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000; // em milissegundos
    printf("Tempo de execução: %.2f ms\n", tempo);

    free(numeros);
    return 0;
}

void quickSort(double *arr, int esq, int dir) {
    if (esq < dir) {
        int indice = particionar(arr, esq, dir);
        quickSort(arr, esq, indice - 1);
        quickSort(arr, indice, dir);
    }
}

int particionar(double *arr, int esq, int dir) {
    double pivot = arr[(esq + dir) / 2];
    int i = esq;
    int j = dir;
    double tmp;

    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;

        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }
    return i;
}

void imprimirArray(double *arr, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%.2f ", arr[i]);
    }
    printf("\n");
}
