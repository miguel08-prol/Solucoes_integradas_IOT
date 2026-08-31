#include <stdio.h>

void inverter(int *x, int *y) {
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int main() {
    int a = 10;
    int b = 20;

    printf("Antes da troca: a = %d, b = %d\n", a, b);

    inverter(&a, &b);

    printf("Depois da troca: a = %d, b = %d\n", a, b);

    return 0;
}
