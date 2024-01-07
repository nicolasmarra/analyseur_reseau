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

/*
    @brief: Fonction qui affiche les informations du paquet HTTP
    @param paquet: paquet le paquet à traiter
    @param taille: la taille du paquet

*/
void afficher_informations_http(const u_char *paquet, int taille);

/*
    @brief: Fonction qui affiche le type de requête HTTP
    @param requete: la requête à afficher
*/
void afficher_requete_http(char *requete);

#endif