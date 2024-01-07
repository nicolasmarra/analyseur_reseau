#include "utiles.h"

void traiter_udp(const u_char *paquet, int taille, int verbosite) {
    struct udphdr *udp_header;
    udp_header = (struct udphdr *)(paquet);

    printf("\n");
    printf("UDP\n");

    // Verbosité de niveau 2
    if (verbosite == 2) {
        printf("Port source : %d - ", ntohs(udp_header->source));
        printf("Port destination : %d\n", ntohs(udp_header->dest));
    }
    // Verbosité de niveau 3
    else if (verbosite == 3) {
        printf("Port source : %d\n", ntohs(udp_header->source));
        printf("Port destination : %d\n", ntohs(udp_header->dest));
        
        printf("Longueur : %d\n", ntohs(udp_header->len));
        printf("Somme de contrôle : 0x%.2x (%d)\n", ntohs(udp_header->check),
               ntohs(udp_header->check));
    }

    // Traitement des ports
    traiter_port_udp(ntohs(udp_header->source), ntohs(udp_header->dest),
                     paquet + sizeof(struct udphdr),
                     taille - sizeof(struct udphdr), verbosite);
}

void traiter_port_udp(int port_source, int port_destination,
                      const u_char *paquet, int taille, int verbosite) {
    
    // BOOTP
    if (port_source == IPPORT_BOOTPC || port_destination == IPPORT_BOOTPC ||
        port_source == IPPORT_BOOTPS || port_destination == IPPORT_BOOTPS) {
        if (taille > 0)
            traiter_bootp(paquet, verbosite);
    }

    // DNS
    if(port_source == PORT_DNS || port_destination == PORT_DNS){
        if(taille > 0)
            traiter_dns(paquet, taille, verbosite);
    }

}