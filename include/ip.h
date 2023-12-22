#ifndef IP_H
#define IP_H

#include "utiles.h"
#include <netinet/in.h>

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


/*
    @brief Fonction qui affiche le type de protocole
    @param protocole : le protocole à afficher
*/
void afficher_type_protocole_IP(int protocole);

/*
    @brief  Fonction qui traite les protocoles
    @param paquet : le paquet à traiter
    @param verbosite : le niveau de verbosité
    @param protocole : le protocole à traiter
    @param version : la version du protocole    
*/
void traiter_protocoles(const u_char *paquet, int verbosite, int protocole, int version);

#endif