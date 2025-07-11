#ifndef ABB_H
#define ABB_H

typedef struct No {
    void *dado;
    struct No *esquerda;
    struct No *direita;
} No;

typedef int (*FuncaoComparar)(void *, void *);
typedef void (*FuncaoMostrarChave)(void *);
typedef void (*FuncaoLiberar)(void *);

typedef struct ABB {
    No *raiz;
    FuncaoComparar comparar;
} ABB;

ABB* criar_ABB(FuncaoComparar comparar);
void inserir_ABB(ABB *arvore, void *dado);
void* remover_ABB(ABB *arvore, void *chave);
int existe_ABB(ABB *arvore, void *chave);
void* buscar_ABB(ABB *arvore, void *chave);
void imprimir_largura(ABB *arvore, FuncaoMostrarChave mostrar_chave);
void destruir_ABB(ABB *arvore, FuncaoLiberar liberar_dado);

#endif
