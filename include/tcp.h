#ifndef TCP_H
#define TCP_H


#include <netinet/tcp.h>
#include "utiles.h"

/*
    @brief Fonction qui traite les paquets TCP
    @param paquet: le paquet à traiter
    @param taille: la taille du paquet
    @param verbosite: le niveau de verbosité
*/
void traiter_tcp(const u_char *paquet, int taille, int verbosite);

/*
    @brief Fonction qui traite les flags TCP
    @param tcp_header: structure contenant les flags

*/
void traiter_flags(struct tcphdr *tcp);

/*
    @brief Fonction qui traite les options TCP
    @param tcp_header: structure contenant les options

*/
void traiter_options(struct tcphdr *tcp_header);


/*
    @brief Fonction qui traite les ports TCP
    @param port_source: le port source
    @param port_destination: le port destination
    @param paquet: le paquet à traiter
    @param taille: la taille du paquet
    @param verbosite: le niveau de verbosité
*/
void traiter_port_tcp(int port_source, int port_destination, const u_char *paquet,int taille, int verbosite);


#endif