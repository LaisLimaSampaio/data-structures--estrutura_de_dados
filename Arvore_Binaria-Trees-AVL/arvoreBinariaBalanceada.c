#include <stdio.h>
#include <stdlib.h>

typedef struct no{
	int valor;
	struct no *direita, *esquerda; 
	short altura;
}No;


short maior(short a, short b){
	return (a > b) ? a : b;	
}
short alturaDoNo(No *no){
	if (no == NULL){
		return -1;
	}else{
		return no->altura;
	}
}
short fatorBalanceamento(No *no){
	if(no){
		return (alturaDoNo(no->esquerda) - alturaDoNo(no->direita));
	}else{
		return 0;
	}
}

No* novoNo(int valor){
	No *aux = malloc(sizeof(No));
	
	if(aux){
		aux->valor = valor;
		aux->esquerda = NULL;
		aux->direita = NULL;
		aux->altura = 0;
		printf("\n\t Valor Inserido\n\n");
		
	}else{
		printf("- Erro ao alocar memoria -");
	}
	return aux;
	
}

No* rotacaoEsquerda(No *r){
	No *y, *f;
	
	y = r->direita;
	f = y->esquerda;
	
	y->esquerda = r;
	r->direita = f;
	
	r->altura = maior(alturaDoNo(r->esquerda),alturaDoNo(r->direita))+1;
	y->altura = maior(alturaDoNo(y->esquerda),alturaDoNo(y->direita))+1;
	
	return y;
	
}
No* rotacaoDireita(No *r){
	No *y, *f;
	
	y = r->esquerda;
	f = y->direita;
	
	y->direita = r;
	r->esquerda	 = f;
	
	r->altura = maior(alturaDoNo(r->esquerda),alturaDoNo(r->direita))+1;
	y->altura = maior(alturaDoNo(y->esquerda),alturaDoNo(y->direita))+1;
	
	return y;
	
}

No* rotacaoDireitaEsquerda(No *r){
	r->direita = rotacaoDireita(r->direita);
	return rotacaoEsquerda(r);
}

No* rotacaoEsquerdaDireita(No *r){
	r->esquerda = rotacaoEsquerda(r->esquerda);
	return rotacaoDireita(r);
}

No* balancear(No *raiz){
	short fb = fatorBalanceamento(raiz);
	
	if (fb < -1 && fatorBalanceamento(raiz->direita)<=0){
		raiz = rotacaoEsquerda(raiz);	
	}
	else if (fb > 1 && fatorBalanceamento(raiz->esquerda)>=0){
		raiz = rotacaoDireita(raiz);	
	}
	else if (fb > 1 && fatorBalanceamento(raiz->esquerda) < 0){
		raiz = rotacaoEsquerdaDireita(raiz);	
	}
	else if (fb < -1 && fatorBalanceamento(raiz->esquerda) > 0){
		raiz = rotacaoDireitaEsquerda(raiz);	
	}
	return raiz;
}
No* inserir(No *raiz, int valor){
	
	if (raiz == NULL){
		return novoNo(valor);	
	}else{
		
		if(valor < raiz->valor){
			
			raiz->esquerda = inserir(raiz->esquerda,valor);
			
		}else{
			raiz->direita = inserir(raiz->direita,valor);
		}
		
	}
	
	raiz->altura = maior(alturaDoNo(raiz->direita), alturaDoNo(raiz->esquerda)) + 1;
	raiz = balancear(raiz);
	
	return raiz;
}

void imprimir_ordenado(No *raiz){
	
	if(raiz){
		imprimir_ordenado(raiz->esquerda);
		printf("\t%i",raiz->valor);
		imprimir_ordenado(raiz->direita);
	}
	
}

No* buscar(No *raiz, int valor){
	if (raiz){
		if (raiz->valor == valor){
			return raiz;
		}
		else{
			if(valor < raiz->valor){
				return buscar(raiz->esquerda, valor);
			}else{
				return buscar(raiz->direita, valor);
			}
		}
	}
	return NULL;
}

int altura(No *raiz){
	if (raiz == NULL){
		return -1;
	}else{
		int esq = altura(raiz->esquerda);
		int dir = altura(raiz->direita);
		if (esq>dir){
			return esq +1;
		}else{
			return dir +1;
		}
	}
}

int quantidade_nos(No *raiz){
	return (raiz==NULL)? 0 : 1 + quantidade_nos(raiz->esquerda) + quantidade_nos(raiz->direita); 
}

int quantidade_folhas(No *raiz){
	if(raiz==NULL){
		return 0;
		
	}else if(raiz->esquerda == NULL && raiz->direita == NULL){
		return 1;
		
	}else{
		return quantidade_folhas(raiz->direita) + quantidade_folhas(raiz->esquerda);
	}
		
}

No* remover(No *raiz, int chave){
	if(raiz==NULL){
		printf("Valor não encontrado");
		return NULL;
	}else{
		if(raiz->valor == chave){
			if (raiz->esquerda == NULL && raiz->direita == NULL){
				free(raiz);
				return NULL;
			}else{
				
				if (raiz->esquerda != NULL && raiz->direita != NULL){
					No *aux = raiz->esquerda;
					while (aux->direita != NULL){
						aux = aux->direita;
					}
					raiz->valor = aux->valor;
					aux->valor = chave;
					raiz->esquerda = remover(raiz->esquerda, chave);
					return raiz;
				}else{
					No *aux = (raiz->esquerda != NULL) ? raiz->esquerda : raiz->direita;
                	free(raiz);
                	return aux;
				}
				
			}
		}else{
			if (chave < raiz->valor){
				raiz->esquerda = remover(raiz->esquerda,chave);	
			}else{
				raiz->direita = remover(raiz->direita,chave);
			}
			return raiz;
		}	
	}
	raiz->altura = maior(alturaDoNo(raiz->direita), alturaDoNo(raiz->esquerda)) + 1;
	raiz = balancear(raiz);	
}

void imprimir_arv(No *raiz, int nivel){
	int i;
	if(raiz){
		imprimir_arv(raiz->direita,nivel+1);
		printf("\n\n");
		
		for(i = 0; i < nivel; i++){
			printf("\t");
		}
		
		printf("%i",raiz->valor);
		imprimir_arv(raiz->esquerda,nivel+1);
	}	
}
int main(){
	
	int opc,valor;
	No *retorno,*raiz = NULL;
	
	
	do{
		system("cls");
		printf("\t                     MENU                  \n\n");	
		printf("\t|          1 - inserir                   |\n");
		printf("\t|          2 - imprimir ordenado         |\n");
		printf("\t|          3 - buscar                    |\n");
		printf("\t|          4 - remover                   |\n");
		printf("\t|          5 - quantidade nos            |\n");
		printf("\t|          6 - altura                    |\n");
		printf("\t|          7 - quantidade de folhas      |\n");
		printf("\t|          8 - imprimir em arvore        |\n");
		printf("\t|          0 - sair                      |\n");
		
		scanf("%i",&opc);
		system("cls");
		switch (opc){
			case 1:
				printf("\tDigite um valor: ");
				scanf("%i",&valor);
				
				raiz = inserir(raiz, valor);
				
				system("pause");
				break;
			case 2:
				printf("\t\tIMPRIMINDO\n\n");
				imprimir_ordenado(raiz);
				printf("\n\n");
				system("pause");
				break;
			case 3:
				printf("\n\n\tBUSCAR");
				printf("\n\n\tQual o valor que deseja procurar? ");
				scanf("%i",&valor);
				retorno = buscar(raiz,valor);
				if (retorno){
					printf("\n\n\tValor encontrado: %i \n\n", retorno->valor);
				}else{
					printf("O valor não foi encontrado");
				}
				system("pause");
				break;
			case 4:
				printf("\n\n\t\tREMOVER");
				printf("\n\n\tQual o valor que deseja procurar? ");
				scanf("%i",&valor);
				remover(raiz,valor);
				system("pause");
				break;
			case 5:
				printf("\tQuantidade de nos: %i\n\n",quantidade_nos(raiz));
				system("pause");
				break;
			case 6:
				printf("\tAltura da arvore: %i\n\n",altura(raiz));
				system("pause");
				break;
			case 7:
				printf("\tQuantidade de folhas: %i\n\n", quantidade_folhas(raiz));
				system("pause");
				break;
			case 8:
				imprimir_arv(raiz,1);
				printf("\n\n");
				system("pause");
				break;
		}
	}while(opc != 0);
	
	return 0;	
}
