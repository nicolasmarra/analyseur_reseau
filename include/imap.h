#ifndef IMAP_H
#define IMAP_H

#include "utiles.h"

/*
    @brief: Fonction qui traite les paquets imap
    @param: paquet: le paquet à traiter
    @param: taille: taille du paquet
    @param: verbosite: niveau de verbosité
*/
void traiter_imap(const u_char *paquet, int taille, int verbosite);

#endif