#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

#define PATH_ORDENADO "C:\\Temp\\Coordenadas\\Ordenado\\"
#define PATH_DESORDENADO "C:\\Temp\\Coordenadas\\Desordenado\\"

typedef struct {
    double* coordenadas;
    int qtdCoord;
} GeradorCoordenada;

void initGeradorCoordenada(GeradorCoordenada* gerador, int qtd) {
    gerador->qtdCoord = qtd;
    gerador->coordenadas = (double*)malloc(qtd * sizeof(double));
}

void freeGeradorCoordenada(GeradorCoordenada* gerador) {
    free(gerador->coordenadas);
}

void gerarCoordenadas(GeradorCoordenada* gerador) {
    for (int i = 0; i < gerador->qtdCoord; i++) {
        gerador->coordenadas[i] = ((double)rand() / RAND_MAX) * 360 - 180; // Latitude entre -180 e 180
    }
}

void criarDiretorio(const char* path) {
    #ifdef _WIN32
    _mkdir(path);
    #else
    mkdir(path, 0777);
    #endif
}

void salvarCoordenadas(const char* nomeArquivo, double* coordenadas, int qtd) {
    FILE* file = fopen(nomeArquivo, "w");
    if (file) {
        for (int i = 0; i < qtd; i++) {
            fprintf(file, "%.6f\n", coordenadas[i]);
        }
        fclose(file);
    } else {
        perror("Não foi possível abrir o arquivo");
    }
}

void quickSort(double* arr, int left, int right);
void mergeSort(double* arr, int left, int right);
void heapSort(double* arr, int n);

void ordenarCoordenadas(double* arr, int qtd, const char* nomeArquivo, void (*sortFunc)(double*, int, int)) {
    double* arrClone = (double*)malloc(qtd * sizeof(double));
    memcpy(arrClone, arr, qtd * sizeof(double));
    
    clock_t start = clock();
    sortFunc(arrClone, 0, qtd - 1);
    clock_t end = clock();
    
    salvarCoordenadas(nomeArquivo, arrClone, qtd);
    free(arrClone);
    printf("Ordenação concluída e salva em %s\n", nomeArquivo);
}

int main() {
    srand(time(NULL)); // Inicializa a semente para números aleatórios

    int qtdCoord = 10; // Defina a quantidade de coordenadas que deseja gerar
    char nomeArquivo[100];
    
    printf("Digite o nome do arquivo (sem extensão): ");
    scanf("%s", nomeArquivo);
    
    // Criação dos diretórios
    criarDiretorio(PATH_ORDENADO);
    criarDiretorio(PATH_DESORDENADO);

    GeradorCoordenada gerador;
    initGeradorCoordenada(&gerador, qtdCoord);
    
    // Gerar coordenadas
    gerarCoordenadas(&gerador);
    salvarCoordenadas(PATH_DESORDENADO "coordenadas_desordenadas.txt", gerador.coordenadas, gerador.qtdCoord);

    // Ordenação
    char nomeArquivoOrdenado[100];
    
    snprintf(nomeArquivoOrdenado, sizeof(nomeArquivoOrdenado), "%s%sQuickSort.txt", PATH_ORDENADO, nomeArquivo);
    ordenarCoordenadas(gerador.coordenadas, gerador.qtdCoord, nomeArquivoOrdenado, quickSort);
    
    snprintf(nomeArquivoOrdenado, sizeof(nomeArquivoOrdenado), "%s%sMergeSort.txt", PATH_ORDENADO, nomeArquivo);
    ordenarCoordenadas(gerador.coordenadas, gerador.qtdCoord, nomeArquivoOrdenado, mergeSort);
    
    snprintf(nomeArquivoOrdenado, sizeof(nomeArquivoOrdenado), "%s%sHeapSort.txt", PATH_ORDENADO, nomeArquivo);
    ordenarCoordenadas(gerador.coordenadas, gerador.qtdCoord, nomeArquivoOrdenado, heapSort);

    freeGeradorCoordenada(&gerador);
    return 0;
}

// Implementação dos algoritmos de ordenação (placeholder para os métodos de ordenação)
void quickSort(double* arr, int left, int right) {
    // Implementação do QuickSort aqui
}

void mergeSort(double* arr, int left, int right) {
    // Implementação do MergeSort aqui
}

void heapSort(double* arr, int n) {
    // Implementação do HeapSort aqui
}
