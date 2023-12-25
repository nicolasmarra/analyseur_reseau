#include "smtp.h"

void traiter_smtp(const u_char *paquet, int taille, int verbosite)
{
    printf("\n");
    printf("SMTP\n");

    if (verbosite > 2)
    {
        for (int i = 0; i < taille; i++)
        {
            printf("%c", paquet[i]);
        }

        printf("\n");
        
    }
}