#include "pop3.h"

void traiter_pop(const u_char *paquet, int taille, int verbosite) {
    printf("\n");
    printf("POP\n");

    // Verbosité de niveau 2
    if (verbosite ==  2) {
    afficher_commande_pop((char *)paquet);
    }

    // Verbosité de niveau 3

    else if (verbosite == 3) {
        for (int i = 0; i < taille; i++) {
            if (isprint(paquet[i]))
                printf("%c", paquet[i]);
            else
                printf(".");
        }

        printf("\n");
    }
}

void afficher_commande_pop(char * requete)
{

    // Réponses du serveur
    if(strstr(requete, "+OK") != NULL)
    {
        printf("S : +OK\n");
    }else if(strstr(requete, "-ERR") != NULL)
    {
        printf("S : -ERR\n");   
    }
    // Commandes POP3 - Client 

    else if(strstr(requete, "USER") != NULL)
    {
        printf("C : USER\n");
    }else if(strstr(requete, "PASS") != NULL)
    {
        printf("C : PASS\n");
    }else if(strstr(requete, "STAT") != NULL)
    {
        printf("C : STAT\n");
    }else if(strstr(requete, "LIST") != NULL)
    {
        printf("C : LIST\n");
    }else if(strstr(requete, "RETR") != NULL)
    {
        printf("C : RETR\n");
    }else if(strstr(requete, "DELE") != NULL)
    {
        printf("C : DELE\n");
    }else if(strstr(requete, "QUIT") != NULL)
    {
        printf("C : QUIT\n");
    }
    else if(strstr(requete, "UIDL") != NULL)
    {
        printf("C : UIDL\n");
    }
    else if(strstr(requete, "TOP") != NULL)
    {
        printf("C : TOP\n");
    }
    else if(strstr(requete, "LAST") != NULL)
    {
        printf("C : LAST\n");
    }
    
    else if(strstr(requete, "RSET") != NULL)
    {
        printf("C : RSET\n");
    }
    else if(strstr(requete, "NOOP") != NULL)
    {
        printf("C : NOOP\n");
    }
    else if(strstr(requete, "CAPA") != NULL)
    {
        printf("C : CAPA\n");
    }
    else if(strstr(requete, "APOP") != NULL)
    {
        printf("C : APOP\n");
    }
    
}