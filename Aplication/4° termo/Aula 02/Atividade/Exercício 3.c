#include <stdio.h>

int main() {
  int numero;

  printf("Digite um número: ");
  scanf("%d", &numero);
  
  printf("O número %d é: %s\n",numero, (numero % 2 == 0) ? "Número Par" : "Numero Impar");

  return 0;
}