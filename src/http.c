#include "http.h"

void traiter_http(const u_char *paquet, int taille, int verbosite) {
    printf("\n");
    printf("HTTP\n");

    // Verbosité de niveau 2
    if (verbosite == 2) 
    {
        // on affiche seulement le type de requête ou de réponse
        afficher_requete_http((char *)paquet);
    }
    // Verbosité de niveau 3
    else if (verbosite == 3) {

        afficher_informations_http(paquet, taille);

        /*
        for (int i = 0; i < taille; i++) {
            if(isprint(paquet[i]))
            printf("%c", paquet[i]);
        }*/
    }
}

void afficher_informations_http(const u_char *paquet, int taille)
{
    // on affiche les lignes du paquet
    int debut_ligne = 0;
    for (int i = 0; i < taille; i++) {
        // On vérifie si c'est la la fin de la ligne
        if (paquet[i] == '\r' && i + 1 < taille && paquet[i + 1] == '\n') {
            for (int j = debut_ligne; j < i; j++) {
                if (isprint(paquet[j])) {
                    printf("%c", paquet[j]);
                } else {
                    printf(".");
                }
            }
            printf("\r\n");
            i++;
            debut_ligne = i + 1;
        }
    }

    //On affiche le reste du paquet
    for (int j = debut_ligne; j < taille; j++) {
        if (isprint(paquet[j])) {
            printf("%c", paquet[j]);
        } else {
            printf(".");
        }
    }

    printf("\n");
}

void afficher_requete_http(char *requete)
{
    if(strncmp(requete, "GET", 3) == 0)
        printf("Requête : GET\n");
    else if(strncmp(requete, "POST", 4) == 0)
        printf("Requête : POST\n");
    else if(strncmp(requete, "HEAD", 4) == 0)
        printf("Requête : HEAD\n");
    else if(strncmp(requete, "PUT", 3) == 0)
        printf("Requête : PUT\n");
    else if(strncmp(requete, "DELETE", 6) == 0)
        printf("Requête : DELETE\n");
    else if(strncmp(requete, "CONNECT", 7) == 0)
        printf("Requête : CONNECT\n");
    else if(strncmp(requete, "OPTIONS", 7) == 0)
        printf("Requête : OPTIONS\n");
    else if(strncmp(requete, "TRACE", 5) == 0)
        printf("Requête : TRACE\n");
    else if(strncmp(requete, "PATCH", 5) == 0)
        printf("Requête : PATCH\n");
    else 
        printf("Réponse\n");
}