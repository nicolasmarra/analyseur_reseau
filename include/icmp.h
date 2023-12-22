#ifndef ICMP_H
#define ICMP_H

#include <netinet/ip_icmp.h>
#include "utiles.h"

/*
    @brief Fonction qui permet de traiter les paquets ICMP
    @param paquet : le paquet à traiter
    @param verbosite : le niveau de verbosité
*/
void traiter_icmp(const u_char *paquet, int verbosite);


/*
    @brief Fonction qui permet d'afficher le type
    @param type : le type
*/
void afficher_type(int type);

#endif