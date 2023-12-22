#ifndef ARP_H
#define ARP_H

#include "utiles.h"

/*
    @brief Fonction qui permet de traiter les paquets ARP
    @param paquet : le paquet à traiter
    @param verbosite : le niveau de verbosité
*/

void traiter_arp(const u_char *paquet, int verbosite);

/*
    @brief Fonction qui permet d'afficher le type de matériel
    @param materiel : le type de matériel
*/
void afficher_type_materiel(int materiel);

/*
    @brief Fonction qui permet d'afficher le type de protocole
    @param protocole : le type de protocole
*/
void afficher_type_protocole(int protocole);

/*
    @brief Fonction qui permet d'afficher les opérations
    @param opcode : l'opcode
*/
void afficher_operation(int opcode);

/*
    @brief Fonction qui permet d'afficher les adresses
    @param taille_mac : la taille de l'adresse mac
    @param taille_ip : la taille de l'adresse ip
    @param paquet : le paquet à traiter
*/
void afficher_adresses(int taille_mac, int taille_ip, const u_char *paquet);

#endif