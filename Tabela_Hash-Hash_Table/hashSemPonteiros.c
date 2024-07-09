#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//	quantidade de chaves (elementos) = 15 * 2 = 31 (primos mais pr�ximo)
#define TAM 31

void zerarTabela(int t[]){
	int cont;	
	for (cont = 0; cont < TAM; cont++){
		t[cont] = 0;
	}
}
int funcaoHash(int chave){
	return chave % TAM;
}

void inserir(int valor, int t[]){
	int pos;
	pos = funcaoHash(valor);
	while(t[pos] != 0){
		pos = funcaoHash(pos + 1); //quando a posi��o for menor que o tam(31) o retorno do hash ser� o pr�pio valor (pos+1)
								   //quando a posi��o for 30 e o id dever� voltar ao 0, entao a funcao hash retornar� 31%31 = 0 	
	}
	t[pos] = valor;
}
int buscar(int t[],int chave){
	int pos;
	pos = funcaoHash(chave);
	
	while(t[pos]!=0){
		if(t[pos] == chave){
			return pos;
		}else{
			pos = funcaoHash(pos+1);
		}
	}
	return 0;
}
void imprimir(int t[]){
	int i;
	for (i=0; i<TAM; i++){
		printf("%i = %i\n",i,t[i]);
	}
}

void inserirRand(int t[]){
	int i,valor;
	srand(time(NULL));
	for (i=0; i<15; i++){
		valor = rand()%100;
		inserir(valor,t);
		imprimir(t);
		Sleep(500);
		system("cls");
	}
}
int main(){
	
	int tabela[TAM],opc,valor,retorno,i;

	zerarTabela(tabela);
	
	do{
		for (i = 0; i < 28; i++){
			printf("%c",196);
		}
		printf("\n%c	            	   %c",179,179);
		printf("\n%c	0 | Sair    	   %c",179,179);
		printf("\n%c	1 | Inserir 	   %c",179,179);
		printf("\n%c	2 | Buscar  	   %c",179,179);
		printf("\n%c	3 | Imprimir	   %c",179,179);
		printf("\n%c	4 | Aleatorio	   %c",179,179);
		printf("\n%c	5 | Zerar tabela   %c",179,179);
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
				inserir(valor,tabela);
				printf("\nValor Inserido");
				break;
			case 2:
				printf("\nDigite o valor buscado: ");
				scanf("%i",&valor);
				fflush(stdin);
				retorno = buscar(tabela,valor);
				if(retorno==0){
					printf("\nValor nao encontrado");
				}else{
					printf("---- Valor - Encontrado ----\n Posicao [%i] = %i\n",retorno, tabela[retorno]);
				}
				break;
			case 3:
				imprimir(tabela);
				break;
			case 4:
				inserirRand(tabela);
				break;
			case 5:
				zerarTabela(tabela);
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
