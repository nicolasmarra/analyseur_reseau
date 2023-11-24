#ifndef TCP_H
#define TCP_H


#include "utiles.h"


/*
    @brief Fonction qui traite les paquets TCP
    @param paquet: le paquet à traiter
    @param verbosite: le niveau de verbosité
*/
void traiter_tcp(const u_char *paquet, int verbosite);

/*
    @brief Fonction qui traite les flags TCP
    @param tcp_header: structure contenant les flags

*/
//void traiter_flags(struct tcphdr *tcp);

/*
    @brief Fonction qui traite les options TCP
    @param tcp_header: structure contenant les options

*/
//void traiter_options(struct tcphdr *tcp_header);

#endif