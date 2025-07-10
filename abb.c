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
    if (raiz == NULL) {
        return criar_no(dado);
    }

    int cmp = comparar(dado, raiz->dado);
    if (cmp < 0) {
        raiz->esquerda = inserir_no(raiz->esquerda, dado, comparar);
    } else if (cmp > 0) {
        raiz->direita = inserir_no(raiz->direita, dado, comparar);
    }

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

static void emOrdem_no(No *raiz, void (*mostrar_dado)(void *)) {
    if (raiz != NULL) {
        emOrdem_no(raiz->esquerda, mostrar_dado);
        mostrar_dado(raiz->dado);
        emOrdem_no(raiz->direita, mostrar_dado);
    }
}

void emOrdem(ABB *arvore, void (*mostrar_dado)(void *)) {
    emOrdem_no(arvore->raiz, mostrar_dado);
}

static void preOrdem_no(No *raiz, void (*mostrar_dado)(void *)) {
    if (raiz != NULL) {
        mostrar_dado(raiz->dado);
        preOrdem_no(raiz->esquerda, mostrar_dado);
        preOrdem_no(raiz->direita, mostrar_dado);
    }
}

void preOrdem(ABB *arvore, void (*mostrar_dado)(void *)) {
    preOrdem_no(arvore->raiz, mostrar_dado);
}

static void posOrdem_no(No *raiz, void (*mostrar_dado)(void *)) {
    if (raiz != NULL) {
        posOrdem_no(raiz->esquerda, mostrar_dado);
        posOrdem_no(raiz->direita, mostrar_dado);
        mostrar_dado(raiz->dado);
    }
}

void posOrdem(ABB *arvore, void (*mostrar_dado)(void *)) {
    posOrdem_no(arvore->raiz, mostrar_dado);
}

void destruir_no(No *raiz, void (*liberar_dado)(void *)) {
    if (raiz != NULL) {
        destruir_no(raiz->esquerda, liberar_dado);
        destruir_no(raiz->direita, liberar_dado);
        liberar_dado(raiz->dado);
        free(raiz);
    }
}

void destruir_ABB(ABB *arvore, void (*liberar_dado)(void *)) {
    destruir_no(arvore->raiz, liberar_dado);
    free(arvore);
}
