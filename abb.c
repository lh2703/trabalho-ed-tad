#include <stdio.h>
#include <stdlib.h>
#include "abb.h"

No* criar_no(void *dado) {
    No *no = malloc(sizeof(No));
    no->dado = dado;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

ABB* criar_ABB(FuncaoComparar comparar) {
    ABB *arvore = malloc(sizeof(ABB));
    arvore->raiz = NULL;
    arvore->comparar = comparar;
    return arvore;
}

No* inserir_no(No *raiz, void *dado, FuncaoComparar comparar) {
    if (raiz == NULL) return criar_no(dado);
    int cmp = comparar(dado, raiz->dado);
    if (cmp < 0) raiz->esquerda = inserir_no(raiz->esquerda, dado, comparar);
    else if (cmp > 0) raiz->direita = inserir_no(raiz->direita, dado, comparar);
    return raiz;
}

void inserir_ABB(ABB *arvore, void *dado) {
    arvore->raiz = inserir_no(arvore->raiz, dado, arvore->comparar);
}

void* buscar_no(No *raiz, void *dado, FuncaoComparar comparar) {
    if (raiz == NULL) return NULL;
    int cmp = comparar(dado, raiz->dado);
    if (cmp == 0) return raiz->dado;
    else if (cmp < 0) return buscar_no(raiz->esquerda, dado, comparar);
    else return buscar_no(raiz->direita, dado, comparar);
}

void* buscar_ABB(ABB *arvore, void *dado) {
    return buscar_no(arvore->raiz, dado, arvore->comparar);
}

int existe_ABB(ABB *arvore, void *dado) {
    return buscar_ABB(arvore, dado) != NULL;
}

No* encontrar_minimo(No *no) {
    while (no->esquerda != NULL)
        no = no->esquerda;
    return no;
}

No* remover_no(No *raiz, void *chave, FuncaoComparar comparar, void **removido) {
    if (raiz == NULL) return NULL;
    int cmp = comparar(chave, raiz->dado);
    if (cmp < 0) raiz->esquerda = remover_no(raiz->esquerda, chave, comparar, removido);
    else if (cmp > 0) raiz->direita = remover_no(raiz->direita, chave, comparar, removido);
    else {
        *removido = raiz->dado;
        if (raiz->esquerda == NULL) {
            No *temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        No *min = encontrar_minimo(raiz->direita);
        raiz->dado = min->dado;
        raiz->direita = remover_no(raiz->direita, min->dado, comparar, removido);
    }
    return raiz;
}

void* remover_ABB(ABB *arvore, void *chave) {
    void *removido = NULL;
    arvore->raiz = remover_no(arvore->raiz, chave, arvore->comparar, &removido);
    return removido;
}

void imprimir_largura(ABB *arvore, FuncaoMostrarChave mostrar_chave) {
    if (arvore->raiz == NULL) return;
    No **fila = malloc(sizeof(No *) * 1000);
    int inicio = 0, fim = 0;
    fila[fim++] = arvore->raiz;
    while (inicio < fim) {
        No *atual = fila[inicio++];
        mostrar_chave(atual->dado);
        if (atual->esquerda) fila[fim++] = atual->esquerda;
        if (atual->direita) fila[fim++] = atual->direita;
    }
    free(fila);
}

void destruir_no(No *raiz, FuncaoLiberar liberar_dado) {
    if (raiz != NULL) {
        destruir_no(raiz->esquerda, liberar_dado);
        destruir_no(raiz->direita, liberar_dado);
        liberar_dado(raiz->dado);
        free(raiz);
    }
}

void destruir_ABB(ABB *arvore, FuncaoLiberar liberar_dado) {
    destruir_no(arvore->raiz, liberar_dado);
    free(arvore);
}
