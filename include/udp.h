#ifndef UDP_H
#define UDP_H

#include "utiles.h"

/*
    @brief Fonction qui permet de traiter les paquets UDP
    @param paquet : le paquet à traiter
    @param verbosite : le niveau de verbosité
*/
void traiter_udp(const u_char *paquet, int verbosite);

#endif