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

    // On convertit la requête en majuscule
    for (int i = 0; i < taille; i++) {
        requete[i] = toupper(requete[i]);
    }

    if (strncmp(requete, "HELO",4) == 0) {
        printf("C : HELO\n");
    } else if (strncmp(requete, "EHLO",4) == 0) {
        printf("C : EHLO\n");
    } else if (strncmp(requete, "MAIL",4) == 0) {
        printf("C : MAIL\n");
    } else if (strncmp(requete, "RCPT",4) == 0) {
        printf("C : RCPT\n");

    } else if (strncmp(requete, "DATA",4) == 0) {
        printf("C : DATA\n");

    } else if (strncmp(requete, "RSET",4) == 0) {
        printf("C : RSET\n");
    } else if (strncmp(requete, "NOOP",4) == 0) {
        printf("C : NOOP\n");
    } else if (strncmp(requete, "QUIT",4) == 0) {
        printf("C : QUIT\n");
    } else if (strncmp(requete, "STARTTLS",8) == 0) {
        printf("C : STARTTLS\n");
    } else if (strncmp(requete, "AUTH",4) == 0) {
        printf("C : AUTH\n");
    } else if (strncmp(requete, "VRFY",4) == 0) {
        printf("C : VRFY\n");
    } else if (strncmp(requete, "EXPN",4) == 0) {
        printf("C : EXPN\n");
    } else if (strncmp(requete, "HELP",4) == 0) {
        printf("C : HELP\n");
    } else if (strncmp(requete, "TURN",4) == 0) {
        printf("C : TURN\n");
    } else if (strncmp(requete, "ETRN",4) == 0) {
        printf("C : ETRN\n");
    } else if (strncmp(requete, "SEND",4) == 0) {
        printf("C : SEND\n");
    } else if (strncmp(requete, "SAML",4) == 0) {
        printf("C : SAML\n");
    } else if (strncmp(requete, "USER",4) == 0) {
        printf("C : USER\n");
    } else if (strncmp(requete, "PASS",4) == 0) {
        printf("C : PASS\n");
    }else if (taille > 3 && requete[0] >= '0' && requete[0] <= '9' &&
             requete[1] >= '0' && requete[1] <= '9' && requete[2] >= '0' &&
             requete[2] <= '9')
     {
        printf("S : %.3s\n", requete);
    }

}
