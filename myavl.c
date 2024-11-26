#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreAVL.h"
#define TAMANHO_STRING 4

int main()
{
    char *string, *chave_char;
    char operacao;
    int chave, nivel = 0;
    size_t tamanho_string = TAMANHO_STRING * sizeof(char);

    avl_t *tree = cria_arvoreAVL(); 

    if ((string = (char*)malloc(TAMANHO_STRING + 1 * sizeof(char))) == NULL)
    {
        perror("erro ao alocar string");
        exit(1);
    }
    
    if ((chave_char = (char*)malloc(2 + 1 * sizeof(char))) == NULL)
    {
        perror("erro ao alocar chave");
        exit(1);
    }

    while (!feof(stdin))
    {
        getline(&string, &tamanho_string, stdin);

        chave_char[0] = string[2];
        chave_char[1] = string[3];
        chave = atoi(chave_char);
        
        operacao = string[0];
        
        switch (operacao)
        {
            case 'i':
                /*insere(chave);*/
                insereAVL(tree, tree->raiz, chave, &nivel);
                balanceamento(tree, tree->raiz);
            break;

            case 'r':
                removeAVL(tree, chave);
            break;
        }
    }

    imprime_arvore(tree->raiz);

    return 0;
}