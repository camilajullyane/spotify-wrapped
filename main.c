#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "default/default.h"
#include "user/user.h"
#include "music/music.h"
#include "album/album.h"

int main()
{
    Default *DefaultList = NULL;
    User *UserList = NULL;
    Music *MusicList = NULL;
    Album *AlbumList = NULL;
    Album *AuxList = NULL;

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
            processRelUser(&DefaultList, &UserList);
            writeUser(UserList);
            processRelMusic(&UserList, &MusicList);
            writeMusic(MusicList);
            sumAlbum(&UserList, &AuxList);
            processRelAlbum(&AuxList, &AlbumList);
            writeAlbum(AlbumList);
            freeDefaultList(&DefaultList);
            freeUserList(&UserList);
            freeMusicList(&MusicList);
            freeAlbum(&AlbumList);
            freeAlbum(&AuxList);
            printf("Carga realizada com sucesso!\n");
        } else if(strcmp(choice, "2") == 0)
        {
            printf("Adeus!");
            break;
        }
    }
    return 0;
}