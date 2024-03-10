#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct rel_default
{
    int idUsuario;
    int idMusica;
    int idAlbum;
    int timeStamp;
    struct rel_default *next;
} Default;

typedef struct rel_user
{
    int idUsuario;
    int idMusica;
    int idAlbum;
    int numPlays;
    struct rel_user *next;
} User;

typedef struct rel_music
{
    int idUsuario;
    int idMusicaPreferida;
    int numPlays;
    struct rel_music *next;
} Music;

typedef struct rel_album
{
    int idUsuario;
    int idAlbumPreferido;
    int numPlays;
    struct rel_album *next;
} Album;

void readCSV();
int addTailDefault();
int addTailUser();
int addTailMusic();
void writeUser();
void processRelUser();
void processRelMusic();
void processRelAlbum();
void sumAlbum();
void freeDefaultList();
void freeUserList();
void freeMusicList();
void freeAlbum();
void writeMusic();
int addTailAlbum();
void writeAlbum();

int main()
{
    Default *DefaultList = NULL;
    User *UserList = NULL;
    Music *MusicList = NULL;
    Album *AlbumList = NULL;

    Album *AuxList = NULL;

    while (1)
    {
        char choice[100];
        printf("[1] - Realizar carga\n[2] - Encerrar programa\n");
        printf("Escolha uma opção: ");
        scanf("%s", choice);
        while (strcmp(choice, "1") != 0 && strcmp(choice, "2") != 0)
        {
            printf("Opção inválida. Digite novamente: ");
            scanf("%s", choice);
        }
        // Para quando o usuário escolher realizar carga
        if (!strcmp(choice, "1"))
        {
            char input[100];
            printf("Digite o nome do arquivo: ");
            scanf("%s", input);
            readCSV(input, &DefaultList);
            processRelUser(&DefaultList, &UserList);
            writeUser(UserList);
            processRelMusic(&UserList, &MusicList);
            writeMusic(MusicList);
            sumAlbum(&UserList, &AuxList);
            processRelAlbum(&AuxList, &AlbumList);
            writeAlbum(AlbumList);
            freeDefaultList(&DefaultList);
            freeUserList(&UserList);
            freeMusicList(&MusicList);
            freeAlbum(&AlbumList);
            freeAlbum(&AuxList);
            printf("Carga realizada com sucesso!\n");
        }
    }
    return 0;
}

void readCSV(char filename[100], Default **list)
{
    FILE *file = fopen(filename, "r");
    char buffer[255];
    // Caso não houver nada no arquivo
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    fgets(buffer, sizeof(buffer), file);
    // Abrir arquivo e ler linha por linha
    Default *tail = NULL;
    int cont = 0;
    while (!feof(file))
    {
        int idUsuario;
        int idMusica;
        int idAlbum;
        int timeStamp;

        fscanf(file, "%d;%d;%d;%d\n", &idUsuario, &idMusica, &idAlbum, &timeStamp);
        addTailDefault(list, &tail, idUsuario, idMusica, idAlbum, timeStamp);
        cont++;
        // printf("Linha %d lida.\n", cont);
    }
    fclose(file);
}

int addTailDefault(Default **head, Default **tail, int idUsuario, int idMusica, int idAlbum, int timeStamp)
{

    Default *newNode = malloc(sizeof(Default));

    if (newNode != NULL)
    { // testa se memoria foi alocada
        newNode->idUsuario = idUsuario;
        newNode->idMusica = idMusica;
        newNode->idAlbum = idAlbum;
        newNode->timeStamp = timeStamp;
        newNode->next = NULL;

        // caso 1: lista vazia
        if (*head == NULL)
        {
            *head = newNode;
        }
        else
        { // caso 2: lista jah contem pelo menos 1 elemento
            // busca posicao correta (ordenacao do menor p/ maior)
            Default *current = *head, *prevNode = NULL;
            while (current != NULL && current->idUsuario > idUsuario)
            {
                // passa para o proximo elemento
                prevNode = current;
                current = current->next;
            }

            // insere elemento entre nó anterior e nó atual
            if (prevNode != NULL)
            { // caso A: insercao no meio
                prevNode->next = newNode;
                newNode->next = current;
            }
            else
            { // caso B: insercao no inicio
                newNode->next = *head;
                *head = newNode;
            }
        }

        return 1; // sucesso
    }
    else
    {
        return 0; // sem memoria
    }
}

// int addTailDefault(Default **head, Default **tail, int idUsuario, int idMusica, int idAlbum, int timeStamp)
// {
//     Default *newNode = malloc(sizeof(Default));

//     if (newNode != NULL)
//     {
//         newNode->idUsuario = idUsuario;
//         newNode->idMusica = idMusica;
//         newNode->idAlbum = idAlbum;
//         newNode->timeStamp = timeStamp;
//         newNode->next = NULL;

//         if (*head == NULL)
//         {
//             *head = newNode;
//             *tail = newNode;
//         }
//         else
//         {
//             (*tail)->next = newNode;
//             *tail = newNode;
//         }
//         return 1;
//     }
//     else
//     {
//         return 0;
//     }
// }

int addTailUser(User **head, User **tail, int idUsuario, int idMusica, int idAlbum, int numPlays)
{
    User *newNode = malloc(sizeof(Default));

    if (newNode != NULL)
    {
        newNode->idUsuario = idUsuario;
        newNode->idMusica = idMusica;
        newNode->idAlbum = idAlbum;
        newNode->numPlays = numPlays;
        newNode->next = NULL;

        if (*head == NULL)
        {
            *head = newNode;
            *tail = newNode;
        }
        else
        {
            (*tail)->next = newNode;
            *tail = newNode;
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

void processRelUser(Default **list, User **head)
{
    Default *current_i = *list;
    User *tail = NULL;

    while (current_i != NULL)
    {
        User *current_user = *head;
        while (current_user != NULL)
        {
            if (current_user->idUsuario == current_i->idUsuario && current_user->idMusica == current_i->idMusica)
            {
                current_user->numPlays += 1;
                break;
            }
            current_user = current_user->next;
        }

        if (current_user == NULL)
        {
            addTailUser(head, &tail, current_i->idUsuario, current_i->idMusica, current_i->idAlbum, 1);
        }
        current_i = current_i->next;
    }
}

void writeUser(User *head)
{
    FILE *file = fopen("usuario_musica.csv", "w");
    User *current = head;

    fprintf(file, "idUsuario;idMusica;idAlbum;numPlays\n");
    while (current != NULL)
    {
        fprintf(file, "%d;%d;%d;%d\n", current->idUsuario, current->idMusica, current->idAlbum, current->numPlays);
        current = current->next;
    }
    fclose(file);
}

void processRelMusic(User **list, Music **head)
{
    User *current_i = *list;
    Music *tail = NULL;
    while (current_i != NULL)
    {
        Music *current_music = *head;
        while (current_music != NULL)
        {
            if (current_music->idUsuario == current_i->idUsuario)
            {
                if (current_i->numPlays > current_music->numPlays)
                {
                    current_music->idMusicaPreferida = current_i->idMusica;
                    current_music->numPlays = current_i->numPlays;
                }
                break;
            }
            current_music = current_music->next;
        }

        if (current_music == NULL)
        {
            addTailMusic(head, &tail, current_i->idUsuario, current_i->idMusica, current_i->numPlays);
        }
        current_i = current_i->next;
    }
}

int addTailMusic(Music **head, Music **tail, int idUsuario, int idMusicaPreferida, int numPlays)
{
    Music *newNode = malloc(sizeof(Music));

    if (newNode != NULL)
    {
        newNode->idUsuario = idUsuario;
        newNode->idMusicaPreferida = idMusicaPreferida;
        newNode->numPlays = numPlays;
        newNode->next = NULL;

        if (*head == NULL)
        {
            *head = newNode;
            *tail = newNode;
        }
        else
        {
            (*tail)->next = newNode;
            *tail = newNode;
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

void freeDefaultList(Default **head)
{
    Default *current = *head;
    Default *nextNode;

    while (current != NULL)
    {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    *head = NULL;
}

void freeUserList(User **head)
{
    User *current = *head;
    User *nextNode;

    while (current != NULL)
    {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    *head = NULL;
}

void writeMusic(Music *head)
{
    FILE *file = fopen("rel_musicas.csv", "w");
    Music *current = head;

    fprintf(file, "idUsuario;idMusicaPreferida;numPlays\n");
    while (current != NULL)
    {
        fprintf(file, "%d;%d;%d\n", current->idUsuario, current->idMusicaPreferida, current->numPlays);
        current = current->next;
    }
    fclose(file);
}

void sumAlbum(User **list, Album **head)
{
  User *current_i = *list;
  Album *tail = NULL;

  while (current_i != NULL)
  {
      Album *current_album = *head;
      while (current_album != NULL)
      {
          if (current_i->idUsuario == current_album->idUsuario && current_i->idAlbum == current_album->idAlbumPreferido)
          {
              current_album->numPlays += current_i->numPlays;
              break;
          }
          current_album = current_album->next;
      }

      if (current_album == NULL)
      {
          addTailAlbum(head, &tail, current_i->idUsuario, current_i->idAlbum, current_i->numPlays);
      }
      current_i = current_i->next;
  }
}

int addTailAlbum(Album **head, Album **tail, int idUsuario, int idAlbumPreferido, int numPlays)
{
    Album *newNode = malloc(sizeof(Album));

    if (newNode != NULL)
    {
        newNode->idUsuario = idUsuario;
        newNode->idAlbumPreferido = idAlbumPreferido;
        newNode->numPlays = numPlays;
        newNode->next = NULL;

        if (*head == NULL)
        {
            *head = newNode;
            *tail = newNode;
        }
        else
        {
            (*tail)->next = newNode;
            *tail = newNode;
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

void writeAlbum(Album *head)
{
    FILE *file = fopen("rel_albuns.csv", "w");
    Album *current = head;

    fprintf(file, "idUsuario;idAlbumPreferido;numPlays\n");
    while (current != NULL)
    {
        fprintf(file, "%d;%d;%d\n", current->idUsuario, current->idAlbumPreferido, current->numPlays);
        current = current->next;
    }
    fclose(file);
}


void processRelAlbum(Album **list, Album **head)
{
    Album *current_i = *list;
    Album *tail = NULL;
    while (current_i != NULL)
    {
        Album *current_album = *head;
        while (current_album != NULL)
        {
            if (current_album->idUsuario == current_i->idUsuario)
            {
                if (current_i->numPlays > current_album->numPlays)
                {
                    current_album->idAlbumPreferido = current_i->idAlbumPreferido;
                    current_album->numPlays = current_i->numPlays;
                }
                break;
            }
            current_album = current_album->next;
        }

        if (current_album == NULL)
        {
            addTailAlbum(head, &tail, current_i->idUsuario, current_i->idAlbumPreferido, current_i->numPlays);
        }
        current_i = current_i->next;
    }
}

void freeAlbum(Album **head)
{
    Album *current = *head;
    Album *nextNode;

    while (current != NULL)
    {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    *head = NULL;
}

void freeMusicList(Music **head) 
{
  Music *current = *head;
  Music *nextNode;

  while (current != NULL)
  {
      nextNode = current->next;
      free(current);
      current = nextNode;
  }

  *head = NULL;
}
// amo vcs :3$2
// amo vcs <3
// amo vcs S2