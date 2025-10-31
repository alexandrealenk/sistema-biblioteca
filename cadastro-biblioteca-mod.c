#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para usar strcspn

//---Constantes globais ---
#define MAX_LIVROS 50
#define MAX_EMPRESTIMOS 100
#define TAM_STRING 100

//---Definição da estrutura (Struct) ---
struct livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
    int disponivel; // 1 para disponível, 0 para emprestado.
};

struct emprestimo {
    int indiceLivro; // Para saber qual livro do array 'biblioteca' foi emprestado.
    char nomeUsuario[TAM_STRING];
};

//prototipo das funções
//declarar as funçoes aqui permite que 'main' as chame antes de suas definições.
void limparBufferEntrada();
void exibirMenu();
void cadastrarLivro(struct livro *biblioteca, int *totalLivros);
void listarLivros(struct livro *biblioteca, int totalLivros);
void emprestarLivro(struct livro *biblioteca, struct emprestimo *emprestimos, int *totalEmprestimos, int totalLivros);
void listarEmprestimos(struct livro *biblioteca, struct emprestimo *emprestimos, int totalEmprestimos);
void liberarMemoria(struct livro *biblioteca, struct emprestimo *emprestimos);

//---Função principal(main) ---
// Agora, a main é mais limpa. Ela aloca memória, chama funções e libera memória.
int main() {

    struct livro *biblioteca = (struct livro *) calloc(MAX_LIVROS, sizeof(struct livro));
    struct emprestimo *emprestimos = (struct emprestimo *) malloc(MAX_EMPRESTIMOS * sizeof(struct emprestimo));

    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro: Falha ao alocar memoria.\n");
        return 1; // Sai do programa com código de erro.
    }
    
    int totalLivros = 0;
    int totalEmprestimos = 0;
    int opcao;

    //---Laço principal do menu ---
    do {
        exibirMenu();
        scanf("%d", &opcao);
        limparBufferEntrada(); 

        switch (opcao) {
            case 1: // Cadastrar novo livro
               cadastrarLivro(biblioteca, &totalLivros);
                break;
            case 2: // Listar todos os livros
                listarLivros(biblioteca, totalLivros);
                break;
            case 3: // Emprestar livro
                emprestarLivro(biblioteca, emprestimos, &totalEmprestimos, totalLivros);
                break;
            case 4: // Listar empréstimos
                listarEmprestimos(biblioteca, emprestimos, totalEmprestimos);
                break;
            case 0: // Sair do sistema.
                printf("\nSaindo do sistema...\n");
                break;
            default: // Opção inválida.
                printf("\nOpcao invalida! Tente novamente.\n");
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
        }
    } while (opcao != 0);

    liberarMemoria(biblioteca, emprestimos);

    return 0; // Retorna 0 para indicar que o programa terminou com sucesso.
}

//--Implementação das funções auxiliares --

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void exibirMenu() {
    printf("===============================\n");
    printf("    BIBLIOTECA - PARTE 1\n");
    printf("===============================\n");
    printf("1 - Cadastrar novo livro\n");
    printf("2 - Listar todos os livros\n");
    printf("3 - Emprestar livro\n");
    printf("4 - Listar emprestimos\n");
    printf("0 - Sair\n");
    printf("===============================\n");
    printf("\nEscolha uma opcao: ");
}

/**
 * @brief Cadastra um novo livro na biblioteca.
 * @param biblioteca Ponteiro para o array de livros.
 * @param totalLivros Ponteiro para o contador de livros cadastrados.
 */
void cadastrarLivro(struct livro *biblioteca, int *totalLivros) {
    printf("\n=== Cadastro de novo livro ===\n");

    if (*totalLivros < MAX_LIVROS) {
        int indice = *totalLivros; // usa o valor apontado pelo ponteiro para o indice.

        printf("Digite o nome do livro: ");
        fgets(biblioteca[indice].nome, TAM_STRING, stdin);
        printf("Digite o autor: ");
        fgets(biblioteca[indice].autor, TAM_STRING, stdin);
        printf("Digite a editora: ");
        fgets(biblioteca[indice].editora, TAM_STRING, stdin);
                    
        biblioteca[indice].nome[strcspn(biblioteca[indice].nome, "\n")] = 0;
        biblioteca[indice].autor[strcspn(biblioteca[indice].autor, "\n")] = 0;
        biblioteca[indice].editora[strcspn(biblioteca[indice].editora, "\n")] = 0;

        printf("Digite a edicao do livro: ");
                    scanf("%d", &biblioteca[indice].edicao);
                    limparBufferEntrada();

                    // Marca o livro como disponível.
        biblioteca[indice].disponivel = 1;

        (*totalLivros)++;
        printf("\nLivro cadastrado com sucesso!\n");

    } else {
        printf("Capacidade maxima de livros atingida.\n");
    }
    printf("\nPressione Enter para continuar...");
    getchar();
}
/**
 * @brief Lista todos os livros cadastrados na biblioteca.
 * @param biblioteca Ponteiro para o array de livros.
 * @param totalLivros Total de livros cadastrados.
 */
void listarLivros(struct livro *biblioteca, int totalLivros) {
    printf("\n=== Lista de livros cadastrados ===\n");
    if (totalLivros == 0) {
        printf("Nenhum livro cadastrado.\n");
    } else {
        for (int i = 0; i < totalLivros; i++) {
            printf("Livro %d:\n", i + 1);
            printf("Nome: %s\n", biblioteca[i].nome);
            printf("Autor: %s\n", biblioteca[i].autor);
            printf("Editora: %s\n", biblioteca[i].editora);
            printf("Edicao: %d\n", biblioteca[i].edicao);
            printf("Status: %s\n", biblioteca[i].disponivel ? "Disponivel" : "Emprestado");
            printf("---------------------------------\n");
        }
            printf("\n===============================\n");
    }
                printf("\nPressione Enter para continuar...");
                getchar();
}
/**
 * @brief Realiza o empréstimo de um livro.
 * @param biblioteca Ponteiro para o array de livros.
 * @param emprestimos Ponteiro para o array de empréstimos.
 * @param totalEmprestimos Ponteiro para o contador de empréstimos realizados.
 * @param totalLivros Total de livros cadastrados.
 */
void realizarEmprestimo(struct livro *biblioteca, struct emprestimo *emprestimos, int *totalEmprestimos, int totalLivros) {
    printf("=== Realizar Emprestimo ===\n");

    if (*totalEmprestimos >= MAX_EMPRESTIMOS) {
        printf("Capacidade maxima de emprestimos atingida.\n");
    } else {
        printf("Livros disponiveis:\n");
        int disponiveis = 0;
        for (int i = 0; i < totalLivros; i++) {
            if (biblioteca[i].disponivel) {
                printf("%d - %s\n", i + 1, biblioteca[i].nome);
                disponiveis++;
            }
        }

        if (disponiveis == 0) {
            printf("\nNenhum livro disponivel para emprestimo.\n");
        } else {
            printf("\nDigite o numero do livro que deseja emprestar: ");
            int numlivro;
            scanf("%d", &numlivro);
            limparBufferEntrada();

            int indice = numlivro - 1; // converte para índice do array (0 a n-1).

                        //validação da escolha do usuário.
            if (indice >= 0 && indice < totalLivros && biblioteca[indice].disponivel) {
                printf("\nDigite o nome do usuario que esta pegando o livro: ");
                fgets(emprestimos[*totalEmprestimos].nomeUsuario, TAM_STRING, stdin);
                emprestimos[*totalEmprestimos].nomeUsuario[strcspn(emprestimos[*totalEmprestimos].nomeUsuario, "\n")] = 0;


                emprestimos[*totalEmprestimos].indiceLivro = indice;
                biblioteca[indice].disponivel = 0; // atualiza o status do livro para emprestado.
                            
                (*totalEmprestimos)++;
                printf("\nEmprestimo realizado com sucesso!\n");
            } else {
                printf("Numero de livro invalido ou livro indisponivel.\n");
            }
        }
    }
    printf("\nPressione Enter para continuar...");
    getchar();
}
/**
 * @brief Lista todos os empréstimos realizados.
 * @param biblioteca Ponteiro para o array de livros.
 * @param emprestimos Ponteiro para o array de empréstimos.
 * @param totalEmprestimos Total de empréstimos realizados.
 */
void listarEmprestimos(struct livro *biblioteca, struct emprestimo *emprestimos, int totalEmprestimos) {
    printf("\n=== Lista de Emprestimos ===\n");
    if (totalEmprestimos == 0) {
        printf("Nenhum emprestimo registrado.\n");
    } else {
        for (int i = 0; i < totalEmprestimos; i++) {
            //usa o indice armazenado no empréstimo para acessar o livro correto.
            int indiceLivro = emprestimos[i].indiceLivro;
            printf("Emprestimo %d:\n", i + 1);
            printf("Livro: %s\n", biblioteca[indiceLivro].nome);
            printf("Usuario: %s\n", emprestimos[i].nomeUsuario);
            printf("-------------------------------\n");
        }
        printf("===============================\n");
    }

    // Pausa para o usuário ler a lista
    // e espera o Enter ser pressionado.
    printf("\nPressione Enter para continuar...");
    getchar();
}
/**
 * @brief Libera a memória alocada para os livros e empréstimos.
 */
void liberarMemoria(struct livro *biblioteca, struct emprestimo *emprestimos) {
    free(biblioteca); // Libera a memória alocada para os livros.
    free(emprestimos); // Libera a memória alocada para os empréstimos
    printf("Memoria liberada com sucesso.\n");
}