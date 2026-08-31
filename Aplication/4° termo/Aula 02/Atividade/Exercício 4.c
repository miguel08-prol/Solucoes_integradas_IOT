#include <stdio.h>

int main() {
  int a, b, c;
  int maior,menor;

  printf("Digite tres numeros inteiros separados por espaco: ");
  scanf("%d %d %d", &a, &b, &c);
 
  maior = a;
  menor = a;

 if (b > maior) {
    maior = b;
  }
  if (b < menor) {
    menor = b;
  }
  
  if (c > maior) {
    maior = c;
  }
  if (c < menor) {
    menor = c;
  }

  printf("Maior: %d\n", maior);
  printf("Menor: %d\n", menor);


  return 0;
}