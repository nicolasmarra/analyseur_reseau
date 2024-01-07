#ifndef IMAP_H
#define IMAP_H

#include "utiles.h"
#define MAX_SIZE 100

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
    @brief: Fonction qui récupère la première ligne d'une requête
    @param: requete: la requête à traiter
    @param: premiere_ligne: la première ligne de la requête
    @return 0 si la requête est bien traitée, -1 sinon

*/
int recuperer_premiere_ligne(char *requete, char *premiere_ligne);



/*
    @brief: Fonction qui affiche les commandes imap
    @param: requete: la requête à vérifier les commandes
    @param: type: le type de requête ou de réponse

*/
void afficher_commande_imap(char *requete, int type); 

#endif