#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "../default/default.h"

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