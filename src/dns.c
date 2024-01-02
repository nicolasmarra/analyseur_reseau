#include "dns.h"

void traiter_dns(const u_char *paquet, int taille, int verbosite) {
    //struct dnshdr *dns_header;
    //dns_header = (struct dnshdr *)(paquet);

    (void) paquet;
    (void) taille;
    printf("\n");
    printf("DNS\n");

    if(verbosite > 1)
    {

    }


}