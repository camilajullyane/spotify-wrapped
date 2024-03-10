#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "default.h"

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