#ifndef DNS_H
#define DNS_H

#include "utiles.h"

#define ANSWER 1
#define NAME_SERVER 2
#define ADITIONNAL_INFO 3

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

/*
    @brief Fonction qui permet d'afficher les requêtes DNS
    @param requetes : les requêtes DNS
    @param nb_question : le nombre de questions
    @param position : la position actuelle du paquet
    @return : renvoie la nouvelle position du paquet
*/
int afficher_questions_dns(const u_char * requetes, int nb_questions, int position);


/*
    @brief Fonction qui permet d'afficher le nom DNS
    @param nom : le nom DNS
    @param position : la position actuelle du paquet
    @return : renvoie la nouvelle position du paquet
*/
int afficher_nom_dns(const u_char *nom, int position);


/*
    @brief Fonction qui permet d'afficher les informations (answer, name server, additional info) DNS
    @param requetes : les requêtes DNS
    @param nb_reponses : le nombre d'informations
    @param position : la position actuelle du paquet
    @param type : le type de l'information (answer, name server, additional info)
    @return : renvoie la nouvelle position du paquet
*/
int afficher_info_dns(const u_char *requetes, int nb_info, int position, int type);


/*
    @brief Fonction qui permet d'afficher le type de la réponse DNS
    @param type : le type de la réponse
*/
void afficher_type_reponse(int type);


/*
    @brief Fonction qui permet d'afficher les informations supplémentaires DNS
    @param requetes : les requêtes DNS
    @param nb_reponses : le nombre de réponses
    @param position : la position actuelle du paquet
    @return : renvoie la nouvelle position du paquet
*/
void afficher_nombre_type_reponse(int type, int n);


/*
    @brief Fonction qui permet d'afficher le type de la requête DNS
    @param type : le type de la requête
*/
void afficher_type_dns(int type);


/*
    @brief Fonction qui permet d'afficher la classe de la requête DNS
    @param class : la classe de la requête
*/
void afficher_class_dns(int class);

#endif
