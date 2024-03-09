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
void CreateFile();
void writeUser();
void processRelUser();
void writeUser();

int main()
{
    CreateFile(); // Criar arquivos para armazenar os dados]
    Default *DefaultList = NULL;

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
            //writeOrder(DefaultList);
            processRelUser(&DefaultList);
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
        printf("Linha %d lida.\n", cont);
    }
    fclose(file);
}

int addTailDefault(Default **head, Default **tail, int idUsuario, int idMusica, int idAlbum, int timeStamp)
{
    Default *newNode = malloc(sizeof(Default));

    if (newNode != NULL)
    {
        newNode->idUsuario = idUsuario;
        newNode->idMusica = idMusica;
        newNode->idAlbum = idAlbum;
        newNode->timeStamp = timeStamp;
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

void CreateFile()
{
    FILE *file = fopen("usuario_musica.csv", "w");
    fprintf(file, "idUsuario,idMusica,idAlbum,numPlays\n");
    fclose(file);
}

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

void processRelUser(Default **list)
{
    Default *current_i = *list;
    User *head = NULL;
    User *tail = NULL;

    while (current_i != NULL)
    {
        User *current_user = head;
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
            addTailUser(&head, &tail, current_i->idUsuario, current_i->idMusica, current_i->idAlbum, 1);
            // User *newUser = malloc(sizeof(User));
            // newUser->idUsuario = current_i->idUsuario;
            // newUser->idMusica = current_i->idMusica;
            // newUser->idAlbum = current_i->idAlbum;
            // newUser->numPlays = 1;
            // newUser->next = NULL;

            // if (head == NULL)
            // {
            //     head = newUser;
            //     tail = newUser;
            // }
            // else
            // {
            //     tail->next = newUser;
            //     tail = newUser;
            // }
        }
        current_i = current_i->next;
    }
    writeUser(head);
}

void writeUser(User *head)
{
    FILE *file = fopen("usuario_musica.csv", "w");
    User *current = head;

    fprintf(file, "idUsuario,idMusica,idAlbum,numPlays\n");
    while (current != NULL)
    {
        fprintf(file, "%d,%d,%d, %d\n", current->idUsuario, current->idMusica, current->idAlbum,current->numPlays);
        current = current->next;
    }
    fclose(file);
}