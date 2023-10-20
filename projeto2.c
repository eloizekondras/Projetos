#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição das estruturas
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

// Funções para ações

// Função para cadastrar uma nova música
Musica* cadastrarMusica() {
    Musica* novaMusica = (Musica*)malloc(sizeof(Musica));
    if (novaMusica == NULL) {
        printf("Erro ao alocar memória para a música.\n");
        exit(1);
    }

    printf("Insira o título da música: ");
    scanf(" %[^\n]", novaMusica->titulo);
    printf("Insira o nome do cantor: ");
    scanf(" %[^\n]", novaMusica->cantor);
    printf("Insira duração da música (em segundos): ");
    scanf("%d", &(novaMusica->duracao));
    novaMusica->proxima = NULL;
    return novaMusica;
}

// Função para editar informações de uma música existente
void editarMusica(Musica* musica) {
    printf("Insira o novo título da música: ");
    scanf(" %[^\n]", musica->titulo);
    printf("Insira o  novo nome do cantor: ");
    scanf(" %[^\n]", musica->cantor);
    printf("Insira a nova duração da música (em segundos): ");
    scanf("%d", &(musica->duracao));
}

// Função para listar todas as músicas cadastradas
void listarMusicas(Musica* listaMusicas) {
    Musica* atual = listaMusicas;
    while (atual != NULL) {
        printf("Título: %s, Cantor: %s, Duração: %d segundos\n", atual->titulo, atual->cantor, atual->duracao);
        atual = atual->proxima;
    }
}

// Função para cadastrar uma nova playlist
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

// Função para listar todas as playlists cadastradas
void listarPlaylists(Playlist* listaPlaylists) {
    Playlist* atual = listaPlaylists;
    while (atual != NULL) {
        printf("Nome da Playlist: %s, Número de Músicas: %d\n", atual->nome, atual->numMusicas);
        atual = atual->proxima;
    }
}

// Função para adicionar uma música a uma playlist
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

// Função para remover uma música de uma playlist
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
            return;
        }
        anterior = atual;
        atual = atual->proxima;
    }

    printf("Música \"%s\" não encontrada na playlist.\n", tituloMusica);
}


// Função principal
int main() {
    Musica* listaMusicas = NULL;
    Playlist* listaPlaylists = NULL;

    int escolha;
    do {
        printf("\nEscolha uma opção:\n");
        printf("1. Cadastrar uma nova música\n");
        printf("2. Editar informações de uma música\n");
        printf("3. Listar todas as músicas cadastradas\n");
        printf("4. Cadastrar uma nova playlist\n");
        printf("5. Remover uma playlist\n");
        printf("6. Listar todas as playlists cadastradas\n");
        printf("7. Adicionar uma música a uma playlist\n");
        printf("8. Remover uma música de uma playlist\n");
        printf("9. Sair do programa\n");
        printf("Opção: ");
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
                if (listaMusicas == NULL) {
                    printf("Nenhuma música cadastrada.\n");
                } else {
                    char tituloMusica[100];
                    printf("Digite o título da música que deseja editar: ");
                    scanf(" %[^\n]", tituloMusica);

                    Musica* atual = listaMusicas;
                    while (atual != NULL) {
                        if (strcmp(atual->titulo, tituloMusica) == 0) {
                            editarMusica(atual);
                            break;
                        }
                        atual = atual->proxima;
                    }

                    if (atual == NULL) {
                        printf("Música \"%s\" não encontrada.\n", tituloMusica);
                    }
                }
                break;
            case 3:
                if (listaMusicas == NULL) {
                    printf("Nenhuma música cadastrada.\n");
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
                    printf("Nenhuma playlist cadastrada.\n");
                } else {
                    char nomePlaylist[100];
                    printf("Digite o nome da playlist que deseja remover: ");
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
                        printf("Playlist \"%s\" não encontrada.\n", nomePlaylist);
                    }
                }
                break;
            case 6:
                if (listaPlaylists == NULL) {
                    printf("Nenhuma playlist cadastrada.\n");
                } else {
                    listarPlaylists(listaPlaylists);
                }
                break;
            case 7:
                if (listaPlaylists == NULL || listaMusicas == NULL) {
                    printf("Nenhuma playlist ou música cadastrada.\n");
                } else {
                    char nomePlaylist[100];
                    printf("Digite o nome da playlist à qual deseja adicionar a música: ");
                    scanf(" %[^\n]", nomePlaylist);

                    char tituloMusica[100];
                    printf("Digite o título da música que deseja adicionar: ");
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
                                printf("Música \"%s\" não encontrada.\n", tituloMusica);
                            }
                            break;
                        }
                        playlistAtual = playlistAtual->proxima;
                    }

                    if (playlistAtual == NULL) {
                        printf("Playlist \"%s\" não encontrada.\n", nomePlaylist);
                    }
                }
                break;
            case 8:
                if (listaPlaylists == NULL) {
                    printf("Nenhuma playlist cadastrada.\n");
                } else {
                    char nomePlaylist[100];
                    printf("Digite o nome da playlist da qual deseja remover a música: ");
                    scanf(" %[^\n]", nomePlaylist);

                    char tituloMusica[100];
                    printf("Digite o título da música que deseja remover: ");
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
                        printf("Playlist \"%s\" não encontrada.\n", nomePlaylist);
                    }
                }
                break;
            case 9:
                // Sair do programa
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (escolha != 9);

    // Libere a memória alocada
    Musica* atualMusica = listaMusicas;
    while (atualMusica != NULL) {
        Musica* proximaMusica = atualMusica->proxima;
        free(atualMusica);
        atualMusica = proximaMusica;
    }

    Playlist* atualPlaylist = listaPlaylists;
    while (atualPlaylist != NULL) {
        Playlist* proximaPlaylist = atualPlaylist->proxima;
        free(atualPlaylist);
        atualPlaylist = proximaPlaylist;
    }

    return 0;
}
