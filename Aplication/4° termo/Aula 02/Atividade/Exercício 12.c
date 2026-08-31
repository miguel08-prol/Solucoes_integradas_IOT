#include <stdio.h>

struct Aluno {
    char nome[50];
    int matricula;
    float nota;
};

int main() {
    struct Aluno lista[3];
    int i;
    int indice_maior_nota = 0;

    for (i = 0; i < 3; i++) {
        printf("--- Cadastro do Aluno %d ---\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", lista[i].nome);
        printf("Matricula: ");
        scanf("%d", &lista[i].matricula);
        printf("Nota: ");
        scanf("%f", &lista[i].nota);
    }

    for (i = 1; i < 3; i++) {
        if (lista[i].nota > lista[indice_maior_nota].nota) {
            indice_maior_nota = i;
        }
    }

    printf("\n=== Aluno com a maior nota ===\n");
    printf("Nome: %s\n", lista[indice_maior_nota].nome);
    printf("Nota: %.2f\n", lista[indice_maior_nota].nota);

    return 0;
}
