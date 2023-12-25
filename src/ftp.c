#include "ftp.h"
#include "utiles.h"

int traiter_ftp(const u_char *paquet, int taille, int verbosite) {

    printf("\n");
    printf("FTP\n");

    if(verbosite > 1)
    {
        
    }

    if (verbosite > 2) {
        
        /*char *fin_commande = strstr((char *)paquet, "\r\n");

        if (fin_commande != NULL) {
            int taille = fin_commande - (char *)paquet;
            printf("%.*s\n", taille+1, paquet);
        }*/

        for(int i=0; i<taille; i++)
        {
            printf("%c", paquet[i]);
        }

        printf("\n");
    }

    return recuperer_port((char *)paquet);

}

int recuperer_port(char *requete)
{
    if(strstr(requete, "150 Data connection accepted from") != NULL)
    {
        char * port = strstr(requete, ":");
        if(port != NULL)
        {
        port = strtok(port+1, ";");

        return atoi(port);
        }
    }

    return 0;
}
