/*header da minha arvore AVL*/

/*o nodo da arvore apresenta um valor, um nivel,
uma altura e possiveis filhos e pai*/

typedef struct No {
    int valor;
    int nivel;
    int altura;
    struct No *esq, *pai, *dir;
} t_No;

typedef struct avl {
    t_No *raiz;
} avl_t;


/*cria uma arvore vazia e a retorna...
se falhar retorna NULL*/

avl_t *cria_arvoreAVL();


/*cria um nodo da arvore*/

t_No *criaNo(int chave, int *nivel);


/*encontra o menor ou o maior valor
da arvore*/

t_No *Minimo(t_No *no);

t_No *Maximo(t_No *no);


/*rotacionam o nodo para esquerda
ou para direita*/

t_No *rot_Esquerda(avl_t *tree, t_No *no);

t_No *rot_Direita(avl_t *tree, t_No *no);


/*insere um nodo na folha*/

t_No *insereAVL(avl_t *tree, t_No *no,  int chave, int *nivel);


/*para a AVL, é utilizado pelo balanceamento para
atribuir corretamente o valor da altura da raiz da arvore,
com base em seus filhos*/

int maior(int a, int b);


/*calcula se ha a necessidade de balancear
um nodo e como balancear*/

int fator_balanceamento(t_No *no);


/*balancea a arvore*/

t_No *balanceamento(avl_t *tree, t_No *no);


/*remove a chave com base no algoritmo AVL*/

t_No *removeAVL(avl_t *tree, int chave);


/*faz os ajustes necessarios na remocao*/

void ajusta_no_pai(avl_t *tree, t_No *no, t_No *novo);


/*busca por uma chave na arvore AVL*/

t_No *buscaAVL(t_No *no, int chave);


/*imprime a arvore*/

void imprime_arvore(t_No *no);


/*remove todos os elementos da arvore, libera espaco
e retorna NULL*/

avl_t *destroiAVL(avl_t *tree, t_No *no);