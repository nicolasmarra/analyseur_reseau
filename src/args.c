#include "args.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void initialiser_args(args_t *args) {
    args->verbosite = VERBOSITE_DEFAULT;
    args->interface = NULL;
    args->fichier = NULL;
    args->filtre = NULL;
}

int parse_args(int argc, char *argv[], args_t *args) {
    initialiser_args(args);

    int opt;
    while ((opt = getopt(argc, argv, "i:o:f:v:h")) != -1) {
        switch (opt) {
        case 'i':
            args->interface = optarg;
            break;
        case 'o':
            args->fichier = optarg;
            break;
        case 'f':
            args->filtre = optarg;
            break;
        case 'v':
            args->verbosite = atoi(optarg);
            if (args->verbosite < 1 || args->verbosite > 3) {
                fprintf(stderr, "Niveau de verbosité invalide : %s\n", optarg);
                afficher_aide();
                exit(EXIT_FAILURE);
            }
            break;
        case 'h':
            afficher_aide();
            exit(EXIT_FAILURE);
        default:
            fprintf(stderr, "Option inconnue: %c\n", optopt);
            afficher_aide();
            exit(EXIT_FAILURE);
        }
    }

    if (args->interface == NULL && args->fichier == NULL) {
        fprintf(stderr, "Vous devez choisir l'option -i ou l'option -f\n");
        afficher_aide();
        exit(EXIT_FAILURE);
    } else if (args->interface != NULL && args->fichier != NULL) {
        fprintf(stderr,
                "Vous ne pouvez pas choisir les options -i et -f à la fois\n");
        afficher_aide();
        exit(EXIT_FAILURE);
    }

    return 0;
}

void afficher_aide() {
    printf("Usage: analyseur\n"
           "-i <interface> : interface pour l'analyse live\n"
           "-o <fichier> : fichier d'entrée pour l'analyse offline\n"
           "-f <filtre> : filtre BPF(optionel)\n"
           "-v <1..3> : niveau de verbosité(1=très concis; 2=synthétique; "
           "3=complet)\n");
}