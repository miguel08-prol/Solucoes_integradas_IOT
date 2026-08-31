#include <stdio.h>

void encontrarMaiorMenor(int vetor[], int tamanho, int *max, int *min) {
    *max = vetor[0];
    *min = vetor[0];

    for (int i = 1; i < tamanho; i++) {
        if (vetor[i] > *max) {
            *max = vetor[i];
        }
        
        if (vetor[i] < *min) {
            *min = vetor[i];
        }
    }
}

int main() {
    int numeros[5] = {14, 42, 8, 29, 31};
    int maior, menor;

    encontrarMaiorMenor(numeros, 5, &maior, &menor);

    printf("Maior valor do vetor: %d\n", maior);
    printf("Menor valor do vetor: %d\n", menor);

    return 0;
}
