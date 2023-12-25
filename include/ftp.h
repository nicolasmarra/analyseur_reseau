#ifndef FTP_H
#define FTP_H


#include "utiles.h"

int traiter_ftp(const u_char * paquet, int taille, int verbosite);

int recuperer_port(char *requete);


#endif