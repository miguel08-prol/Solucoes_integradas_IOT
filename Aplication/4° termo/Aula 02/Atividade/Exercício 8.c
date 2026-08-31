#include <stdio.h>

int main() {
    int numeros[5];
    int i;

    printf("Digite 5 numeros inteiros:\n");
    for (i = 0; i < 5; i++) {
        scanf("%d", &numeros[i]);
    }

    printf("\nArray na ordem inversa:\n");
    

    for (i = 4; i >= 0 ; i--) {
        printf("%d ", numeros[i]);
    }

    printf("\n");
    return 0;
}