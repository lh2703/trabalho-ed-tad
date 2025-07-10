#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abb.h"

typedef struct {
    char nome[50];
    int idade;
} Pessoa;

int comparar_pessoas(void *a, void *b) {
    Pessoa *p1 = (Pessoa *)a;
    Pessoa *p2 = (Pessoa *)b;
    return strcmp(p1->nome, p2->nome);
}

void mostrar_pessoa(void *dado) {
    Pessoa *p = (Pessoa *)dado;
    printf("Nome: %s | Idade: %d\n", p->nome, p->idade);
}

void liberar_pessoa(void *dado) {
    free(dado);
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main() {
    ABB *arvore = criar_ABB(comparar_pessoas);

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1 - Inserir pessoa\n");
        printf("2 - Listar pessoas em ordem\n");
        printf("3 - Listar pessoas em pre-ordem\n");
        printf("4 - Listar pessoas em pos-ordem\n");
        printf("5 - Buscar pessoa por nome\n");
        printf("6 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limpar_buffer();

        if (opcao == 1) {
            Pessoa *p = malloc(sizeof(Pessoa));
            if (!p) {
                printf("Erro de alocacao!\n");
                continue;
            }

            printf("Digite o nome: ");
            fgets(p->nome, 50, stdin);
            p->nome[strcspn(p->nome, "\n")] = '\0'; // remove \n

            printf("Digite a idade: ");
            scanf("%d", &p->idade);
            limpar_buffer();

            inserir_ABB(arvore, p);
            printf("Pessoa inserida com sucesso.\n");

        } else if (opcao == 2) {
            printf("\nPessoas em ordem:\n");
            emOrdem(arvore, mostrar_pessoa);

        } else if (opcao == 3) {
            printf("\nPessoas em pre-ordem:\n");
            preOrdem(arvore, mostrar_pessoa);

        } else if (opcao == 4) {
            printf("\nPessoas em pos-ordem:\n");
            posOrdem(arvore, mostrar_pessoa);

        } else if (opcao == 5) {
            char nome_busca[50];
            printf("Digite o nome para buscar: ");
            fgets(nome_busca, 50, stdin);
            nome_busca[strcspn(nome_busca, "\n")] = '\0';

            Pessoa chave;
            strcpy(chave.nome, nome_busca);

            Pessoa *resultado = buscar_ABB(arvore, &chave);
            if (resultado)
                printf("Pessoa encontrada: %s (%d anos)\n", resultado->nome, resultado->idade);
            else
                printf("Pessoa nao encontrada\n");

        } else if (opcao == 6) {
            printf("Saindo...\n");
        } else {
            printf("Opcao invalida, tente novamente.\n");
        }

    } while (opcao != 6);

    destruir_ABB(arvore, liberar_pessoa);
    return 0;
}
