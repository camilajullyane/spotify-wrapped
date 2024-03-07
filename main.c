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
int addFinal();

int main()
{
    // CreateFile();       // Criar arquivos para armazenar os dados]
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
    while (!feof(file))
    {
        int idUsuario;
        int idMusica;
        int idAlbum;
        int timeStamp;

        fscanf(file, "%d,%d,%d,%d\n", &idUsuario, &idMusica, &idAlbum, &timeStamp);
        addFinal(list, idUsuario, idMusica, idAlbum, timeStamp);
    }
    fclose(file);
}

int addFinal(Default **head, int idUsuario, int idMusica, int idAlbum, int timeStamp)
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
        }
        else
        {
            Default *current = NULL;

            current = *head;

            while (current->next != NULL)
            {
                current = current->next;
            }

            current->next = newNode;
        }
        return 1;
    }
    else
    {
        return 0;
    }
}