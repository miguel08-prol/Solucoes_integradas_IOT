#include <stdio.h>

int main() {

    float nota1, nota2, nota3, nota4, media;

    printf("Digite as 4 notas: ");
    scanf("%f %f %f %f", &nota1, &nota2, &nota3, &nota4);

    media = (nota1 + nota2 + nota3 + nota4) / 4.0;
    printf("Media: %.2f\n", media);

    if (media >= 7.0) {
        printf("Aprovado\n");
    }else if (media >= 5.0) {
        printf("Em Recuperação\n");
    }
    else {
        printf("Reprovado");
    }

    return 0;
}
