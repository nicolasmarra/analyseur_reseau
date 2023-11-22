#include "analyseur-args.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void initialiser_args(args_t *args) {
    args->verbosite = 3;
    args->interface = NULL;
    args->fichier = NULL;
    args->filtre = NULL;
}

int parse_args(int argc, char *argv[], args_t *args) {
    initialiser_args(args);
    opterr = 0;

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
            break;
        case 'h':
            afficher_aide();
            return -1; 
        default:
            fprintf(stderr, "Option inconnu\n",
                    argv[0]);
            afficher_aide();
            return -1;
        }
    }
    
    if (args->interface == NULL || args->fichier == NULL) {
        fprintf(stderr, "\ttu dois choisir l'option -i ou l'option -f\n",
                argv[0]);
        afficher_aide();
        return -1;
    }else if(args->interface != NULL && args->fichier != NULL){
        fprintf(stderr, "\ttu ne peux pas choisir les deux options à la fois\n",
                argv[0]);
        afficher_aide();
        return -1;
    }   


    return 0;
}

void afficher_aide() {
    printf("\tUsage:\n");
    printf("\t  -i <interface> : interface pour l'analyse live\n");
    printf("\t  -o <fichier> : fichier d'entrée pour l'analyse offline\n");
    printf("\t  -f <filtre> : filtre BPF(optionel)\n");
    printf("\t  -v <1..3> : niveau de verbosité(1=très concis; 2=synthétique; "
           "3=complet)\n");
}