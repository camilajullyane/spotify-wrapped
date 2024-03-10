#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "music.h"
#include "../user/user.h"

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