#ifndef FTP_H
#define FTP_H


#include "utiles.h"

/*
    @brief: Fonction qui traite les paquets FTP
    @param paquet: paquet le paquet à traiter
    @param taille: la taille du paquet
    @param verbosite: le niveau de verbosité
    @return: le port
*/
int traiter_ftp(const u_char * paquet, int taille, int verbosite);


/*
    @brief: Fonction qui récupère le port de la requête FTP
    @param requete: la requête FTP
    @return: le port
*/
int recuperer_port_fttp(char *requete);


#endif