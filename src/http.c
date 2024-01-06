#include "http.h"

void traiter_http(const u_char *paquet, int taille, int verbosite) {
    printf("\n");
    printf("HTTP\n");

    if (verbosite > 1) {
    }

    if (verbosite > 2) {


        for (int i = 0; i < taille; i++) {
            if(isprint(paquet[i]))
            printf("%c", paquet[i]);
        }

        printf("\n");
    }
}

