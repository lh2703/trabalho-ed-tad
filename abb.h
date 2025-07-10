#ifndef ABB_H
#define ABB_H

typedef struct No {
    void *dado;
    struct No *esquerda;
    struct No *direita;
} No;

typedef int (*FuncaoComparar)(void *, void *);

typedef struct ABB {
    No *raiz;
    FuncaoComparar comparar;
} ABB;

ABB* criar_ABB(FuncaoComparar comparar);
void inserir_ABB(ABB *arvore, void *dado);
void* buscar_ABB(ABB *arvore, void *dado);
void emOrdem(ABB *arvore, void (*mostrar_dado)(void *));
void preOrdem(ABB *arvore, void (*mostrar_dado)(void *));
void posOrdem(ABB *arvore, void (*mostrar_dado)(void *));
void destruir_ABB(ABB *arvore, void (*liberar_dado)(void *));

#endif
