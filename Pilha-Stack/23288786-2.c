#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct {
    char nome[50], cpf[15], rg[13];
} Pessoa;

typedef struct {
    int ra;
    char curso[30];
    Pessoa p;
} Aluno;

Aluno ler_dados() {
    Aluno al;

    printf("Digite o seu nome: ");
    fgets(al.p.nome, 50, stdin);

    printf("Digite seu CPF: (xxx.xxx.xxx.-xx) = ");
    fgets(al.p.cpf, 15, stdin);
    al.p.cpf[14] = '\0';

    printf("Digite seu RG: (xx.xxx.xxx-x) = ");
    fgets(al.p.rg, 13, stdin);
    al.p.rg[12] = '\0';

    printf("Digite seu RA: (somente números) = ");
    scanf("%i", &al.ra);
    getchar(); // Limpar o buffer do teclado

    printf("Digite seu curso: ");
    fgets(al.curso, 30, stdin);

    return al;
}

typedef struct no {
    Aluno al;
    struct no *anterior;
} No;

void imprimir(Aluno dados) {
    printf("NOME: %s\nRG: %s\nCPF: %s\nCURSO: %s\nRA: %i\n", dados.p.nome, dados.p.cpf, dados.p.rg, dados.curso, dados.ra);
}

No* push(No *topo) {
    No *novo = malloc(sizeof(No));
    if (novo) {
        novo->al = ler_dados();
        novo->anterior = topo;
        return novo;
    } else {
        printf("Erro ao alocar memória.\n");
        return NULL;
    }
}

No* pop(No **topo) {
	No *tmp;
    if (*topo != NULL) {
        tmp = *topo;
        *topo = tmp->anterior;
        return tmp;
    } else {
        printf("Não há nada na pilha.\n");
        return NULL;
    }
}

void imprimir_pilha(No *topo) {
    printf("\n------------- PILHA -----------------\n");
    while (topo) {
        imprimir(topo->al);
        topo = topo->anterior;
    }
    printf("\n------------- FIM PILHA -------------\n");
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    No *removido, *topo = NULL;
    int opc;

    do {
        printf("\n0-sair\n1-empilhar\n2-desempilhar\n3-imprimir\nOpção: ");
        scanf("%i", &opc);
        getchar(); // Limpar o buffer do teclado
        switch (opc) {
            case 1:
                topo = push(topo);
                break;
            case 2:
                removido = pop(&topo);
                if (removido) {
                    imprimir(removido->al);
                    free(removido); // Liberar memória alocada para o nó removido
                } else {
                    printf("Nada há ser removido.\n");
                }
                break;
            case 3:
                imprimir_pilha(topo);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida\n");
        }
    } while (opc != 0);

    return 0;
}
