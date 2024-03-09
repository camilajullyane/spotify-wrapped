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
            writeOrder(DefaultList);
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
        addFinal(list, &tail, idUsuario, idMusica, idAlbum, timeStamp);
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

void writeUser(Default *list)
{
    FILE *file = fopen("usuario_musica.csv", "a");
    Default *current = list;
    while (current != NULL)
    {
        fprintf(file, "%d,%d,%d,%d\n", current->idUsuario, current->idMusica, current->idAlbum, current->timeStamp);
        current = current->next;
    }
    fclose(file);
}

int addTailUser(Default **head, Default **tail, int idUsuario, int idMusica, int idAlbum, int numPlays)
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
    Default *current_j = *list;
    User *head = NULL;
    User *tail = NULL;
    int count = 0;
    int j;
    int idUsuario;
    int idMusica;
    int idAlbum;
    int numPlays;

    while (current_i != NULL)
    {
        while (current_j != NULL)
        {
            // Soma os pedidos com o mesmo código
            if (current_j->idAlbum == current_i->idAlbum)
            {
                array[j].TotalItensVendidos += p[i].TotalItensVendidos;
                array[j].FatTotal += p[i].FatTotal;
                break;
            }
            j++;
        }
        // Caso não tenha nenhum pedido com o mesmo código
        if (j == count)
        {
            current_j->idUsuario = p[i].CodFilial;
            array[count].TotalItensVendidos = p[i].TotalItensVendidos;
            array[count].FatTotal = p[i].FatTotal;
            count++;
        }
    }
    writeUser(head);
}
