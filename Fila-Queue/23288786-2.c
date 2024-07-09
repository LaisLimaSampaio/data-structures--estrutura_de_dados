#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char nome[50],rg[13],cpf[15];
}Pessoais;

typedef struct{
	char ra[11], curso[30];
	Pessoais dados;
}Aluno;

typedef struct no{
	Aluno dados;
	struct no *proximo;	
}No;

Aluno inserir_pessoa(){
	
	Aluno p;
	
	printf("\nDigite o NOME do aluno: ");
	gets(p.dados.nome);
	fflush(stdin);
	printf("Digite o CPF do aluno: ");
	gets(p.dados.cpf);
	printf("Digite o RG do aluno: ");
	gets(p.dados.rg);
	printf("Digite o RA do aluno: ");
	gets(p.ra);
	printf("Digite o CURSO do aluno: ");
	gets(p.curso);
		
	return p;
}

void enfileirar(No **fila){
	printf("\n-------ENFILEIRANDO-------\n");
	
	No *aux, *novo = malloc(sizeof(No)); 
	
	if (novo){
		novo->dados = inserir_pessoa();
		novo->proximo = NULL;
		if (*fila == NULL){
			*fila = novo;			
		}
		else{
			aux = *fila;
			
			while(aux->proximo)
				aux=aux->proximo;
			aux->proximo = novo;
		}
		
	}
	else{
		printf("Erro ao alocar memória\n");
	}
}

No* desenfileirar(No **fila){
	No *removido = NULL;
	printf("\n------DESENFILEIRANDO------\n\n");
	if (*fila){
		removido = *fila;
		*fila = removido->proximo;
	}
	else{
		printf("Fila Vazia.\n");
	}
	
	return removido;
}

void imprimir_pessoa(Aluno p){
	
	printf("\nNOME: %s",p.dados.nome);
	printf("\nCPF: %s",p.dados.cpf);
	printf("\nRG: %s",p.dados.rg);
	printf("\nRA: %s",p.ra);
	printf("\nCURSO: %s",p.curso);
}
void imprimir(No *fila){
	if (fila){
		while (fila){
		imprimir_pessoa(fila->dados);
		fila = fila->proximo;
		printf("\n");
		}
	}else{
		printf("Fila vazia.\n");
	}
}
int main(){
	No *fila = NULL, *r;
	int opc;
	
	do{
		
		printf("\n----------- MENU ----------\n\n");
		printf("0 | SAIR\n1 | ENFILEIRAR\n2 | DESENFILEIRAR\n3 | IMPRIMIR\n");
		printf("Digite aqui: ");
		scanf("%i",&opc);
		fflush(stdin);
		system("cls");
		switch(opc){
			case 1:
				enfileirar(&fila);
				break;
			case 2:
				r = desenfileirar(&fila);
				
				if (r){
					printf("O elemento desenfileirado foi: \n");
					imprimir_pessoa(r->dados);
				}
				free(r);
				break;
			case 3:
				imprimir(fila);
				break;
			default:
				if (opc!=0){
					printf("Opção inválida.\n");	
				}
		}
	}while(opc != 0);
	
}
