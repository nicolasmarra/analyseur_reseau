#ifndef POP3_H
#define POP3_H

#include "utiles.h"


/*
    @brief: Fonction qui traite les paquets POP
    @param paquet: paquet le paquet à traiter
    @param taille: la taille du paquet
    @param verbosite: le niveau de verbosité
*/
void traiter_pop(const u_char *paquet, int taille, int verbosite);

#endif