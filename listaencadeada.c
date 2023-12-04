#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Musica {
    char titulo[100];
    char cantor[100];
    int duracao;
    struct Musica* proxima;
} Musica;

typedef struct Playlist {
    char nome[100];
    int numMusicas;
    Musica* musicas;
    struct Playlist* proxima;
} Playlist;

Musica* cadastrarMusica() {
    Musica* novaMusica = (Musica*)malloc(sizeof(Musica));
    if (novaMusica == NULL) {
         printf("Erro ao alocar memória para a playlist.\n");
        exit(1);
    }

    printf("Digite o nome da musica: ");
    scanf(" %[^\n]", novaMusica->titulo);
    printf("Digite o  nome do cantor: ");
    scanf(" %[^\n]", novaMusica->cantor);
    printf("Digite a duracao da musica (em segundos): ");
    scanf("%d", &(novaMusica->duracao));
    novaMusica->proxima = NULL;
    return novaMusica;
}

void editarMusica(Musica* listaMusicas) {
    if (listaMusicas == NULL) {
        printf("Nenhuma musica cadastrada.\n");
    } else {
        char tituloMusica[100];
        printf("Digite o titulo da musica que deseja editar: ");
        scanf(" %[^\n]", tituloMusica);

        Musica* atual = listaMusicas;
        while (atual != NULL) {
            if (strcmp(atual->titulo, tituloMusica) == 0) {
                int escolhaEdicao;
                printf("Musica encontrada:\n");
                printf("Titulo: %s, Cantor: %s, Duracao: %d segundos\n", atual->titulo, atual->cantor, atual->duracao);
                printf("\nEscolha o que deseja editar:\n");
                printf("1. Titulo\n");
                printf("2. Cantor\n");
                printf("3. Duracao\n");
                printf("4. Sair da edicao\n");
                printf("Opcao: ");
                scanf("%d", &escolhaEdicao);

                switch (escolhaEdicao) {
                    case 1:
                        printf("Insira o novo titulo da musica: ");
                        scanf(" %[^\n]", atual->titulo);
                        break;
                    case 2:
                        printf("Insira o novo nome do cantor: ");
                        scanf(" %[^\n]", atual->cantor);
                        break;
                    case 3:
                        printf("Insira a nova duracao da musica (em segundos): ");
                        scanf("%d", &(atual->duracao));
                        break;
                    case 4:
                        printf("Edicao finalizada.\n");
                        return;
                    default:
                        printf("Opcao invalida. Tente novamente.\n");
                }
                return;  
            }
            atual = atual->proxima;
        }

        printf("Musica \"%s\" nao encontrada.\n", tituloMusica);
    }
}


void listarMusicas(Musica* listaMusicas) {
    Musica* atual = listaMusicas;
    while (atual != NULL) {
        printf("Titulo: %s, Cantor: %s, Duracao: %d Segundos\n", atual->titulo, atual->cantor, atual->duracao);
        atual = atual->proxima;
    }
}

Playlist* cadastrarPlaylist() {
    Playlist* novaPlaylist = (Playlist*)malloc(sizeof(Playlist));
    if (novaPlaylist == NULL) {
        printf("Erro ao alocar memória para a playlist.\n");
        exit(1);
    }

    printf("Digite o nome da playlist: ");
    scanf(" %[^\n]", novaPlaylist->nome);
    novaPlaylist->numMusicas = 0;
    novaPlaylist->musicas = NULL;
    novaPlaylist->proxima = NULL;
    return novaPlaylist;
}

void listarPlaylists(Playlist* listaPlaylists) {
    Playlist* atual = listaPlaylists;
    while (atual != NULL) {
        printf("Nome da playlist: %s, Numero de musicas: %d\n", atual->nome, atual->numMusicas);
        atual = atual->proxima;
    }
}

void adicionarMusicaAPlaylist(Musica* musica, Playlist* playlist) {
    if (playlist->musicas == NULL) {
        playlist->musicas = musica;
    } else {
        Musica* atual = playlist->musicas;
        while (atual->proxima != NULL) {
            atual = atual->proxima;
        }
        atual->proxima = musica;
    }
    playlist->numMusicas++;
}

void removerMusicaDePlaylist(Playlist* playlist, char* tituloMusica) {
    Musica* atual = playlist->musicas;
    Musica* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->titulo, tituloMusica) == 0) {
            if (anterior == NULL) {
                playlist->musicas = atual->proxima;
            } else {
                anterior->proxima = atual->proxima;
            }
            playlist->numMusicas--;
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->proxima;
    }

    printf("Musica \"%s\" nao encontrada na playlist.\n", tituloMusica);
}

int main() {
    Musica* listaMusicas = NULL;
    Playlist* listaPlaylists = NULL;

    int escolha;
    do {
    printf("\nEscolha uma opcao:\n");
    printf("1. Cadastrar uma musica\n");
    printf("2. Editar uma musica\n");
    printf("3. Lista das musicas cadastradas\n");
    printf("4. Cadastrar nova playlist\n");
    printf("5. Remover uma playlist\n");
    printf("6. Lista das playlist cadastradas\n");
    printf("7. Adicionar musica a playlist\n");
    printf("8. Remover musica da playlist\n");
    printf("9. Sair do programa\n");
    printf("Opcao: ");


        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                if (listaMusicas == NULL) {
                    listaMusicas = cadastrarMusica();
                } else {
                    Musica* novaMusica = cadastrarMusica();
                    novaMusica->proxima = listaMusicas;
                    listaMusicas = novaMusica;
                }
                break;
            case 2:
                editarMusica(listaMusicas);
                break;
            case 3:
                if (listaMusicas == NULL) {
                    printf("Musica nao cadastrada.\n");
                } else {
                    listarMusicas(listaMusicas);
                }
                break;
            case 4:
                if (listaPlaylists == NULL) {
                    listaPlaylists = cadastrarPlaylist();
                } else {
                    Playlist* novaPlaylist = cadastrarPlaylist();
                    novaPlaylist->proxima = listaPlaylists;
                    listaPlaylists = novaPlaylist;
                }
                break;
            case 5:
                if (listaPlaylists == NULL) {
                    printf("Playlist nao cadastrada.\n");
                } else {
                    char nomePlaylist[100];
                    printf("Digite o nome da playlist que você deseja remover: ");
                    scanf(" %[^\n]", nomePlaylist);

                    Playlist* atual = listaPlaylists;
                    Playlist* anterior = NULL;
                    while (atual != NULL) {
                        if (strcmp(atual->nome, nomePlaylist) == 0) {
                            if (anterior == NULL) {
                                listaPlaylists = atual->proxima;
                            } else {
                                anterior->proxima = atual->proxima;
                            }
                            free(atual);
                            break;
                        }
                        anterior = atual;
                        atual = atual->proxima;
                    }

                    if (atual == NULL) {
                        printf("Playlist \"%s\" nao encontrada.\n", nomePlaylist);
                    }
                }
                break;
            case 6:
                if (listaPlaylists == NULL) {
                    printf("Playlist nao cadastrada.\n");
                } else {
                    listarPlaylists(listaPlaylists);
                }
                break;
            case 7:
                if (listaPlaylists == NULL || listaMusicas == NULL) {
                    printf("Nenhuma playlist ou música cadastrada.\n");
                } else {
                    char nomePlaylist[100];
                    printf("Digite o nome da playlist a qual deseja adicionar a musica: ");
                    scanf(" %[^\n]", nomePlaylist);

                    char tituloMusica[100];
                    printf("Digite o titulo da musica que deseja adicionar: ");
                    scanf(" %[^\n]", tituloMusica);

                    Playlist* playlistAtual = listaPlaylists;
                    Musica* musicaEncontrada = NULL;

                    while (playlistAtual != NULL) {
                        if (strcmp(playlistAtual->nome, nomePlaylist) == 0) {
                            Musica* musicaAtual = listaMusicas;
                            while (musicaAtual != NULL) {
                                if (strcmp(musicaAtual->titulo, tituloMusica) == 0) {
                                    musicaEncontrada = musicaAtual;
                                    break;
                                }
                                musicaAtual = musicaAtual->proxima;
                            }
                            if (musicaEncontrada != NULL) {
                                adicionarMusicaAPlaylist(musicaEncontrada, playlistAtual);
                            } else {
                                printf("Musica \"%s\" nao encontrado.\n", tituloMusica);
                            }
                            break;
                        }
                        playlistAtual = playlistAtual->proxima;
                    }

                    if (playlistAtual == NULL) {
                        printf("Playlist \"%s\" nao encontrada.\n", nomePlaylist);
                    }
                }
                break;
            case 8:
                if (listaPlaylists == NULL) {
                    printf("Playlist nao cadastrada.\n");
                } else {
                    char nomePlaylist[100];
                    printf("Digite o nome da playlist da qual deseja remover a musica: ");
                    scanf(" %[^\n]", nomePlaylist);

                    char tituloMusica[100];
                    printf("Digite o titulo da musica que deseja remover: ");
                    scanf(" %[^\n]", tituloMusica);

                    Playlist* playlistAtual = listaPlaylists;
                    while (playlistAtual != NULL) {
                        if (strcmp(playlistAtual->nome, nomePlaylist) == 0) {
                            removerMusicaDePlaylist(playlistAtual, tituloMusica);
                            break;
                        }
                        playlistAtual = playlistAtual->proxima;
                    }

                    if (playlistAtual == NULL) {
                        printf("Playlist \"%s\" nao encontrada.\n", nomePlaylist);
                    }
                }
                break;
            case 9:
            printf("Saindo do programa. Obrigado!\n");
                break;
            default:
                printf("Opcao invalida, tente novamente.\n");
        }
    } while (escolha != 9);

    
    Musica* atualMusica = listaMusicas;
    while (atualMusica != NULL) {
        Musica* proximaMusica = atualMusica->proxima;
        free(atualMusica);
        atualMusica = proximaMusica;
    }

    Playlist* atualPlaylist = listaPlaylists;
    while (atualPlaylist != NULL) {
        Playlist* proximaPlaylist = atualPlaylist->proxima;
        Musica* atualMusicaPlaylist = atualPlaylist->musicas;
        while (atualMusicaPlaylist != NULL) {
            Musica* proximaMusicaPlaylist = atualMusicaPlaylist->proxima;
            free(atualMusicaPlaylist);
            atualMusicaPlaylist = proximaMusicaPlaylist;
        }
        free(atualPlaylist);
        atualPlaylist = proximaPlaylist;
    }

    return 0;
}