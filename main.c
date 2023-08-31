#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _musica {
    char nomeMusica[40];
    char album[40];
    int anoLancamento;
} Musica;

typedef struct _cantor {
    char nome[40];
    char generoMusical[15];
    int idade;
    Musica musicas[100]; // Armazena as músicas diretamente
    int numMusicas;
} Cantor;

Musica cadastrarMusica() {
    Musica novaMusica;
    printf("Insira o nome da musica: ");
    fgets(novaMusica.nomeMusica, sizeof(novaMusica.nomeMusica), stdin);
    novaMusica.nomeMusica[strcspn(novaMusica.nomeMusica, "\n")] = '\0'; // Remover o newline

    printf("Insira o nome do album: ");
    fgets(novaMusica.album, sizeof(novaMusica.album), stdin);
    novaMusica.album[strcspn(novaMusica.album, "\n")] = '\0'; // Remover o newline

    printf("Insira o ano de lançamento: ");
    scanf(" %d", &novaMusica.anoLancamento);
    getchar(); // Consume the newline character after scanf

    return novaMusica;
}

Cantor cadastrarCantor() {
    Cantor novoCantor;
    printf("Insira o nome do cantor: ");
    fgets(novoCantor.nome, sizeof(novoCantor.nome), stdin);
    scanf(" %[^\n]s", novoCantor);
    novoCantor.nome[strcspn(novoCantor.nome, "\n")] = '\0'; // Remover o newline

    printf("Insira qual o genero musical: ");
    fgets(novoCantor.generoMusical, sizeof(novoCantor.generoMusical), stdin);
    scanf(" %[^\n]s", novoCantor.generoMusical);
    novoCantor.generoMusical[strcspn(novoCantor.generoMusical, "\n")] = '\0'; // Remover o newline

    printf("Insira a idade do cantor: ");
    scanf(" %d", &novoCantor.idade);
    getchar(); // Consume the newline character after scanf

    novoCantor.numMusicas = 0;
    printf("\n");
    return novoCantor;
}

void listarCantores(Cantor cantores[], int numCantores) {
    int i;
    for (i = 0; i < numCantores; i++) {
        printf("%d - %s\n", i + 1, cantores[i].nome);
    }
    printf("\n");
}

void editarCantores(Cantor cantores[], int numCantores) {
    char nome[40];
    int i, opcao;

    printf("Insira o nome do cantor a ser editado: ");
    scanf(" %[^\n]s", nome);

    for (i = 0; i < numCantores; i++) {
        if (strcmp(nome, cantores[i].nome) == 0) {
            printf("Digite:\n");
            printf("  Digite 1 para editar o nome do cantor\n");
            printf("  Digite 2 para editar o genero musical\n");
            printf("  Digite 3 para editar a idade do cantor\n");
            scanf(" %d", &opcao);
            switch (opcao) {
                case 1:
                    printf("Digite o novo nome do cantor: ");
                    scanf(" %[^\n]s", cantores[i].nome);
                    break;
                case 2:
                    printf("Digite o novo genero musical: ");
                    scanf(" %[^\n]s", cantores[i].generoMusical);
                    break;
                case 3:
                    printf("Digite a nova idade do cantor: ");
                    scanf(" %d", &cantores[i].idade);
                    break;
                default:
                    printf("Opção invalida!\n\n");
                    return;
            }
            printf("Operação realizada com sucesso!\n\n");
            return;
        }
    }
    printf("Cantor não encontrado!\n\n");
}

void removerCantor(Cantor cantores[], int *numCantores) {
    char nome[40];
    int i, encontrei = 0;
    printf("Insira o nome do cantor para remover: ");
    scanf(" %[^\n]s", nome);
    for (i = 0; i < *numCantores; i++) {
        if (encontrei) {
            cantores[i - 1] = cantores[i];
        }
        if (strcmp(nome, cantores[i].nome) == 0) {
            encontrei = 1;
        }
    }
    if (encontrei) {
        (*numCantores)--;
        printf("Operação realizada com sucesso!\n\n");
    } else {
        printf("Cantor não encontrado!\n\n");
    }
}

void inserirMusica(Cantor *cantor) {
    if (cantor->numMusicas < 100) { // Verifica se há espaço para mais músicas
        Musica novaMusica = cadastrarMusica();
        cantor->musicas[cantor->numMusicas] = novaMusica;
        cantor->numMusicas++;
        printf("Música inserida com sucesso!\n\n");
    } else {
        printf("O cantor já possui o limite máximo de músicas!\n\n");
    }
}

void listarMusicasDoCantor(Cantor *cantor) {
    printf("Músicas de %s:\n", cantor->nome);
    for (int i = 0; i < cantor->numMusicas; i++) {
        Musica musica = cantor->musicas[i];
        printf("%d - %s - %s\n", i + 1, musica.nomeMusica, musica.album);
    }
    printf("\n");
}

void editarMusicaCantor(Cantor *cantor) {
    char nomeMusica[40];
    printf("Insira o nome da música a ser editada: ");
    scanf(" %[^\n]s", nomeMusica);

    for (int i = 0; i < cantor->numMusicas; i++) {
        Musica *musica = &cantor->musicas[i];
        if (strcmp(nomeMusica, musica->nomeMusica) == 0) {
            printf("Digite:\n");
            printf("  Digite 1 para editar o nome da música\n");
            printf("  Digite 2 para editar o nome do álbum\n");
            printf("  Digite 3 para editar o ano de lançamento da música\n");
            int opcao;
            scanf(" %d", &opcao);
            switch (opcao) {
                case 1:
                    printf("Insira o novo nome da música: ");
                    scanf(" %[^\n]s", musica->nomeMusica);
                    break;
                case 2:
                    printf("Insira o novo nome do álbum: ");
                    scanf(" %[^\n]s", musica->album);
                    break;
                case 3:
                    printf("Insira o novo ano de lançamento da música: ");
                    scanf(" %d", &musica->anoLancamento);
                    break;
                default:
                    printf("Opção inválida!\n\n");
                    return;
            }
            printf("Operação realizada com sucesso!\n\n");
            return;
        }
    }
    printf("Música não encontrada!\n\n");
}


void removerMusicaCantor(Cantor *cantor) {
    char nomeMusica[40];
    printf("Insira o nome da música a ser removida: ");
    scanf(" %[^\n]s", nomeMusica);

    for (int i = 0; i < cantor->numMusicas; i++) {
        Musica *musica = &cantor->musicas[i];
        if (strcmp(nomeMusica, musica->nomeMusica) == 0) {
            for (int j = i; j < cantor->numMusicas - 1; j++) {
                cantor->musicas[j] = cantor->musicas[j + 1];
            }
            cantor->numMusicas--;
            printf("Música removida com sucesso!\n\n");
            return;
        }
    }
    printf("Música não encontrada!\n\n");
}
int main() {
    Cantor cantores[100]; // Limite de 100 cantores
    int numCantores = 0;
    int opcao;
    int escolhaCantor;
    int escolhaCantorMusica; // Renomear a variável para evitar conflito
    int numMusicas = 0;
    Musica musicas[100];

    do {
        printf("Digite:\n");
        printf("  Digite 1 para cadastrar um cantor\n");
        printf("  Digite 2 para listar cantores e suas musicas\n");
        printf("  Digite 3 para editar cantor\n");
        printf("  Digite 4 para remover cantor\n");
        printf("  Digite 5 para adicionar uma musica a um cantor\n");
        printf("  Digite 6 para editar uma música\n");
        printf("  Digite 7 para remover uma música\n");
        printf("  Digite 0 para sair\n");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                cantores[numCantores] = cadastrarCantor();
                numCantores++;
                break;
            case 2:
                listarCantores(cantores, numCantores);
                // Solicitação para escolher um cantor para listar suas músicas
                printf("Escolha o número de um cantor para listar suas músicas: ");
                scanf("%d", &escolhaCantor);
                escolhaCantor--; // Ajusta para o índice do vetor
                if (escolhaCantor >= 0 && escolhaCantor < numCantores) {
                    listarMusicasDoCantor(&cantores[escolhaCantor]);
                } else {
                    printf("Escolha de cantor inválida.\n");
                }
                break;
            case 3:
                editarCantores(cantores, numCantores);
                break;
            case 4:
                removerCantor(cantores, &numCantores);
                break;

            case 5:
                listarCantores(cantores, numCantores);
                // Solicitação para escolher um cantor para adicionar a música
                printf("Escolha o número de um cantor para adicionar uma música: ");
                int escolhaCantor;
                scanf("%d", &escolhaCantor);
                escolhaCantor--; // Ajusta para o índice do vetor
                if (escolhaCantor >= 0 && escolhaCantor < numCantores) {
                    inserirMusica(&cantores[escolhaCantor]);
                } else {
                    printf("Escolha de cantor inválida.\n");
                }
                break;

            case 6:
                listarCantores(cantores, numCantores);
                printf("Escolha o número de um cantor para editar uma música: ");
                scanf("%d", &escolhaCantor);
                escolhaCantor--; // Ajusta para o índice do vetor
                if (escolhaCantor >= 0 && escolhaCantor < numCantores) {
                    printf("Cantor selecionado: %s\n", cantores[escolhaCantor].nome);
                    editarMusicaCantor(&cantores[escolhaCantor]);
                } else {
                    printf("Escolha de cantor inválida.\n");
                }
                break;

            case 7:
                listarCantores(cantores, numCantores);
                printf("Escolha o número de um cantor para remover uma música: ");
                scanf("%d", &escolhaCantor);
                escolhaCantor--; // Ajusta para o índice do vetor
                if (escolhaCantor >= 0 && escolhaCantor < numCantores) {
                    printf("Cantor selecionado: %s\n", cantores[escolhaCantor].nome);
                    removerMusicaCantor(&cantores[escolhaCantor]);
                } else {
                    printf("Escolha de cantor inválida.\n");
                }
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção invalida!\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}