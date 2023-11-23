#ifndef ARGS_H
#define ARGS_H


#define VERBOSITE_DEFAULT 3

typedef struct args_t
{
    int verbosite;
    char *fichier;
    char *interface;
    char *filtre;
}args_t;


/**
 * @brief Initialise la structure args_t
 * @param args (structure contenant les options du programme)
*/
void initialiser_args(args_t *args);


/**
 * @brief Parse les arguments de la ligne de commande et définit les options du programme
 * @param argc (argument standard du main)
 * @param argv (argument standard du main)
 * @param args (structure contenant les options du programme)
 * @return 0 si tout s'est bien passé
*/
int parse_args(int argc, char *argv[], args_t *args);


/**
 * @brief Affiche les instructions d'utilisation du programme
*/
void afficher_aide(void);

#endif