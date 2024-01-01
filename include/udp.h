#ifndef UDP_H
#define UDP_H

#include "utiles.h"

/*
    @brief Fonction qui permet de traiter les paquets UDP
    @param paquet : le paquet à traiter
    @param taille : la taille du paquet
    @param verbosite : le niveau de verbosité
*/
void traiter_udp(const u_char *paquet, int taille, int verbosite);

/*
    @brief Fonction qui traite les ports UDP
    @param port_source: le port source
    @param port_destination: le port destination
    @param paquet: le paquet à traiter
    @param taille: la taille du paquet
    @param verbosite: le niveau de verbosité
*/
void traiter_port_udp(int port_source, int port_destination, const u_char *paquet,int taille, int verbosite);

#endif