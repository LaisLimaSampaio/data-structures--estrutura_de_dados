#include <stdio.h>
#include <stdlib.h>

typedef struct no{
	int conteudo;
	struct no *direita, *esquerda;
}No;

typedef struct{
	No *raiz;
}ArvB;

//-------------- Inserçao ---------------
void inserirDireita(No *noPai,int valor){
	if(noPai->direita==NULL){
		No *novo = (No*)malloc(sizeof(No));
		novo->conteudo = valor;
		novo->direita = NULL;
		novo->esquerda = NULL;
		noPai->direita = novo;
	}
	else{
		if (valor > noPai->direita->conteudo){
			inserirDireita(noPai->direita,valor);
		}else{
			inserirEsquerda(noPai->direita,valor);
		}
	}
}


void inserirEsquerda(No *noPai,int valor){
	if(noPai->esquerda==NULL){
		No *novo = (No*)malloc(sizeof(No));
		novo->conteudo = valor;
		novo->direita = NULL;
		novo->esquerda = NULL;
		noPai->esquerda = novo; 
	}else{
		if(valor < noPai->esquerda->conteudo){
			inserirEsquerda(noPai->esquerda,valor);
		}else{
			inserirDireita(noPai->esquerda,valor);
		}
	}
	
}

void inserir(ArvB *arv, int valor){
	if (arv->raiz == NULL){
		No *novo = (No*)malloc(sizeof(No));
		novo->conteudo = valor;
		novo->direita = NULL;
		novo->esquerda = NULL;		
		arv->raiz = novo;
	}
	else{
		if (valor < arv->raiz->conteudo){
			inserirEsquerda(arv->raiz,valor);
		}else{
			inserirDireita(arv->raiz,valor);
		}
	}
}
//------------Impressão-------------------------
void imprimir(No *raiz){
	if (raiz!=NULL){
		imprimir(raiz->esquerda);
		printf("%2d  |  ",raiz->conteudo);
		imprimir(raiz->direita);
		
	}
}
//----------busca---------

int buscar(No *raiz, int chave){
	if (raiz == NULL){
		return -1;
	}else{
		if(raiz->conteudo == chave){
			return raiz->conteudo;
		}
		else{
			if (chave > raiz->conteudo){
				buscar(raiz->direita, chave);
			}else{
				buscar(raiz->esquerda, chave);
			}
		}
	}
}

int main(){
	
	int opc, valor,i,retorno;
	ArvB arvore;
	
	arvore.raiz = NULL;
	
	do{
		for (i = 0; i < 28; i++){
			printf("%c",196);
		}
		printf("\n%c	            	   %c",179,179);
		printf("\n%c	0 | Sair    	   %c",179,179);
		printf("\n%c	1 | Inserir 	   %c",179,179);
		printf("\n%c	2 | Imprimir	   %c",179,179);
		printf("\n%c	3 | Buscar   	   %c",179,179);
		printf("\n%c	            	   %c\n",179,179);
		
		for (i = 0; i < 28; i++){
			printf("%c",196);
		}
		printf("\nDigite aqui: ");
		scanf("%i",&opc);
		fflush(stdin);
		
		system("cls");
		switch(opc){
			case 1:
				printf("\nDigite o valor que deseja inserir: ");
				scanf("%i",&valor);
				fflush(stdin);
				
				inserir(&arvore,valor);
				
				printf("\nValor Inserido");
				break;
			case 2:
				printf("---- Mostrando Arvore Binaria----\n\n");
				imprimir(arvore.raiz);
				break;
			case 3:
				printf("Qual valor deseja buscar? ");
				scanf("%i",&valor);
				retorno = buscar(arvore.raiz,valor);
				
				printf("\n\n ----------Resultado da busca----------\n\n");
				if (retorno == -1){
					printf("Valor nao encontrado.");
				}else{
						printf("\tValor encontrado: %i",retorno);
				}
				break;
			default:
				if (opc!=0){
					printf("Opcao invalida");	
				}else{
					printf("Saindo . . .");
				}
				break;
			
		}
		printf("\n\n\n");
		system("pause");
		system("cls");
	}while(opc!=0);
	
}
