#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef  struct _musica Musica;

typedef struct _cantor {
    char nome[40];
    char generoMusical[15];
    int idade;
    Musica *musicas[100];
    int numMusicas;
} Cantor;

typedef struct _musica {
    char nomeMusica[40];
    char album[40];
    int anoLancamento;
} Musica;

Musica cadastrarMusica(){
    Musica novaMusica;
    printf("Insira o nome da musica: ");
    scanf(" %[^\n]s", novaMusica.nomeMusica);
    printf("Insira o nome do album: ");
    scanf(" %[^\n]s", novaMusica.album);
    printf("Insira o ano de lançamento: ");
    scanf(" %d", &novaMusica.anoLancamento);
    return novaMusica;
}

Cantor cadastrarCantor() {
    Cantor novoCantor;
    printf("Insira o nome do cantor: ");
    scanf(" %[^\n]s", novoCantor.nome);
    printf("Insira qual o genero musical: ");
    scanf(" %[^\n]s", novoCantor.generoMusical);
    printf("Insira a idade do cantor: ");
    scanf(" %d", &novoCantor.idade);
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
        cantor->musicas[cantor->numMusicas] = malloc(sizeof(Musica));
        *(cantor->musicas[cantor->numMusicas]) = novaMusica;
        cantor->numMusicas++;
        printf("Música inserida com sucesso!\n\n");
    } else {
        printf("O cantor já possui o limite máximo de músicas!\n\n");
    }
}
void listarMusicasDoCantor(Cantor *cantor) {
    printf("Músicas de %s:\n", cantor->nome);
    for (int i = 0; i < cantor->numMusicas; i++) {
        Musica *musica = cantor->musicas[i];
        printf("%d - %s - %s\n", i + 1, musica->nomeMusica, musica->album);
    }
    printf("\n");
}

void editarMusica(Musica musicas[], int numMusicas) {
    char nomeMusica[40];
    int i, opcao;

    printf("Insira o nome da musica a ser editada: ");
    scanf(" %[^\n]s", nomeMusica);

    for (i = 0; i < numMusicas; i++) {
        if (strcmp(nomeMusica, musicas[i].nomeMusica) == 0) {
            printf("Digite:\n");
            printf("  Digite 1 para editar o nome da musica\n");
            printf("  Digite 2 para editar o nome do album\n");
            printf("  Digite 3 para editar o ano de lançamento da musica\n");
            scanf(" %d", &opcao);
            switch (opcao) {
                case 1:
                    printf("Insira o novo nome da musica: ");
                    scanf(" %[^\n]s", musicas[i].nomeMusica);
                    break;
                case 2:
                    printf("Insira o novo nome do album: ");
                    scanf(" %[^\n]s", musicas[i].album);
                    break;
                case 3:
                    printf("Insira o novo ano de lançamento da musica: ");
                    scanf(" %d", &musicas[i].anoLancamento);
                    break;
                default:
                    printf("Opção invalida!\n\n");
                    return;
            }
            printf("Operação realizada com sucesso!\n\n");
            return;
        }
    }
    printf("Musica não encontrada!\n\n");
}

int main(){
    Cantor cantores[100];  // Limite de 100 cantores
    int numCantores = 0;
    int opcao;
    int escolhaCantor;

    do {
        printf("Digite:\n");
        printf("  Digite 1 para cadastrar um cantor\n");
        printf("  Digite 2 para listar cantores e suas musicas\n");
        printf("  Digite 3 para editar cantor\n");
        printf("  Digite 4 para remover cantor\n");
        printf("  Digite 5 para adicionar uma musica a um cantor\n");
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
