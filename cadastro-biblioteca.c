#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIVROS 50
#define TAM_STRING 100

struct livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
};

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    struct livro biblioteca[MAX_LIVROS];
    int totalLivros = 0;
    int opcao;

    do {
        printf("===============================\n");
        printf("    BICLIOTECA - PARTE1\n");
        printf("===============================\n");
        printf("1 - Cadastrar novo livro\n");
        printf("2 - Listar todos os livros\n");
        printf("0 - Sair\n");
        printf("===============================\n");
        printf("Escolha uma opcao: ");


        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                printf("=== Cadastro de novo livro ===\n");
                
                if (totalLivros < MAX_LIVROS) {
                    printf("Digite o nome do livro: ");
                    fgets(biblioteca[totalLivros].nome, TAM_STRING, stdin);
                    

                    printf("Digite o autor: ");
                    fgets(biblioteca[totalLivros].autor, TAM_STRING, stdin);
                    

                    printf("Digite a editora: ");
                    fgets(biblioteca[totalLivros].editora, TAM_STRING, stdin);
                    

                    biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] = 0;
                    biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")] = 0;
                    biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")] = 0;

                    printf("Digite a edicao do livro: ");
                    scanf("%d", &biblioteca[totalLivros].edicao);
                    limparBufferEntrada();


                    totalLivros++;
                    //totalLivros = totalLivros +1;

                    printf("\nLivro cadastrado com sucesso!\n");

                } else {
                    printf("Capacidade maxima de livros atingida.\n");
                }
                break;

            case 2:
                if (totalLivros == 0) {
                    printf("Nenhum livro cadastrado.\n");
                } else {
                    for (int i = 0; i < totalLivros; i++) {
                        printf("\nLivro %d:\n", i + 1);
                        printf("Nome: %s\n", biblioteca[i].nome);
                        printf("Autor: %s\n", biblioteca[i].autor);
                        printf("Editora: %s\n", biblioteca[i].editora);
                        printf("Edicao: %d\n", biblioteca[i].edicao);
                    }
                    printf("===============================\n");
                }
                break;

            case 0:
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
        }
    } while (opcao != 0);

    return 0;
}
