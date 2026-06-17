#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int   id;
    float preco;
} Produto;

void aplicar_desconto(Produto *p, float percentual) {
    p->preco = p->preco * (1.0f - percentual / 100.0f);
}

void imprimir_produtos(Produto *ptr, int quantidade) {
    printf("\n%-5s %-10s\n", "ID", "Preco (R$)");
    printf("%-5s %-10s\n", "---", "----------");
    for (int i = 0; i < quantidade; i++) {
        printf("%-5d R$ %.2f\n", (ptr + i)->id, (ptr + i)->preco);
    }
    printf("\n");
}

int main(void) {

    printf("=== ATIVIDADE 1: Ponteiro para float ===\n");
    float preco = 100.0f;
    float *ptr_preco = &preco;
    *ptr_preco = *ptr_preco * 1.10f;
    printf("Preco apos aumento de 10%%: R$ %.2f\n\n", preco);

    printf("=== ATIVIDADE 2: Passagem por referencia ===\n");
    Produto prod2 = {0, 200.0f};
    printf("Preco original: R$ %.2f\n", prod2.preco);
    aplicar_desconto(&prod2, 15.0f);
    printf("Preco apos desconto de 15%%: R$ %.2f\n\n", prod2.preco);

    printf("=== ATIVIDADE 3: Ponteiro para struct ===\n");
    Produto produto3 = {1, 350.00f};
    Produto *ptr3 = &produto3;
    printf("Antes do desconto: ID=%d | Preco=R$ %.2f\n", ptr3->id, ptr3->preco);
    aplicar_desconto(ptr3, 20.0f);
    printf("Apos desconto de 20%%:  ID=%d | Preco=R$ %.2f\n\n", ptr3->id, ptr3->preco);

    printf("=== ATIVIDADE 4: Array estatico (3 produtos) ===\n");
    Produto estoque[3] = {
        {101, 49.90f},
        {102, 129.99f},
        {103, 299.00f}
    };
    printf("Estoque inicial:");
    imprimir_produtos(estoque, 3);
    for (int i = 0; i < 3; i++) {
        aplicar_desconto(estoque + i, 10.0f);
    }
    printf("Estoque apos desconto de 10%%:");
    imprimir_produtos(estoque, 3);

    printf("=== ATIVIDADE 5: Alocacao dinamica (malloc/free) ===\n");
    int n;
    printf("Quantos produtos deseja cadastrar? ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Quantidade invalida.\n");
        return 1;
    }

    Produto *catalogo = (Produto *) malloc(n * sizeof(Produto));
    if (catalogo == NULL) {
        printf("Erro: memoria insuficiente.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        (catalogo + i)->id = 200 + i + 1;
        printf("Preco do produto %d: R$ ", (catalogo + i)->id);
        if (scanf("%f", &(catalogo + i)->preco) != 1) {
            printf("Entrada invalida.\n");
            free(catalogo);
            return 1;
        }
    }

    printf("\nProdutos cadastrados:");
    imprimir_produtos(catalogo, n);

    free(catalogo);
    catalogo = NULL;

    printf("Memoria liberada com sucesso.\n");
    return 0;
}
