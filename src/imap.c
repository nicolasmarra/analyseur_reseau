#include "imap.h"

void traiter_imap(const u_char *paquet, int taille, int verbosite) {
    printf("\n");
    printf("IMAP\n");

    // Verbosité de niveau 2

    char premiere_ligne[MAX_SIZE];
    if (verbosite == 2) {
        if(recuperer_premiere_ligne((char *)paquet, premiere_ligne) == 0) {
            afficher_requete_imap(premiere_ligne);
        }else
        {
        afficher_requete_imap((char *)paquet);
        }
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



int recuperer_premiere_ligne(char *requete, char *premiere_ligne)
{
    const char *index = strchr(requete, '\n');

    if (index != NULL)
    {
        size_t taille = index - requete;

        if (taille < MAX_SIZE)
        {
            strncpy(premiere_ligne, requete, taille);
            premiere_ligne[taille] = '\0'; 
        }
        return 0;
    }

    return -1;
}

void afficher_requete_imap(char *requete) {
    
    // réponse
    if (strstr(requete, "OK") != NULL) {
        afficher_commande_imap(requete,2);
    }
    // requête
    else {
        afficher_commande_imap(requete,1);
    }
}

void afficher_commande_imap(char *requete, int type) {
    if (strstr(requete, "LOGIN") != NULL)
        printf("%s - Commande : LOGIN\n", type == 1 ? "Requête" : "Réponse");
    else if (strstr(requete, "LOGOUT") != NULL)
        printf("%s - Commande : LOGOUT\n", type == 1 ? "Requête" : "Réponse");
    else if (strstr(requete, "SELECT") != NULL)
        printf("%s - Commande : SELECT\n", type == 1 ? "Requête" : "Réponse");
    else if (strstr(requete, "NOOP") != NULL)
        printf("%s - Commande : NOOP\n", type == 1 ? "Requête" : "Réponse");
    else if (strstr(requete, "LIST") != NULL)
        printf("%s - Commande : LIST\n", type == 1 ? "Requête" : "Réponse");
    else if (strstr(requete, "CAPABILITY") != NULL)
        printf("%s - Commande : CAPABILITY\n", type == 1 ? "Requête" : "Réponse");
    else if (strstr(requete, "EXAMINE") != NULL)
        printf("%s - Commande : EXAMINE\n", type == 1 ? "Requête" : "Réponse");
    else if (strstr(requete, "CREATE") != NULL)
        printf("%s - Commande : CREATE\n", type == 1 ? "Requête" : "Réponse");
    else if (strstr(requete, "DELETE") != NULL)
        printf("%s - Commande : DELETE\n", type == 1 ? "Requête" : "Réponse");
    else if (strstr(requete, "RENAME") != NULL)
        printf("%s - Commande : RENAME\n", type == 1 ? "Requête" : "Réponse");
    else if (strstr(requete, "APPEND") != NULL)
        printf("%s - Commande : APPEND\n", type == 1 ? "Requête" : "Réponse");
    else if (strstr(requete, "STATUS") != NULL)
        printf("%s - Commande : STATUS\n", type == 1 ? "Requête" : "Réponse");
    else if (strstr(requete, "SUBSCRIBE") != NULL)
        printf("%s - Commande : SUBSCRIBE\n", type == 1 ? "Requête" : "Réponse");
    else if (strstr(requete, "UNSUBSCRIBE") != NULL)
        printf("%s - Commande : UNSUBSCRIBE\n", type == 1 ? "Requête" : "Réponse");
    else if (strstr(requete, "SEARCH") != NULL)
        printf("%s - Commande : SEARCH\n", type == 1 ? "Requête" : "Réponse");
    else if (strstr(requete, "CHECK") != NULL)
        printf("%s - Commande : CHECK\n", type == 1 ? "Requête" : "Réponse");
    else if (strstr(requete, "CLOSE") != NULL)
        printf("%s - Commande : CLOSE\n", type == 1 ? "Requête" : "Réponse");
    else if (strstr(requete, "EXPUNGE") != NULL)
        printf("%s - Commande : EXPUNGE\n", type == 1 ? "Requête" : "Réponse");
    else if(strstr(requete, "STARTTLS") != NULL)
        printf("%s - Commande : STARTTLS\n", type == 1 ? "Requête" : "Réponse");
    else if(strstr(requete, "AUTHENTICATE") != NULL)
        printf("%s - Commande : AUTHENTICATE\n", type == 1 ? "Requête" : "Réponse");
    else if(strstr(requete, "STORE") != NULL)
        printf("%s - Commande : STORE\n", type == 1 ? "Requête" : "Réponse");
    else
        printf("\n");
}