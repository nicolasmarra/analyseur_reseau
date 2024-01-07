#ifndef SMTP_H
#define SMTP_H


#include "utiles.h"

/*
    @brief: Fonction qui traite les paquets SMTP
    @param: paquet, le paquet à traiter
    @param: taille, la taille du paquet
    @param: verbosite, le niveau de verbosité
*/
void traiter_smtp(const u_char *paquet, int taille, int verbosite);

/*
    @brief: Fonction qui affiche les commandes SMTP
    @param: requete, la requete à analyser
    @param: taille, la taille du paquet

*/
void afficher_commandes_smtp(char *requete, int taille);

#endif