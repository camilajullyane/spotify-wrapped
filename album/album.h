#ifndef ALBUM_H
#define ALBUM_H

typedef struct rel_album
{
    int idUsuario;
    int idAlbumPreferido;
    int numPlays;
    struct rel_album *next;
} Album;

void processRelAlbum();
void sumAlbum();
void freeAlbum();
int addTailAlbum();
void writeAlbum();

#endif // ALBUM_H