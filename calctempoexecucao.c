#include <stdio.h>
#include <time.h>

// Definindo um tipo para a função que calculará o tempo de execução
typedef long (*TempoExecucaoFunc)();

// Estrutura que simula a interface
typedef struct {
    TempoExecucaoFunc calcularTempoAlgoritmo;
} CalcTempoExecucao;

// Exemplo de função que implementa a lógica de cálculo de tempo
long calcularTempoExemplo() {
    clock_t start = clock();
    
    // Simulando algum algoritmo com um loop
    for (volatile int i = 0; i < 1000000; i++);
    
    clock_t end = clock();
    return (long)(end - start);
}

int main() {
    // Criando uma instância da "interface"
    CalcTempoExecucao calcTempo;
    calcTempo.calcularTempoAlgoritmo = calcularTempoExemplo;

    // Usando a função
    long tempo = calcTempo.calcularTempoAlgoritmo();
    printf("Tempo de execução: %ld clock ticks\n", tempo);

    return 0;
}
