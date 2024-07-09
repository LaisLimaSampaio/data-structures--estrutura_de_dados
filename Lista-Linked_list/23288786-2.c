#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    char cpf[20];
    char rg[15];
} pessoa;

typedef struct {
    char curso[30];
    char ra[13];
    pessoa p;
} aluno;

typedef struct apelido_no {
    aluno al;
    struct apelido_no *proximo;
} no;

typedef struct {
    no *inicio;
    int tam;
} Lista;

void criar_lista(Lista *lista);
aluno entradadedados();
no* buscar(Lista *lista, char *ra);
void inserir_ordenado(Lista *lista, aluno dados);
void inserir_inicio(Lista *lista, aluno dados);
void inserir_meio(aluno dados, Lista *lista, char ant[]);
void inserir_fim(aluno dados, Lista *lista);
void imprimir(Lista lista);
void mostrar_dados(no *dados);
no* remover(Lista *lista, char *ra);

int main() {
    int opcao;
    Lista lista;
    no *loc;
    aluno dados;
    char ra[13];
    criar_lista(&lista);

    do {
        system("cls");
        printf("/-----------------------------------------------------------/\n");
        printf("|                        1-Buscar                           |\n");
        printf("|                        2-Inserir Ordenado                 |\n");
        printf("|                        3-Inserir ao Inicio                |\n");
        printf("|                        4-Inserir ao Medio                 |\n");
        printf("|                        5-Inserir ao Final                 |\n");
        printf("|                        6-Imprimir                         |\n");
        printf("|                        7-Remover                          |\n");
        printf("|                        8-Sair                             |\n");
        printf("/-----------------------------------------------------------/\n");
        scanf("%d", &opcao);
        fflush(stdin); // Limpa o buffer do teclado
        system("cls");

        switch (opcao) {
            case 1:
                printf("Buscar RA: ");
                gets(ra);
                loc = buscar(&lista, ra);
                if (loc){
                    printf("Aluno Encontrado: \n");
                    mostrar_dados(loc);
                } else
                    printf("Aluno nao encontrado. \n");
                break;
            case 2:
                dados = entradadedados();
                inserir_ordenado(&lista, dados);
                break;
            case 3:
                dados = entradadedados();
                inserir_inicio(&lista, dados);
                break;
            case 4:
                dados = entradadedados();
                printf("Escreva sua R.A de referencia: \n");
                gets(ra);
                inserir_meio(dados, &lista, ra);
                break;
            case 5:
                dados = entradadedados();
                inserir_fim(dados, &lista);
                break;
            case 6:
                imprimir(lista);
                break;
            case 7:
                printf("Remover RA: ");
                gets(ra);
                loc = remover(&lista, ra);
                if(loc){
                    printf("Aluno removido:\n");
                    mostrar_dados(loc);
                    free(loc);
                } else {
                    printf("Aluno nao removido\n");
                }
                break;
            default:
                if (opcao != 8)
                    printf("Opcao Invalida");
        }
        system("pause");
    } while (opcao != 8);

    return 0;
}

void criar_lista(Lista *lista) {
    lista->inicio = NULL;
    lista->tam = 0;
}

aluno entradadedados() {
    aluno dados;

    printf("/---------------------INSERINDO ALUNOS----------------------/\n\n");

    printf("                    Escreva o Nome:");
    gets(dados.p.nome);

    printf("                    Escreva o CPF:");
    gets(dados.p.cpf);

    printf("                    Escreva o RG:");
    gets(dados.p.rg);

    printf("                    Escreva o Curso:");
    gets(dados.curso);

    printf("                    Escreva o R.A:");
    gets(dados.ra);

    printf("/-----------------------------------------------------------/\n\n");

    return dados;
}

no* buscar(Lista *lista, char *ra) {
    no *aux = lista->inicio;
    while (aux && strcmp(aux->al.ra, ra) != 0)
        aux = aux->proximo;
    return aux;
}

void inserir_ordenado(Lista *lista, aluno dados) {
    no *aux, *novo = malloc(sizeof(no));
    if (novo) {
        novo->al = dados;
        if (lista->inicio == NULL || strcmp(lista->inicio->al.ra, dados.ra) > 0) {
            novo->proximo = lista->inicio;
            lista->inicio = novo;
        } else {
            aux = lista->inicio;
            while (aux->proximo && strcmp(aux->al.ra, dados.ra) <= 0)
                aux = aux->proximo;
            novo->proximo = aux->proximo;
            aux->proximo = novo;
        }
        lista->tam++;
    } else {
        printf("ERRO AO ALOCAR A MEMORIA");
    }
}

void inserir_inicio(Lista *lista, aluno dados) {
    no *novo = malloc(sizeof(no));
    if (novo) {
        novo->al = dados;
        novo->proximo = lista->inicio;
        lista->inicio = novo;
        lista->tam++;
    } else {
        printf("ERRO AO ALOCAR A MEMORIA");
    }
}

void inserir_meio(aluno dados, Lista *lista, char ant[]) {
    no *aux, *novo = malloc(sizeof(no));

    if (novo) {
        novo->al = dados;
        if (lista->inicio == NULL) {
            novo->proximo = NULL;
            lista->inicio = novo;
        } else {
            aux = lista->inicio;
            while (aux->proximo && strcmp(aux->proximo->al.ra, ant) != 0)
                aux = aux->proximo;

            novo->proximo = aux->proximo;
            aux->proximo = novo;
        }
        lista->tam++;
    } else {
        printf("ERRO AO ALOCAR A MEMORIA");
    }
}

void inserir_fim(aluno dados, Lista *lista) {
    no *aux, *novo = malloc(sizeof(no));
    if (novo) {
        novo->al = dados;
        novo->proximo = NULL;
        if (lista->inicio == NULL) {
            lista->inicio = novo;
        } else {
            aux = lista->inicio;
            while (aux->proximo)
                aux = aux->proximo;
            aux->proximo = novo;
        }
        lista->tam++;
    } else {
        printf("ERRO AO ALOCAR A MEMORIA");
    }
}

void imprimir(Lista lista) {
    no *aux = lista.inicio;
    printf("%d\n", lista.tam);

    while (aux) {
        mostrar_dados(aux);
        aux = aux->proximo;
    }
}

void mostrar_dados(no *dados) {
    printf("\n/-----------------------------------------------------------/\n");
    printf("                         Nome: %s\n", dados->al.p.nome);
    printf("                          R.A: %s\n", dados->al.ra);
    printf("                          CPF: %s\n", dados->al.p.cpf);
    printf("                           RG: %s\n", dados->al.p.rg);
    printf("                        Curso: %s\n", dados->al.curso);
    printf("/-----------------------------------------------------------/\n");
}

no* remover(Lista *lista, char *ra) {
    no *aux = lista->inicio;
    no *remover = NULL;
    no *anterior = NULL;

    while (aux != NULL && strcmp(aux->al.ra, ra) != 0) {
        anterior = aux;
        aux = aux->proximo;
    }

    if (aux != NULL) {
        if (anterior == NULL) {
            lista->inicio = aux->proximo;
        } else {
            anterior->proximo = aux->proximo;
        }
        aux->proximo = NULL;
        lista->tam--;
        remover = aux;
    }

    return remover;
}

