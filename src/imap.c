#include "imap.h"

void traiter_imap(const u_char *paquet, int taille, int verbosite)
{
    printf("\n");
    printf("IMAP\n");

    if (verbosite > 1)
    {
    }

    if (verbosite > 2)
    {
        for (int i = 0; i < taille; i++)
        {
            printf("%c", paquet[i]);
        }
        printf("\n");
    }
}