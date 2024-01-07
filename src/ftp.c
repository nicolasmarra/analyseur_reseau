#include "ftp.h"
#include "utiles.h"

int traiter_ftp(const u_char *paquet, int taille, int verbosite) {

    printf("\n");
    printf("FTP\n");

    // Verbosité de niveau 2
    if (verbosite == 2) {
        // on affiche seulement le type de requête ou de réponse pour ce niveau
        // de verbosité
        afficher_type_requete_ftp((char *)paquet, taille);
    } else if (verbosite == 3) {

        /*char *fin_commande = strstr((char *)paquet, "\r\n");

        if (fin_commande != NULL) {
            int taille = fin_commande - (char *)paquet;
            printf("%.*s\n", taille+1, paquet);
        }*/

        for (int i = 0; i < taille; i++) {
            if (isprint(paquet[i]))
                printf("%c", paquet[i]);
            else
                printf(".");
        }

        printf("\n");
    }

    return recuperer_port_fttp((char *)paquet);
}

int recuperer_port_fttp(char *requete) {

    // Les réponses commençant par 150 Data connexion ... contiennent le port
    // accepté par le serveur pour les envoies et reception des données
    if (strstr(requete, "150 Data connection accepted from") != NULL) {
        char *port = strstr(requete, ":");
        if (port != NULL) {
            port = strtok(port + 1, ";");

            return atoi(port);
        }
    }

    return 0;
}

void afficher_type_requete_ftp(char *requete, int taille) {
    // on affiche le type de requête ou de réponse pour la verbosité de niveau 2
    if (strncmp(requete, "USER", 4) == 0)
        printf("Requête : USER \n");
    else if (strncmp(requete, "PASS", 4) == 0)
        printf("Requête: PASS\n");
    else if (strncmp(requete, "SYST", 4) == 0)
        printf("Requête: SYST\n");
    else if (strncmp(requete, "PWD", 3) == 0)
        printf("Requête: PWD\n");
    else if (strncmp(requete, "CWD", 3) == 0)
        printf("Requête: CWD \n");
    else if (strncmp(requete, "PORT", 4) == 0)
        printf("Requête: PORT\n");
    else if (strncmp(requete, "PASV", 4) == 0)
        printf("Requête: PASV\n");
    else if (strncmp(requete, "LIST", 4) == 0)
        printf("Requête: LIST\n");
    else if (strncmp(requete, "RETR", 4) == 0)
        printf("Requête: RETR\n");
    else if (strncmp(requete, "STOR", 4) == 0)
        printf("Requête: STOR\n");
    else if (strncmp(requete, "QUIT", 4) == 0)
        printf("Requête: QUIT\n");
    else if (strncmp(requete, "TYPE", 4) == 0)
        printf("Requête: TYPE\n");
    else if (strncmp(requete, "MODE", 4) == 0)
        printf("Requête: MODE\n");
    else if (strncmp(requete, "STRU", 4) == 0)
        printf("Requête: STRU\n");
    else if (strncmp(requete, "NOOP", 4) == 0)
        printf("Requête: NOOP\n");
    else if (strncmp(requete, "ABOR", 4) == 0)
        printf("Requête: ABOR\n");
    else if (strncmp(requete, "DELE", 4) == 0)
        printf("Requête: DELE\n");
    else if (strncmp(requete, "MKD", 3) == 0)
        printf("Requête: MKD\n");
    else if (strncmp(requete, "RMD", 3) == 0)
        printf("Requête: RMD\n");
    else if (strncmp(requete, "RNFR", 4) == 0)
        printf("Requête: RNFR\n");
    else if (strncmp(requete, "RNTO", 4) == 0)
        printf("Requête: RNTO\n");
    else if (strncmp(requete, "APPE", 4) == 0)
        printf("Requête: APPE\n");
    else if (strncmp(requete, "ESPV", 4) == 0)
        printf("Requête: ESPV\n");
    else if (strncmp(requete, "EPRT", 4) == 0)
        printf("Requête: EPRT\n");
    else if (strncmp(requete, "AUTH", 4) == 0)
        printf("Requête: AUTH\n");
    else if (strncmp(requete, "PBSZ", 4) == 0)
        printf("Requête: PBSZ\n");
    else if (strncmp(requete, "PROT", 4) == 0)
        printf("Requête: PROT\n");
    else if (strncmp(requete, "CCC", 3) == 0)
        printf("Requête: CCC\n");
    else if (strncmp(requete, "FEAT", 4) == 0)
        printf("Requête: FEAT\n");
    else if (strncmp(requete, "OPTS", 4) == 0)
        printf("Requête: OPTS\n");
    else if (strncmp(requete, "SIZE", 4) == 0)
        printf("Requête: SIZE\n");
    else if (strncmp(requete, "MDTM", 4) == 0)
        printf("Requête: MDTM\n");
    else if (strncmp(requete, "REST", 4) == 0)
        printf("Requête: REST\n");
    else if (strncmp(requete, "MLSD", 4) == 0)
        printf("Requête: MLSD\n");
    else if (strncmp(requete, "MLST", 4) == 0)
        printf("Requête: MLST\n");
    else if (strncmp(requete, "SITE", 4) == 0)
        printf("Requête: SITE\n");
    else if (strncmp(requete, "STAT", 4) == 0)
        printf("Requête: STAT\n");
    else if (strncmp(requete, "HELP", 4) == 0)
        printf("Requête: HELP\n");
    else if (strncmp(requete, "ALLO", 4) == 0)
        printf("Requête: ALLO\n");
    else if (strncmp(requete, "NLST", 4) == 0)
        printf("Requête: NLST\n");
    else if (strncmp(requete, "ACCT", 4) == 0)
        printf("Requête: ACCT\n");
    else if (strncmp(requete, "SMNT", 4) == 0)
        printf("Requête: SMNT\n");
    else if (strncmp(requete, "REIN", 4) == 0)
        printf("Requête: REIN\n");
    else if (strncmp(requete, "STOU", 4) == 0)
        printf("Requête: STOU\n");
    else if (strncmp(requete, "CDUP", 4) == 0)
        printf("Requête: CDUP\n");
    else if (strncmp(requete, "XCUP", 4) == 0)
        printf("Requête: XCUP\n");
    else if (strncmp(requete, "XRMD", 4) == 0)
        printf("Requête: XRMD\n");
    else if (strncmp(requete, "XMKD", 4) == 0)
        printf("Requête: XMKD\n");
    else if (strncmp(requete, "XPWD", 4) == 0)
        printf("Requête: XPWD\n");
    else if (strncmp(requete, "XRCP", 4) == 0)
        printf("Requête: XRCP\n");
    else if (strncmp(requete, "XRSQ", 4) == 0)
        printf("Requête: XRSQ\n");
    else if (strncmp(requete, "XSEM", 4) == 0)
        printf("Requête: XSEM\n");
    else if (strncmp(requete, "XSEN", 4) == 0)
        printf("Requête: XSEN\n");
    else if (taille > 3 && requete[0] >= '1' && requete[0] <= '5' &&
             requete[1] >= '0' && requete[1] <= '5' && requete[2] >= '0' &&
             requete[2] <= '9')
        printf("Réponse: %.3s\n", requete);
    else
        printf("Requête\n");
}