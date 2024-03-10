#ifndef MUSIC_H
#define MUSIC_H

typedef struct rel_music
{
    int idUsuario;
    int idMusicaPreferida;
    int numPlays;
    struct rel_music *next;
} Music;

void processRelMusic();
int addTailMusic();
void writeMusic();
void freeMusicList();

#endif // MUSIC_H