#include "pop.h"

void traiter_pop(const u_char *paquet, int taille, int verbosite) {
    printf("\n");
    printf("POP\n");

    if (verbosite > 1) {
    }

    if (verbosite > 2) {
        for (int i = 0; i < taille; i++) {
            printf("%c", paquet[i]);
        }

        printf("\n");
    }
}