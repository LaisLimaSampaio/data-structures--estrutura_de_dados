#include <stdio.h>
#include <stdlib.h>

#define TAM 15

typedef struct no{
    int chave;
    struct no *proximo;
}No;
typedef struct{
    No *inicio;
    int tam;
}Lista;

void inicializarLista(Lista *l){
   l->inicio = NULL;
   l->tam = 0;
}

void inicializarTabela(Lista t[]){
    int i;
    for (i=0; i<TAM; i++)
        inicializarLista(&t[i]);
}
void inserirLista(Lista *l,int valor){
    No *novo = malloc(sizeof(No));
    novo->chave = valor;
    novo->proximo = l->inicio;
    l->inicio = novo;
    l->tam++;
}
void inserir(Lista t[],int valor){
    int pos;
    pos = funcaoHash(valor);
    inserirLista(&t[pos],valor);

}
int funcaoHash(int valor){
    return valor % TAM;
}


int buscarLista(Lista *l, int chave){

    No *aux = l->inicio;
    while(aux && aux->chave!=chave){
        aux = aux->proximo;
    }
    if(aux){
        return aux->chave;
    }
    return -1;
}
int buscar(Lista t[],int chave){
    int pos;
    pos = funcaoHash(chave);
    return buscarLista(&t[pos],chave);
}

void imprimirLista(Lista *l){
    No *aux = l->inicio;
    while(aux){
        printf(" %i ",aux->chave);
        aux=aux->proximo;
    }
}
void imprimir(Lista t[]){
    int i;
    for(i=0; i<TAM; i++){
        printf("%2i =",i);
        imprimirLista(&t[i]);
        printf("\t|%i < - Lista tamanho",t[i].tam);
        printf("\n");
    }
}

int main(){
    Lista tabela[TAM];
    int opc,valor,retorno,i;

    inicializarTabela(tabela);

    do{
		for (i = 0; i < 28; i++){
			printf("%c",196);
		}
		printf("\n%c	            	   %c",179,179);
		printf("\n%c	0 | Sair    	   %c",179,179);
		printf("\n%c	1 | Inserir 	   %c",179,179);
		printf("\n%c	2 | Buscar  	   %c",179,179);
		printf("\n%c	3 | Imprimir	   %c",179,179);
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
				inserir(tabela,valor);
				printf("\nValor Inserido");
				break;
			case 2:
				printf("\nDigite o valor buscado: ");
				scanf("%i",&valor);
				fflush(stdin);
				retorno = buscar(tabela,valor);
				if(retorno==-1){
					printf("\nValor nao encontrado");
				}else{
					printf("---- Valor - Encontrado ----\n Posicao [%i] = %i\n",retorno, tabela[retorno]);
				}
				break;
			case 3:
				imprimir(tabela);
				break;

			default:
				if (opc!=0){
					printf("Op��o inv�lida");
				break;	
				}
			
		}
		printf("\n\n\n");
		system("pause");
		system("cls");
	}while(opc!=0);
	
	return 0;  
}
