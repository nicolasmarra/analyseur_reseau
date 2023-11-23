#include "utiles.h"

void traiter_udp(const u_char *paquet, int verbosite) {
    struct udphdr *udp_header;
    udp_header = (struct udphdr *)(paquet);

    printf("\n");
    printf("UDP\n");

    if (verbosite > 1) {
        printf("Port source : %d\n", ntohs(udp_header->source));
        printf("Port destination : %d\n", ntohs(udp_header->dest));
        
    }
    if (verbosite > 2) {
        printf("Longueur : %d\n", ntohs(udp_header->len));
        printf("Somme de contrôle : 0x%.2x (%d)\n", ntohs(udp_header->check),
               ntohs(udp_header->check));
    }

    
}