#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreBinaria.h"



struct arvore_binaria{
	
	char prefixo[8];
	int tempovoo;
	Arvore left, right;

};

void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

/* Cria uma nova arvore*/
Arvore t_new(char* prefixo, int tempovoo){
	Arvore arvore = (Arvore)malloc(sizeof(struct arvore_binaria));
	strncpy(arvore->prefixo,prefixo,8);
	arvore -> tempovoo = tempovoo;
	arvore -> left = NULL;
	arvore -> right = NULL;
	return arvore;

}

/*Adiciona um novo elemento na arvore*/
Arvore t_insert(Arvore arvore, char* prefixo, int tempovoo){
	if(arvore == NULL)
		return t_new(prefixo, tempovoo);
	if(!strcmp(arvore->prefixo, prefixo))//Compara igualdade entre as strings 
		return arvore;
	if(strcmp(arvore->prefixo,prefixo)>0)
		arvore->left = t_insert(arvore->left,prefixo,tempovoo);
	if(strcmp(arvore->prefixo,prefixo)<0)
		arvore->right = t_insert(arvore->right,prefixo,tempovoo);
	return arvore;
}

/*Apaga arvore Binaria*/
void t_free(Arvore arvore){
	if(arvore == NULL)
		return;
	t_free(arvore->left);
	t_free(arvore->right);
	free(arvore);
}

/*Procura um elemento da arvore usando o prefixo, e remove*/
Arvore t_delete(Arvore arvore, char* prefixo){
	if(arvore == NULL)
		return arvore;
	if(!strcmp(arvore->prefixo,prefixo)){
		Arvore tmp;
		if(arvore->right == NULL){/*Nao tem filho a direita*/
			tmp = arvore->left;
		}
		if(arvore->left == NULL){/*Nao tem filho a esquerda*/
			tmp = arvore->right;
		}
		else/*Tem os dois filhos*/
		{
			tmp = arvore->left;/*Vai para a esquerda*/
			while(arvore->right != NULL){
				tmp = arvore->right;/*Encontra o mais a direita*/
			}
			tmp->right = arvore->right;/*Funde as arvores*/
			tmp->left = arvore->left;
		}
		free(arvore);
		return tmp;
	}
	if(strcmp(arvore->prefixo,prefixo)>0)
		arvore->left = t_delete(arvore->left,prefixo);
	if(strcmp(arvore->prefixo,prefixo)<0)
		arvore->right = t_delete(arvore->right,prefixo);
	return arvore;
}	


/*Procura um elemento da arvore pelo prefixo, e mostra o numero de comparaçoes feitas*/
char* t_search(Arvore arvore, char* prefixo, int count){
	int cont = 0;
	if(arvore == NULL) {// Arvore vazia
		printf("arvore nula\n");
		return 0;
	}
	/*Se os prfixo procurado, for igual ao prefixo contindo na arvore*/
	if(!strcmp(arvore->prefixo,prefixo)) {//strcmp - funçao para comparar strings, quando com ! retorn 1;

		printf("Found it: %s\nNumero de saltos: %d\n", prefixo, count);
		return "found";
	}/*Se o prefixo for maior que o procurado*/
	else if(strcmp(arvore->prefixo,prefixo)>0) {//vai para a esquerda 
		printf("esquerda\n ");
		return t_search(arvore->left,prefixo,count+1);
	}/*Se o prefixo for menor que o procurado*/
	else if(strcmp(arvore->prefixo,prefixo)<0) {
		printf("direita\n ");
		return t_search(arvore->right,prefixo,count+1);		
	}
	return "not_found";
}


/*tamanho da arvore*/
int t_size(Arvore arvore){
	if(arvore == NULL)
		return 0;
	return 1 + t_size(arvore->left) + t_size(arvore->right);
}


/*Le o arquivo txt*/
Arvore ler_arquivo(Arvore arvore){

	int tempovoo;
	char prefixo[8]; prefixo[7] = '\0';
	char tempo[4]; tempo[3] = '\0';
	FILE *fptr; /*Ponteiro para arquivo*/
	/*abre arquivo para ler em modo texto*/
	fptr = fopen("voos.txt","r");
	char ch;
	if(fptr == NULL){
		printf("\nErro, nao foi possivel abrir o arquivo\n");
		return arvore;
	}

	int cont = 0;
	/*Enquanto o arquivo nao chegar ao final*/
	while((ch =fgetc(fptr)) != EOF){
		
		if (cont < 7) {
			prefixo[cont] = ch;
		}
		
		cont++;// Contador para ir ao valor do tempo 
		if(cont > 8 && cont < 12){
			tempo[cont-9] = ch;
		}//Se o arquivo chegar no final, ou salatar linha
		if(ch == '\0' || ch == '\n'){
			tempovoo = atoi(tempo);// transforma char para int
			arvore = t_insert(arvore, prefixo, tempovoo);
			printf("insert %s %03d\n",prefixo, tempovoo);

			cont = 0;
		}
	}
	printf("\nLeitura realizada com sucesso.\n");
	fclose(fptr);
	return arvore;
}



/*Finaliza programa*/
int t_exit(Arvore arvore){
	t_free(arvore);
	exit(1);
}


/*Encontra elemento dado o prefixo, usando a funçao t_search*/
char encontra(Arvore arvore){
	char str[8];

	printf("Adicione o prefixo a ser procurado:");
	scanf("%s",&str);
	//fgets(str,sizeof(str),stdin);//Le do teclado o prefixo
	// t_search(arvore,str);
	t_search(arvore,str,0);
	
}


/*Imprime arvore na ordem crescente*/
void t_imprime_ordem(Arvore arvore){
	if(arvore == NULL)
		return;
	/*primeiro para a direita, depois o pai, e por ultimo a esquerda*/
	t_imprime_ordem(arvore->left);
	printf("%s %03d\n",arvore->prefixo,arvore->tempovoo);
	t_imprime_ordem(arvore->right);
	
	
}

/*Adiciona elemento dado prefixo e tempo*/
void add_elemento(Arvore arvore){
	char str[8];
	int tempo;

	printf("\nAdicione um novo elemento\n");
	printf("\nAdicione o prefixo: ");
	fflush(stdin);//pausa para leitura so windows
	//fgets(str,sizeof(str),stdin);//le prefixo do teclado
	scanf("%s",&str);
	printf("\nAdicione o tempo: ");
	fflush(stdin);
	scanf("%d",&tempo);//le inteiro do teclado
	t_insert(arvore, str, tempo);
}
/*Remove elemento dado prefixo usando funçao t_delete*/
void delete_elemento(Arvore arvore){

	char str[8];
	printf("\nEntre com o prefixo a ser deletado:");
	fflush(stdin);
	scanf("%s",str);
	//fgets(str,sizeof(str),stdin);
	t_delete(arvore,str);
}
/*Menu de opçoes do programa*/
int menu(Arvore arvore){

	int opcao = 0;
	do{
		printf("1 - Ler o arquivo com os avioes e gerar a arvore na memoria\n2 - Buscar um elemento na arvore dada uma chave\n3 - Adicionar um elemento na arvore\n4 - Remover um dado elemento na arvore, dada uma chave\n5 - Exibir uma lista em ordem crescente das chaves com todos os elementos da arvore e seus campos\n6 - Exit\n");
			
			
			
			
			
		printf("\nsua opcao:");
		scanf("%d",&opcao);
		if(opcao<1 || opcao>6){
			printf("\nOpcao invalida, tenete novamente");
			getchar();
			//system("pause");
			system("cls");
			continue;
		}
		switch(opcao){
			case 1: arvore = ler_arquivo(arvore);
			//system("pause");//para Windows
			getchar(); // Para Linux
			break;

			case 2: encontra(arvore);
			//system("pause");
			getchar();
			break;

			case 3: add_elemento(arvore);
			//system("pause");
			getchar();
			break;

			case 4: delete_elemento(arvore);
			//system("pause");
			getchar();
			break;

			case 5: t_imprime_ordem(arvore);
			//system("pause");
			getchar();
			break;

			case 6: exit(arvore);
			//system("pause");
			getchar();
			break;
		}
	}
	while(opcao != 6);
	return 0;

}