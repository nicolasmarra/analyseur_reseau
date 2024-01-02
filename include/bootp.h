#ifndef BOOTP_H
#define BOOTP_H


#include "utiles.h"
#include "bootp_reference.h"

#define TAG_SIP_SERVERS 120
#define TAG_TFTP_SERVER_ADDRESS 150
#define TAG_CLIENT_LAST_TRANSACTION_TIME 91

#define DHCPLEASEQUERY 10


/*
    @brief: fonction qui traiter les paquets bootp
    @param: paquet, le paquet a traiter
    @param: taille, la taille du paquet
    @param: verbosite, le niveau de verbosite
*/
void traiter_bootp(const u_char *paquet, int taille, int verbosite);


/*
    @brief: fonction qui affiche les options bootp
    @param: vendor_specific, les options a afficher
*/
void afficher_options_bootp(uint8_t *vendor_specific);


/*
    @brief: fonction qui affiche les données relatives au temps
    @param: description, la description des données à afficher
*/
void afficher_temps(char * description, int temps);

/*
    @brief: fonction qui affiche les données relatives à la liste de paramètres
    @param: item, la valeur de l'item à afficher
*/
void afficher_liste_parametres(int item);

/*
    @brief: fonction qui affiche une info
    @param: info, l'info à afficher
    @param: taille, la taille de l'info
    @param: type, le type de l'info
*/
void afficher_info(uint8_t *info, uint8_t taille, int type);

/*
    @brief: fonction qui affiche un message dhcp
    @param: type_message, le type de message à afficher

*/
void afficher_message_dhcp(int type_message);


#endif