#include <stdio.h>
#include <stdlib.h>
#include "abb.h"

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

int comparar_datas(void *a, void *b) {
    Data *d1 = (Data *)a;
    Data *d2 = (Data *)b;

    if (d1->ano != d2->ano)
        return d1->ano - d2->ano;
    if (d1->mes != d2->mes)
        return d1->mes - d2->mes;
    return d1->dia - d2->dia;
}

void mostrar_data(void *dado) {
    Data *d = (Data *)dado;
    printf("%02d/%02d/%04d\n", d->dia, d->mes, d->ano);
}

void liberar_data(void *dado) {
    free(dado);
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main() {
    ABB *arvore = criar_ABB(comparar_datas);
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1 - Inserir data\n");
        printf("2 - Listar datas em ordem\n");
        printf("3 - Listar datas em pre-ordem\n");
        printf("4 - Listar datas em pos-ordem\n");
        printf("5 - Buscar data\n");
        printf("6 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limpar_buffer();

        if (opcao == 1) {
            Data *d = malloc(sizeof(Data));
            if (!d) {
                printf("Erro de alocacao!\n");
                continue;
            }

            printf("Digite o dia: ");
            scanf("%d", &d->dia);
            limpar_buffer();

            printf("Digite o mes: ");
            scanf("%d", &d->mes);
            limpar_buffer();

            printf("Digite o ano: ");
            scanf("%d", &d->ano);
            limpar_buffer();

            inserir_ABB(arvore, d);
            printf("Data inserida com sucesso.\n");

        } else if (opcao == 2) {
            printf("\nDatas em ordem:\n");
            emOrdem(arvore, mostrar_data);

        } else if (opcao == 3) {
            printf("\nDatas em pre-ordem:\n");
            preOrdem(arvore, mostrar_data);

        } else if (opcao == 4) {
            printf("\nDatas em pos-ordem:\n");
            posOrdem(arvore, mostrar_data);

        } else if (opcao == 5) {
            Data chave;
            printf("Digite o dia para buscar: ");
            scanf("%d", &chave.dia);
            limpar_buffer();
            printf("Digite o mes para buscar: ");
            scanf("%d", &chave.mes);
            limpar_buffer();
            printf("Digite o ano para buscar: ");
            scanf("%d", &chave.ano);
            limpar_buffer();

            Data *resultado = buscar_ABB(arvore, &chave);
            if (resultado)
                printf("Data encontrada: %02d/%02d/%04d\n", resultado->dia, resultado->mes, resultado->ano);
            else
                printf("Data nao encontrada\n");

        } else if (opcao == 6) {
            printf("Saindo...\n");
        } else {
            printf("Opcao invalida, tente novamente.\n");
        }

    } while (opcao != 6);

    destruir_ABB(arvore, liberar_data);
    return 0;
}
