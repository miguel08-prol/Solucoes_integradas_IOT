#include <stdio.h>
#include <string.h>

struct ContaBancaria {
    char titular[50];
    double saldo;
};

void exibirSaldo(struct ContaBancaria *conta) {
    printf("Titular: %s | Saldo: R$ %.2f\n", conta->titular, conta->saldo);
}

void depositar(struct ContaBancaria *conta, double valor) {
    if (valor > 0) {
        conta->saldo += valor;
        printf("Deposito de R$ %.2f realizado!\n", valor);
    }
}

void sacar(struct ContaBancaria *conta, double valor) {
    if (valor > conta->saldo) {
        printf("Erro: Saldo insuficiente para o saque de R$ %.2f\n", valor);
    } else if (valor > 0) {
        conta->saldo -= valor;
        printf("Saque de R$ %.2f realizado!\n", valor);
    }
}

int main() {
    struct ContaBancaria minhaConta;
    
    strcpy(minhaConta.titular, "Jose da Silva");
    minhaConta.saldo = 500.0;

    exibirSaldo(&minhaConta);
    depositar(&minhaConta, 200.0);
    sacar(&minhaConta, 800.0);
    sacar(&minhaConta, 300.0);
    exibirSaldo(&minhaConta);

    return 0;
}
