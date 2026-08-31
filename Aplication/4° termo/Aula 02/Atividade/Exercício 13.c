#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i;
    int *vetor;
    int soma = 0;

    printf("Digite o tamanho do array (N): ");
    scanf("%d", &n);

    vetor = (int *) malloc(n * sizeof(int));

    if (vetor == NULL) {
        printf("Erro: Memoria insuficiente!\n");
        return 1; 
    }

    printf("Digite os %d elementos:\n", n);
    for (i = 0; i < n; i++) {
        printf("Elemento [%d]: ", i);
        scanf("%d", &vetor[i]);
        soma += vetor[i];
    }

    printf("\nA soma de todos os elementos eh: %d\n", soma);

    free(vetor);
    printf("Memoria liberada com sucesso!\n");

    return 0;
}
