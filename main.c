#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _musica {
    char nomeMusica[40];     //Duas estruturas definidas, que vão armazenar informações sobre músicas e cantores
    char album[40];          //por exemplo, o nome, o ano de lancamento, o album, etc.
    int anoLancamento;
} Musica;

typedef struct _cantor {
    char nome[40];
    char generoMusical[15];
    int idade;
    Musica musicas[100];
    int numMusicas;
} Cantor;

Musica cadastrarMusica() {               //Esta função permite o usuário inserir os detalhes de uma nova musica.
    Musica novaMusica;
    printf("Insira o nome da musica: ");
    scanf(" %[^\n]s", novaMusica.nomeMusica);
    printf("Insira o nome do album: ");
    scanf(" %[^\n]s", novaMusica.album);
    printf("Insira o ano de lancamento: ");
    scanf(" %d", &novaMusica.anoLancamento);
    printf("\n");
    return novaMusica;
}

Cantor cadastrarCantor() {                //Esta função permite o usuário inserir os detalhes de um novo cantor.
    Cantor novoCantor;
    printf("Insira o nome do cantor: ");
    scanf(" %[^\n]s", novoCantor.nome);
    printf("Insira o genero musical: ");
    scanf(" %[^\n]s", novoCantor.generoMusical);
    printf("Insira a idade do cantor: ");
    scanf(" %d", &novoCantor.idade);
    novoCantor.numMusicas = 0;
    printf("\n");
    return novoCantor;
}

void listarCantores(Cantor cantores[], int numCantores) { //Está função percorre o array de cantores e lista
    int i;                                                //seus nomes na saída. Utilizada para listar uma
    for (i = 0; i < numCantores; i++) {                   //lista de cantores disponiveis.
        printf("%d - %s\n", i + 1, cantores[i].nome);
    }
    printf("\n");
}

void editarCantores(Cantor cantores[], int numCantores) { //Está funçao permite a ediçao de cantores especificos
    char nome[40];                                        //a mesma pede o nome do cantor que se deseja editar
    int i, opcao;                                         //onde se ela encontrar ela oferece as opcoes.

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
    printf("Cantor nao encontrado!\n\n");
}

void removerCantor(Cantor cantores[], int *numCantores) {  //Esta funcao permite remover um cantor do array.
    char nome[40];                                         //solicita o nome do cantor a ser removido, e se
    int i, encontrei = 0;                                  //encontrado ele reorganiza os mesmos.
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
        printf("Operacao realizada com sucesso!\n\n");
    } else {
        printf("Cantor nao encontrado!\n\n");
    }
}

void inserirMusica(Cantor *cantor) {     //Permite adicionar uma nova musica para o array de musicas de um
    if (cantor->numMusicas < 100) {      //cantor, verifica se possui o numero maximo de musicas permitidas.
        Musica novaMusica = cadastrarMusica();
        cantor->musicas[cantor->numMusicas] = novaMusica;
        cantor->numMusicas++;
        printf("Musica inserida com sucesso!\n\n");
    } else {
        printf("O cantor já possui o limite máximo de músicas!\n\n");
    }
}

void listarMusicasDoCantor(Cantor *cantor) {    //Lista todas as musicas de um cantor especifico.
    printf("Musicas de %s:\n", cantor->nome);
    for (int i = 0; i < cantor->numMusicas; i++) {
        Musica musica = cantor->musicas[i];
        printf("%d - %s - %s\n", i + 1, musica.nomeMusica, musica.album);
    }
    printf("\n");
}

void editarMusica(Musica musicas[], int numMusicas) { //Permite editar os detalhes de uma musica especifica
    char nomeMusica[40];                              //associada a um cantor.
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
                    printf("Opçao invalida!\n\n");
                    return;
            }
            printf("Operaçao realizada com sucesso!\n\n");
            return;
        }
    }
    printf("Musica não encontrada!\n\n");
}

void removerMusica(Musica musicas[], int *numMusicas) {
    char nomeMusica[40];
    int i, encontrei = 0;
    printf("Insira o nome da musica para remover: ");
    scanf(" %[^\n]s", nomeMusica);
    for (i = 0; i < *numMusicas; i++) {
        if (encontrei) {
            musicas[i - 1] = musicas[i];
        }
        if (strcmp(nomeMusica, musicas[i].nomeMusica) == 0) {
            encontrei = 1;
        }
    }
    if (encontrei) {
        (*numMusicas)--;
        printf("Operacao realizada com sucesso!\n\n");
    } else {
        printf("Musica não encontrada!\n\n");
    }
}

int main() {               //Esta é a funçao principal, onde contem o loop, onde o usuario pode escolher opçoes
    Cantor cantores[100];  //atraves de um menu, dependendo da escolha as funçoes mencionadas a cima são
    int numCantores = 0;   //para executar as açoes desejadas. O loop continua até o 0 ser acionado.
    int opcao;
    int escolhaCantor;
    int numMusicas = 0;
    Musica musicas[100];

    do {
        printf("Digite:\n");
        printf("  Digite 1 para cadastrar um cantor\n");
        printf("  Digite 2 para listar cantores e suas musicas\n");
        printf("  Digite 3 para editar cantor\n");
        printf("  Digite 4 para remover cantor\n");
        printf("  Digite 5 para adicionar uma musica a um cantor\n");
        printf("  Digite 6 para editar uma musica\n");
        printf("  Digite 7 para remover uma musica\n");
        printf("  Digite 0 para sair\n");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                cantores[numCantores] = cadastrarCantor();
                numCantores++;
                break;
            case 2:
                listarCantores(cantores, numCantores);
                printf("Escolha o numero de um cantor para listar suas musicas: ");
                scanf("%d", &escolhaCantor);
                escolhaCantor--;
                if (escolhaCantor >= 0 && escolhaCantor < numCantores) {
                    listarMusicasDoCantor(&cantores[escolhaCantor]);
                } else {
                    printf("Escolha de cantor invalida.\n");
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
                printf("Escolha o numero de um cantor para adicionar uma musica: ");
                int escolhaCantor;
                scanf("%d", &escolhaCantor);
                escolhaCantor--;
                if (escolhaCantor >= 0 && escolhaCantor < numCantores) {
                    inserirMusica(&cantores[escolhaCantor]);
                } else {
                    printf("Escolha de cantor invalida.\n");
                }
                break;

            case 6:
                editarMusica(musicas, numMusicas);
                break;

            case 7:
                removerMusica(musicas, &numMusicas);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}