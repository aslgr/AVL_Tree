#include <stdio.h>
#include <stdlib.h>
#include "arvoreAVL.h"

avl_t *cria_arvoreAVL()
{
    avl_t *tree;
    if ((tree = (avl_t*) malloc (sizeof(avl_t))) == NULL)
        return NULL;

    tree->raiz = NULL;

    return tree;
}

t_No *criaNo(int chave, int *nivel)
{
    t_No *no;
    if ((no = (t_No *) malloc (sizeof(t_No))) == NULL)
        return NULL;
    
    no->valor = chave;
    no->nivel = *nivel;
    *nivel = 0;
    no->altura = 1;
    no->esq = no->pai = no->dir = NULL;

    return no;
}

t_No *Minimo(t_No *no)
{
    if (no->esq == NULL)
        return no;

    return Minimo(no->esq);
}

t_No *Maximo(t_No *no)
{
    if (no->dir == NULL)
        return no;

    return Minimo(no->dir);
}

void decrementa_rot(t_No *no)
{
    if (no == NULL)
        return;

    decrementa_rot(no->esq);
    
    no->nivel--;

    decrementa_rot(no->dir);
}

void incrementa_rot(t_No *no)
{
    if (no == NULL)
        return;

    incrementa_rot(no->esq);
    
    no->nivel++;

    incrementa_rot(no->dir);
}

t_No *incrementa_tamanho(avl_t *tree, t_No *no, int chave)
{
    if (no->valor == chave)
        return no;

    if (no != tree->raiz)
        no->altura++;

    if (chave < no->valor)
        return incrementa_tamanho(tree, no->esq, chave);
    
    return incrementa_tamanho(tree, no->dir, chave);
}

t_No *rot_Esquerda(avl_t *tree, t_No *no)
{
    t_No *aux;
    aux = no->dir;

    if (tree->raiz == no)
        tree->raiz = aux;

    if (aux->esq != NULL)
        aux->esq->pai = no;

    no->dir = aux->esq;

    aux->pai = no->pai;

    if (no->pai != NULL)
    {
        if (no->pai->esq == no)
            no->pai->esq = aux;
        else
            no->pai->dir = aux;
    }

    no->pai = aux;

    aux->esq = no;

    aux->nivel--;
    no->nivel++;

    incrementa_rot(no->esq);
    decrementa_rot(aux->dir);

    return aux;
}

t_No *rot_Direita(avl_t *tree, t_No *no)
{
    t_No *aux;
    aux = no->esq;

    if (tree->raiz == no)
        tree->raiz = aux;

    if (aux->dir != NULL)
        aux->dir->pai = no;

    no->esq = aux->dir;

    aux->pai = no->pai;

    if (no->pai != NULL)
    {
        if (no->pai->esq == no)
            no->pai->esq = aux;
        else
            no->pai->dir = aux;
    }

    no->pai = aux;

    aux->dir = no;

    aux->nivel--;
    no->nivel++;

    incrementa_rot(no->dir);
    decrementa_rot(aux->esq);

    return aux;
}

t_No *insereAVL(avl_t *tree, t_No *no,  int chave, int *nivel)
{
    t_No *aux;

    if (tree->raiz == NULL)
    {
        aux = criaNo(chave, nivel);
        tree->raiz = aux;

        return aux;
    }

    if (no == NULL)
        return criaNo(chave, nivel);
    else
    {
        (*nivel)++;
        if (chave < no->valor)
        {
            no->esq = insereAVL(tree, no->esq, chave, nivel);
            no->esq->pai = no;

            if (no->esq->altura == no->altura)
                incrementa_tamanho(tree, tree->raiz, chave);
        }
        else
        {
            no->dir = insereAVL(tree, no->dir, chave, nivel);
            no->dir->pai = no;

            if (no->dir->altura == no->altura)
                incrementa_tamanho(tree, tree->raiz, chave);
        }
    }

    if (tree->raiz->esq == NULL)
    {
        if (tree->raiz->dir == NULL)
            tree->raiz->altura = 1;
        else
            tree->raiz->altura = tree->raiz->dir->altura + 1;
    }
    else if (tree->raiz->dir == NULL)
    {
        tree->raiz->altura = tree->raiz->esq->altura + 1;
    }
    else
        tree->raiz->altura = maior(tree->raiz->esq->altura, tree->raiz->dir->altura) + 1;

    return no;
}

int maior(int a, int b)
{
    if (a > b)
        return a;
    
    return b;
}

int fator_balanceamento(t_No *no)
{
    int fb;

    if (no->esq == NULL)
    {
        if (no->dir == NULL)
            fb = 0;
        else
            fb = -1 * (no->dir->altura);
    }
    else if (no->dir == NULL)
    {
        fb = no->esq->altura;
    }
    else
        fb = (no->esq->altura)-(no->dir->altura);

    return fb;
}

t_No *balanceamento(avl_t *tree, t_No *no)
{
    int fb;

    t_No *aux;

    if (no == NULL)
        return NULL;

    balanceamento(tree, no->esq);
    balanceamento(tree, no->dir);

    fb = fator_balanceamento(no);

    if (fb < (-1))
    {
        fb = fator_balanceamento(no->dir);

        no->altura-=2;

        if (fb <= 0)
        {
            aux = no->dir;
            rot_Esquerda(tree, no);
        }
        else
        {
            aux = no->dir->esq;
            no->dir->altura--;
            no->dir->esq->altura++;
            rot_Direita(tree, no->dir);
            rot_Esquerda(tree, no);
        }

        while (aux->pai != tree->raiz)
        {
            aux = aux->pai;
            aux->altura--;
        }

        if (tree->raiz->esq == NULL)
        {
            if (tree->raiz->dir == NULL)
                tree->raiz->altura = 1;
            else
                tree->raiz->altura = tree->raiz->dir->altura + 1;
        }
        else if (tree->raiz->dir == NULL)
        {
            tree->raiz->altura = tree->raiz->esq->altura + 1;
        }
        else
            tree->raiz->altura = maior(tree->raiz->esq->altura, tree->raiz->dir->altura) + 1;

        return balanceamento(tree, tree->raiz);
    }
    else if (fb > 1)
    {
        fb = fator_balanceamento(no->esq);

        no->altura-=2;

        if (fb >= 0)
        {
            aux = no->esq;
            rot_Direita(tree, no);
        }
        else
        {
            aux = no->esq->dir;
            no->esq->altura--;
            no->esq->dir->altura++;
            rot_Esquerda(tree, no->esq);
            rot_Direita(tree, no);
        }

        while (aux->pai != tree->raiz)
        {
            aux = aux->pai;
            aux->altura--;
        }

        if (tree->raiz->esq == NULL)
        {
            if (tree->raiz->dir == NULL)
                tree->raiz->altura = 1;
            else
                tree->raiz->altura = tree->raiz->dir->altura + 1;
        }
        else if (tree->raiz->dir == NULL)
        {
            tree->raiz->altura = tree->raiz->esq->altura + 1;
        }
        else
            tree->raiz->altura = maior(tree->raiz->esq->altura, tree->raiz->dir->altura) + 1;

        return balanceamento(tree, tree->raiz);
    }

    return NULL;
}

t_No *removeAVL(avl_t *tree, int chave)
{
    t_No *no, *s;

    if ((no = buscaAVL(tree->raiz, chave)) == NULL)
        return NULL;

    if (no->esq == NULL)
    {
        ajusta_no_pai(tree, no, no->dir);
        free(no);
    }
    else if (no->dir == NULL)
    {
        ajusta_no_pai(tree, no, no->esq);
        free(no);
    }
    else
    {
        s = Minimo(no->dir);
        ajusta_no_pai(tree, s, s->dir);
        s->esq = no->esq;
        s->dir = no->dir;
        ajusta_no_pai(tree, no, s);
        free(no);

        return s;
    }

    return NULL;
}

void ajusta_no_pai(avl_t *tree, t_No *no, t_No *novo)
{
    if (no->pai != NULL)
    {
        if (no->pai->esq == no)
            no->pai->esq = novo;
        else
            no->pai->dir = novo;
        
        if (novo != NULL)
            novo->pai = no->pai;
    }
    else
    {
        tree->raiz = novo;
    }
}

t_No *buscaAVL(t_No *no, int chave)
{
    if (no == NULL)
    {
        printf("Chave %d nao encontrada\n", chave);
        return NULL;
    }

    if (no->valor == chave)
        return no;

    if (chave < no->valor)
        return buscaAVL(no->esq, chave);
    
    return buscaAVL(no->dir, chave);
}

void imprime_arvore(t_No *no)
{
    if (no == NULL)
        return;

    imprime_arvore(no->esq);
    
    printf("%d,%d", no->valor, no->nivel);

    imprime_arvore(no->dir);
}

avl_t *destroiAVL(avl_t *tree, t_No *no)
{
    if (no == NULL)
        return NULL;

    destroiAVL(tree, no->esq);
    destroiAVL(tree, no->dir);

    if (no == tree->raiz)
    {
        free(no);
        free(tree);
    }
    else
        free(no);
    
    return NULL;
}