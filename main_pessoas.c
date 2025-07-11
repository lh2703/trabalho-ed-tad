#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abb.h"

typedef struct {
    char nome[50];
    int idade;
} Pessoa;

int comparar_pessoa(void *a, void *b) {
    Pessoa *p1 = (Pessoa *)a;
    Pessoa *p2 = (Pessoa *)b;
    return strcmp(p1->nome, p2->nome);
}

void mostrar_chave_pessoa(void *dado) {
    Pessoa *p = (Pessoa *)dado;
    printf("%s ", p->nome);
}

void liberar_pessoa(void *dado) {
    free(dado);
}

void mostrar_pessoa(Pessoa *p) {
    printf("Nome: %s | Idade: %d\n", p->nome, p->idade);
}

int main() {
    ABB *arvore = criar_ABB(comparar_pessoa);
    int opcao;
    char nome[50];
    Pessoa *p;

    do {
        printf("\n=== MENU PESSOA ===\n");
        printf("1 - Inserir Pessoa\n");
        printf("2 - Remover Pessoa\n");
        printf("3 - Verificar se Pessoa existe\n");
        printf("4 - Buscar Pessoa\n");
        printf("5 - Imprimir em Largura\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                p = malloc(sizeof(Pessoa));
                printf("Nome: ");
                scanf("%s", p->nome);
                printf("Idade: ");
                scanf("%d", &p->idade);
                inserir_ABB(arvore, p);
                printf("Inserido!\n");
                break;

            case 2:
                printf("Nome da Pessoa para remover: ");
                scanf("%s", nome);
                p = malloc(sizeof(Pessoa));
                strcpy(p->nome, nome);
                Pessoa *removida = remover_ABB(arvore, p);
                if (removida) {
                    printf("Removida: ");
                    mostrar_pessoa(removida);
                    free(removida);
                } else {
                    printf("Pessoa não encontrada.\n");
                }
                free(p);
                break;

            case 3:
                printf("Nome da Pessoa para verificar: ");
                scanf("%s", nome);
                p = malloc(sizeof(Pessoa));
                strcpy(p->nome, nome);
                if (existe_ABB(arvore, p))
                    printf("Existe.\n");
                else
                    printf("Não existe.\n");
                free(p);
                break;

            case 4:
                printf("Nome da Pessoa para buscar: ");
                scanf("%s", nome);
                p = malloc(sizeof(Pessoa));
                strcpy(p->nome, nome);
                Pessoa *encontrada = buscar_ABB(arvore, p);
                if (encontrada) {
                    mostrar_pessoa(encontrada);
                } else {
                    printf("Pessoa não encontrada.\n");
                }
                free(p);
                break;

            case 5:
                printf("Pessoas em largura: ");
                imprimir_largura(arvore, mostrar_chave_pessoa);
                printf("\n");
                break;

            case 0:
                destruir_ABB(arvore, liberar_pessoa);
                printf("Encerrando...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}
