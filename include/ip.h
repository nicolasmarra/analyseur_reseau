#ifndef IP_H
#define IP_H

#include "utiles.h"

/*
    @brief Fonction qui traite les paquets IPv4
    @param paquet : le paquet à traiter
    @param verbosite : le niveau de verbosité
*/
void traiter_ipv4(const u_char *paquet, int verbosite);

/*
    @brief Fonction qui traite les paquets IPv6
    @param paquet : le paquet à traiter
    @param verbosite : le niveau de verbosité
*/
void traiter_ipv6(const u_char *paquet, int verbosite);



#endif