#include <stdio.h>

int main() {
    int n, i;
    int termo1 = 0, termo2 = 1, proximo;

    printf("Quantos termos da sequencia voce quer ver? ");
    scanf("%d", &n);

    printf("Sequencia de Fibonacci: ");

    for (i = 1; i <= n; i++) {
        if (i == 1) {
            printf("%d ", termo1);
            continue;
        }
        if (i == 2) {
            printf("%d ", termo2);
            continue;
        }

        proximo = termo1 + termo2;
        printf("%d ", proximo);

       termo1 = termo2;
       termo2 = proximo;
    }

    printf("\n");
    return 0;
}
