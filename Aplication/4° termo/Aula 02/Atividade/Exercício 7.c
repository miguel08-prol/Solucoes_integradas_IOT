#include <stdio.h>

int main() {
    int vetor[10];
    int i, numero_busca;
    int encontrado = -1;

    printf("Digite 10 numeros inteiros:\n");
    for (i = 0; i < 10; i++) {
        printf("Posicao [%d]: ", i);
        scanf("%d", &vetor[i]);
    }

    printf("\nDigite o valor que deseja buscar: ");
    scanf("%d", &numero_busca);

    for (i = 0; i < 10; i++) {
        if (vetor[i] == numero_busca) {
            encontrado = i;
            break;
        }
    }

    // Exibindo o resultado
    if (encontrado != -1) {
        printf("O valor %d foi encontrado no indice %d.\n", numero_busca, encontrado);
    } else {
        printf("O valor %d nao foi encontrado no vetor.\n", numero_busca);
    }

    return 0;
}
