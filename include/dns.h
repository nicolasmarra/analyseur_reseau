#ifndef DNS_H
#define DNS_H

#include "utiles.h"

struct dnshdr {
    uint16_t id;
    uint16_t flags;
    uint16_t questions;
    uint16_t answers;
    uint16_t authority;
    uint16_t additional;
};

/*
    @brief Fonction qui permet de traiter les paquets DNS
    @param paquet : le paquet à traiter
    @param taille : la taille du paquet
    @param verbosite : le niveau de verbosité
*/
void traiter_dns(const u_char *paquet, int taille, int verbosite);



#endif
