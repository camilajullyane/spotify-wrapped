#ifndef DEFAULT_H
#define DEFAULT_H

typedef struct rel_default
{
    int idUsuario;
    int idMusica;
    int idAlbum;
    int timeStamp;
    struct rel_default *next;
} Default;

void readCSV();
int addTailDefault();
void freeDefaultList();
#endif // DEFAULT_H