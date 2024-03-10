#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "album.h"
#include "../user/user.h"

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