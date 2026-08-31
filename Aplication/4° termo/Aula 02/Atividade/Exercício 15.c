#include <stdio.h>

struct Veiculo {
    void (*exibirInfo)(void *self); 
};

struct Carro {
    struct Veiculo base;
    int portas;
};

struct Moto {
    struct Veiculo base;
    int cilindradas;
};

void infoCarro(void *self) {
    struct Carro *c = (struct Carro *)self;
    printf("Veiculo: Carro | Quantidade de portas: %d\n", c->portas);
}

void infoMoto(void *self) {
    struct Moto *m = (struct Moto *)self;
    printf("Veiculo: Moto | Cilindradas: %d cc\n", m->cilindradas);
}

int main() {
    struct Carro meuCarro;
    meuCarro.portas = 4;
    meuCarro.base.exibirInfo = infoCarro;

    struct Moto minhaMoto;
    minhaMoto.cilindradas = 600;
    minhaMoto.base.exibirInfo = infoMoto;

    struct Veiculo *v1 = (struct Veiculo *)&meuCarro;
    struct Veiculo *v2 = (struct Veiculo *)&minhaMoto;

    v1->exibirInfo(&meuCarro);
    v2->exibirInfo(&minhaMoto);

    return 0;
}
