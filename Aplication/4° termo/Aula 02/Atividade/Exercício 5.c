#include <stdio.h>

int main() {
    int n, i;
    int fatorial = 1;

    printf("Digite um numero inteiro positivo: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        fatorial = fatorial * i;
    }

    printf("O fatorial de %d eh: %d\n", n, fatorial);

    return 0;
}
