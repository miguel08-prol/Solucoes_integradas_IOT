#include <stdio.h>

int main() {
    float celsius, fahrenheit, kelvin;

    printf("Digite a temperatura em Celsius: ");
    scanf("%f", &celsius);

    fahrenheit = (celsius*9/5) + 32;
    kelvin = celsius + 273.15;

    printf("Temperatura em fahrenheit: %.2f\n",fahrenheit); 
    printf("Temperatura em kelvin: %.2f\n",kelvin);

    return 0;
}