#ifndef TELNET_H
#define TELNET_H

#include "utiles.h"

/*
    * Fonction qui traite les paquets telnet
    * @param paquet : le paquet a traiter
    * @param taille : la taille du paquet
    * @param verbosite : le niveau de verbosite
*/
void traiter_telnet(const u_char *paquet, int taille, int verbosite);

void afficher_commandes_telnet(const uint8_t commande);

void afficher_options_telnet(const uint8_t option);
#endif
