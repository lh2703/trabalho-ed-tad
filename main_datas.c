#include <stdio.h>
#include <stdlib.h>
#include "abb.h"

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

int comparar_data(void *a, void *b) {
    Data *d1 = (Data *)a;
    Data *d2 = (Data *)b;
    if (d1->ano != d2->ano) return d1->ano - d2->ano;
    if (d1->mes != d2->mes) return d1->mes - d2->mes;
    return d1->dia - d2->dia;
}

void mostrar_chave_data(void *dado) {
    Data *d = (Data *)dado;
    printf("%02d/%02d/%04d ", d->dia, d->mes, d->ano);
}

void liberar_data(void *dado) {
    free(dado);
}

void mostrar_data(Data *d) {
    printf("Data: %02d/%02d/%04d\n", d->dia, d->mes, d->ano);
}

int main() {
    ABB *arvore = criar_ABB(comparar_data);
    int opcao;
    Data *d;

    do {
        printf("\n=== MENU DATA ===\n");
        printf("1 - Inserir Data\n");
        printf("2 - Remover Data\n");
        printf("3 - Verificar se Data existe\n");
        printf("4 - Buscar Data\n");
        printf("5 - Imprimir em Largura\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                d = malloc(sizeof(Data));
                printf("Dia: "); scanf("%d", &d->dia);
                printf("Mes: "); scanf("%d", &d->mes);
                printf("Ano: "); scanf("%d", &d->ano);
                inserir_ABB(arvore, d);
                printf("Inserido!\n");
                break;

            case 2:
                d = malloc(sizeof(Data));
                printf("Dia: "); scanf("%d", &d->dia);
                printf("Mes: "); scanf("%d", &d->mes);
                printf("Ano: "); scanf("%d", &d->ano);
                Data *removida = remover_ABB(arvore, d);
                if (removida) {
                    printf("Removida: ");
                    mostrar_data(removida);
                    free(removida);
                } else {
                    printf("Data não encontrada.\n");
                }
                free(d);
                break;

            case 3:
                d = malloc(sizeof(Data));
                printf("Dia: "); scanf("%d", &d->dia);
                printf("Mes: "); scanf("%d", &d->mes);
                printf("Ano: "); scanf("%d", &d->ano);
                if (existe_ABB(arvore, d))
                    printf("Existe.\n");
                else
                    printf("Não existe.\n");
                free(d);
                break;

            case 4:
                d = malloc(sizeof(Data));
                printf("Dia: "); scanf("%d", &d->dia);
                printf("Mes: "); scanf("%d", &d->mes);
                printf("Ano: "); scanf("%d", &d->ano);
                Data *encontrada = buscar_ABB(arvore, d);
                if (encontrada) {
                    mostrar_data(encontrada);
                } else {
                    printf("Data não encontrada.\n");
                }
                free(d);
                break;

            case 5:
                printf("Datas em largura: ");
                imprimir_largura(arvore, mostrar_chave_data);
                printf("\n");
                break;

            case 0:
                destruir_ABB(arvore, liberar_data);
                printf("Encerrando...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}
