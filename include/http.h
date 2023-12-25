#ifndef HTTP_H
#define HTTP_H

#include "utiles.h"

/*
    @brief: Fonction qui traite les paquets HTTP
    @param paquet: paquet le paquet à traiter
    @param taille: la taille du paquet
    @param verbosite: le niveau de verbosité
*/
void traiter_http(const u_char *paquet, int taille, int verbosite);



#endif