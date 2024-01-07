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


/*
    @brief: Fonction qui affiche le type de requête ou de réponse
    @param: requete: la requête à afficher


*/
void afficher_requete_imap(char *requete);


/*
    @brief: Fonction qui affiche les commandes imap
    @param: requete: la requête à vérifier les commandes
    @param: type: le type de requête ou de réponse

*/
void afficher_commande_imap(char *requete, int type); 

#endif