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

//---Função para limpar o buffer de entrada ---
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//---Função principal(main) ---
int main() {
//1. ALOCAÇÃO DINÂMICA DE MEMÓRIA
// Ao inves de usar arrays estáticos, usa-se ponteiros.
    struct livro *biblioteca;
    struct emprestimo *emprestimos;

//Usamos calloc para o array de livros. calloc(numero_elementos, tamanho_elemento)
//vantagem: inicializa toda a memória com zeros. Isso é útil para o campo 'disponivel'.
    
    biblioteca = (struct livro *) calloc(MAX_LIVROS, sizeof(struct livro));
//Usamos malloc para o array de empréstimos. malloc(tamanho_total_em_bytes)
//vantagem: é mais rápido que calloc, e não precisamos inicializar os dados.
    emprestimos = (struct emprestimo *) malloc(MAX_EMPRESTIMOS * sizeof(struct emprestimo));

    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro: Falha ao alocar memoria.\n");
        return 1; // Sai do programa com código de erro.
    }
    
    int totalLivros = 0;
    int totalEmprestimos = 0;
    int opcao;

    //---Laço principal do menu ---
    do {

        //Exibe o menu de opções.
        printf("===============================\n");
        printf("    BIBLIOTECA - PARTE 1\n");
        printf("===============================\n");
        printf("1 - Cadastrar novo livro\n");
        printf("2 - Listar todos os livros\n");
        printf("3 - Emprestar livro\n");
        printf("4 - Listar emprestimos\n");
        printf("0 - Sair\n");
        printf("===============================\n");
        printf("Escolha uma opcao: ");

        //Lê a opção do usuário.
        scanf("%d", &opcao);
        limparBufferEntrada(); // Limpa o '\n' deixado pelo scanf.

        //---Processa a opção escolhida.
        switch (opcao) {
            case 1: // Cadastrar novo livro
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

            case 2: // Listar todos os livros
                printf("=== Lista de livros cadastrados ===\n");
                if (totalLivros == 0) {
                    printf("Nenhum livro cadastrado.\n");
                } else {
                    for (int i = 0; i < totalLivros; i++) {
                        printf("Livro %d:\n", i + 1);
                        printf("Nome: %s\n", biblioteca[i].nome);
                        printf("Autor: %s\n", biblioteca[i].autor);
                        printf("Editora: %s\n", biblioteca[i].editora);
                        printf("Edicao: %d\n", biblioteca[i].edicao);
                    }
                    printf("===============================\n");
                }

                // Pausa para o usuário ler a lista
                // e espera o Enter ser pressionado.
                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 3: // Emprestar livro
                printf("=== Realizar Emprestimo ===\n");

                if (totalEmprestimos >= MAX_EMPRESTIMOS) {
                    printf("Capacidade maxima de emprestimos atingida.\n");
                } else
                    printf("Livros disponiveis:\n");
                    int disponiveis = 0;
                    for (int i = 0; i < totalLivros; i++) {
                        if (biblioteca[i].disponivel) {
                            printf("%d - %s\n", i + 1, biblioteca[i].nome);
                            disponiveis++;
                        }
                    }
                    if (disponiveis == 0) {
                        printf("Nenhum livro disponivel para emprestimo.\n");
                    } else {
                        printf("Digite o numero do livro que deseja emprestar: ");
                        int numlivro;
                        scanf("%d", &numlivro);
                        limparBufferEntrada();

                        int indice = numlivro - 1; // converte para índice do array (0 a n-1).

                        //validação da escolha do usuário.
                        if (indice >= 0 && indice < totalLivros && biblioteca[indice].disponivel) {
                            printf("Digite o nome do usuario que esta pegando o livro: ");
                            fgets(emprestimos[totalEmprestimos].nomeUsuario, TAM_STRING, stdin);
                            emprestimos[totalEmprestimos].nomeUsuario[strcspn(emprestimos[totalEmprestimos].nomeUsuario, "\n")] = 0;

                            // Registra o empréstimo.
                            emprestimos[totalEmprestimos].indiceLivro = indice;

                            biblioteca[indice].disponivel = 0; // atualiza o status do livro para emprestado.
                            totalEmprestimos++;

                            printf("Emprestimo realizado com sucesso!\n");
                        } else {
                            printf("Numero de livro invalido ou livro indisponivel.\n");
                        }
                    }
                    printf("\nPressione Enter para continuar...");
                    getchar();
                    break;

                case 4: // Listar empréstimos
                    ("=== Lista de Emprestimos ===\n");
                    if (totalEmprestimos == 0) {
                    printf("Nenhum emprestimo registrado.\n");
                    } else {
                        for (int i = 0; i < totalEmprestimos; i++) {
                        //usa o indice armazenado no empréstimo para acessar o livro correto.
                        int indiceLivro = emprestimos[i].indiceLivro;
                        printf("Emprestimo %d:\n", i + 1);
                        printf("Livro: %s\n", biblioteca[indiceLivro].nome);
                        printf("Usuario: %s\n", emprestimos[i].nomeUsuario);
                    }
                    printf("===============================\n");
                }

                // Pausa para o usuário ler a lista
                // e espera o Enter ser pressionado.
                printf("\nPressione Enter para continuar...");
                getchar();
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

    //---Liberação da memória alocada ---
    // Sempre que alocamos memória dinamicamente, devemos liberá-la no final do uso.
    // Isso evita vazamentos de memória (memory leaks).
    free(biblioteca); // Libera a memória alocada para os livros.
    free(emprestimos); // Libera a memória alocada para os empréstimos

    printf("Memoria liberada com sucesso.\n");

    return 0; // Retorna 0 para indicar que o programa terminou com sucesso.
}
