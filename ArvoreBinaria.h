#ifndef ARVOREBINARIA_H_INCLUDED
#define ARVOREBINARIA_H_INCLUDED


typedef struct arvore_binaria* Arvore;

Arvore t_new(char* prefixo, int tempovoo);
Arvore t_insert(Arvore arvore, char* prefixo, int tempovoo);
Arvore t_delete(Arvore arvore, char* prefixo);
char* t_search(Arvore arvore, char* prefixo, int count);
int t_get(Arvore arvore, char* prefixo);
int t_size(Arvore arvore);
Arvore ler_arquivo(Arvore arvore);
void t_visit_pre(Arvore arvore);
int menu(Arvore arvore);
int t_exit(Arvore arvore);
char encontra(Arvore arvore);
void add_elemento(Arvore arvore);
void t_imprime_ordem(Arvore arvore);
void delete_elemento(Arvore arvore);
#endif //ARVOREBINARIA_H_INCLUDEDs