#include <stdio.h>
#include <ctype.h>

void paraMaiusculas(char *str) {
    int i = 0;
    while (str[i] != '\0') {

        str[i] = toupper(str[i]);

        i++;
    }
}

int main() {
    char texto[] = "iot com linguagem c";

    printf("Antes: %s\n", texto);

    paraMaiusculas(texto);

    printf("Depois: %s\n", texto);

    return 0;
}
