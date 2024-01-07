#include "ftp.h"
#include "utiles.h"

int traiter_ftp(const u_char *paquet, int taille, int verbosite) {

    printf("\n");
    printf("FTP\n");

    if(verbosite == 2)
    {
        afficher_type_requete_ftp((char *)paquet, taille);
    }else if (verbosite == 3) {
        
        /*char *fin_commande = strstr((char *)paquet, "\r\n");

        if (fin_commande != NULL) {
            int taille = fin_commande - (char *)paquet;
            printf("%.*s\n", taille+1, paquet);
        }*/

        for(int i=0; i<taille; i++)
        {
            if(isprint(paquet[i]))
             printf("%c", paquet[i]);
            else printf(".");
        }

        printf("\n");
    }

    return recuperer_port_fttp((char *)paquet);

}

int recuperer_port_fttp(char *requete)
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

void afficher_type_requete_ftp(char *requete, int taille)
{
    if(strncmp(requete, "USER",4) == 0)
        printf("Request : USER \n");
    else if(strncmp(requete, "PASS",4) == 0)
        printf("Request: PASS\n");
    else if(strncmp(requete, "SYST",4) == 0)
        printf("Request: SYST\n");
    else if(strncmp(requete, "PWD",3) == 0)
        printf("Request: PWD\n");
    else if(strncmp(requete, "CWD",3) == 0)
        printf("Request: CWD \n");
    else if(strncmp(requete, "PORT",4) == 0)
        printf("Request: PORT\n");
    else if(strncmp(requete, "PASV",4) == 0)
        printf("Request: PASV\n");
    else if(strncmp(requete, "LIST",4) == 0)
        printf("Request: LIST\n");
    else if(strncmp(requete, "RETR",4) == 0)
        printf("Request: RETR\n");
    else if(strncmp(requete, "STOR",4) == 0)
        printf("Request: STOR\n");
    else if(strncmp(requete, "QUIT",4) == 0)
        printf("Request: QUIT\n");
    else if(strncmp(requete, "TYPE",4) == 0)
        printf("Request: TYPE\n");
    else if(strncmp(requete, "MODE",4) == 0)
        printf("Request: MODE\n");
    else if(strncmp(requete, "STRU",4) == 0)
        printf("Request: STRU\n");
    else if(strncmp(requete, "NOOP",4) == 0)
        printf("Request: NOOP\n");
    else if(strncmp(requete, "ABOR",4) == 0)
        printf("Request: ABOR\n");
    else if(strncmp(requete, "DELE",4) == 0)
        printf("Request: DELE\n");
    else if(strncmp(requete, "MKD",3) == 0)
        printf("Request: MKD\n");
    else if(strncmp(requete, "RMD",3) == 0)
        printf("Request: RMD\n");
    else if(strncmp(requete, "RNFR",4) == 0)
        printf("Request: RNFR\n");
    else if(strncmp(requete, "RNTO",4) == 0)
        printf("Request: RNTO\n");
    else if(strncmp(requete, "APPE",4) == 0)
        printf("REQUEST: APPE\n");
    else if(strncmp(requete, "ESPV",4) == 0)
        printf("Request: ESPV\n");
    else if(strncmp(requete, "EPRT",4) == 0)
        printf("Request: EPRT\n");
    else if(strncmp(requete, "AUTH",4) == 0)
        printf("Request: AUTH\n");
    else if(strncmp(requete, "PBSZ",4) == 0)
        printf("Request: PBSZ\n");
    else if(strncmp(requete, "PROT",4) == 0)
        printf("Request: PROT\n");
    else if(strncmp(requete, "CCC",3) == 0)
        printf("Request: CCC\n");
    else if(strncmp(requete, "FEAT",4) == 0)
        printf("Request: FEAT\n");
    else if(strncmp(requete, "OPTS",4) == 0)
        printf("Request: OPTS\n");
    else if(strncmp(requete, "SIZE",4) == 0)
        printf("Request: SIZE\n");
    else if(strncmp(requete, "MDTM",4) == 0)
        printf("Request: MDTM\n");
    else if(strncmp(requete, "REST",4) == 0)
        printf("Request: REST\n");
    else if(strncmp(requete, "MLSD",4) == 0)
        printf("Request: MLSD\n");
    else if(strncmp(requete, "MLST",4) == 0)
        printf("Request: MLST\n");
    else if(strncmp(requete, "SITE",4) == 0)
        printf("Request: SITE\n");
    else if(strncmp(requete, "STAT",4) == 0)
        printf("Request: STAT\n");
    else if(strncmp(requete, "HELP",4) == 0)
        printf("Request: HELP\n");
    else if(strncmp(requete, "ALLO",4) == 0)
        printf("Request: ALLO\n");
    else if(strncmp(requete, "NLST",4) == 0)
        printf("Request: NLST\n");
    else if(strncmp(requete, "ACCT",4) == 0)
        printf("Request: ACCT\n");
    else if(strncmp(requete, "SMNT",4) == 0)
        printf("Request: SMNT\n");
    else if(strncmp(requete, "REIN",4) == 0)
        printf("Request: REIN\n");
    else if(strncmp(requete, "STOU",4) == 0)
        printf("Request: STOU\n");
    else if(strncmp(requete, "CDUP",4) == 0)
        printf("Request: CDUP\n");
    else if(strncmp(requete, "XCUP",4) == 0)
        printf("Request: XCUP\n");
    else if(strncmp(requete, "XRMD",4) == 0)
        printf("Request: XRMD\n");
    else if(strncmp(requete, "XMKD",4) == 0)
        printf("Request: XMKD\n");
    else if(strncmp(requete, "XPWD",4) == 0)
        printf("Request: XPWD\n");
    else if(strncmp(requete, "XRCP",4) == 0)
        printf("Request: XRCP\n");
    else if(strncmp(requete, "XRSQ",4) == 0)
        printf("Request: XRSQ\n");
    else if(strncmp(requete, "XSEM",4) == 0)
        printf("Request: XSEM\n");
    else if(strncmp(requete, "XSEN",4) == 0)
        printf("Request: XSEN\n");
    else if(taille > 3 && requete[0] >= '1' && requete[0] <= '5' && requete[1] >= '0' && requete[1] <= '5' && requete[2] >= '0' && requete[2] <= '9')
        printf("Response: %.3s\n", requete);
    else
        printf("Request\n");
    
}