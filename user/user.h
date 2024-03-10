#ifndef USER_H
#define USER_H

typedef struct rel_user
{
    int idUsuario;
    int idMusica;
    int idAlbum;
    int numPlays;
    struct rel_user *next;
} User;

void processRelUser();
int addTailUser();
void freeUserList();
void writeUser();

#endif // USER_H