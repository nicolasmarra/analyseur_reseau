#ifndef BOOTP_H
#define BOOTP_H


#include "utiles.h"

/*
    @brief: fonction qui traiter les paquets bootp
    @param: paquet, le paquet a traiter
    @param: taille, la taille du paquet
    @param: verbosite, le niveau de verbosite
*/
void traiter_bootp(const u_char *paquet, int taille, int verbosite);

#endif