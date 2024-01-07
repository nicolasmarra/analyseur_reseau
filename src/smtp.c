#include "smtp.h"

void traiter_smtp(const u_char *paquet, int taille, int verbosite) {
    printf("\n");
    printf("SMTP\n");

    if (verbosite == 2) {
        afficher_commandes_smtp((char *)paquet, taille);
    }

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

void afficher_commandes_smtp(char *requete, int taille) {
    if (strstr(requete, "HELO") != NULL) {
        printf("C : HELO\n");
    } else if (strstr(requete, "EHLO") != NULL) {
        printf("C : EHLO\n");
    } else if (strstr(requete, "MAIL") != NULL) {
        printf("C : MAIL\n");
    } else if (strstr(requete, "RCPT") != NULL) {
        printf("C : RCPT\n");

    } else if (strstr(requete, "DATA") != NULL) {
        printf("C : DATA\n");

    } else if (strstr(requete, "RSET") != NULL) {
        printf("C : RSET\n");
    } else if (strstr(requete, "NOOP") != NULL) {
        printf("C : NOOP\n");
    } else if (strstr(requete, "QUIT") != NULL) {
        printf("C : QUIT\n");
    } else if (strstr(requete, "STARTTLS") != NULL) {
        printf("C : STARTTLS\n");
    } else if (strstr(requete, "AUTH") != NULL) {
        printf("C : AUTH\n");
    } else if (strstr(requete, "VRFY") != NULL) {
        printf("C : VRFY\n");
    } else if (strstr(requete, "EXPN") != NULL) {
        printf("C : EXPN\n");
    } else if (strstr(requete, "HELP") != NULL) {
        printf("C : HELP\n");
    } else if (strstr(requete, "TURN") != NULL) {
        printf("C : TURN\n");
    } else if (strstr(requete, "ETRN") != NULL) {
        printf("C : ETRN\n");
    } else if (strstr(requete, "SEND") != NULL) {
        printf("C : SEND\n");
    } else if (strstr(requete, "SAML") != NULL) {
        printf("C : SAML\n");
    } else if (strstr(requete, "USER") != NULL) {
        printf("C : USER\n");
    } else if (strstr(requete, "PASS") != NULL) {
        printf("C : PASS\n");
    } else if (taille > 3 && requete[0] >= '0' && requete[0] <= '9' &&
             requete[1] >= '0' && requete[1] <= '9' && requete[2] >= '0' &&
             requete[2] <= '9')
     {
        printf("S : %.3s\n", requete);
    }

}
