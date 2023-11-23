#include "args.h"
#include "ip.h"
#include "net/ethernet.h"
#include "netinet/ether.h"
#include "netinet/if_ether.h"
#include "pcap.h"
#include "utiles.h"
#include <stdio.h>
#include <stdlib.h>

int nbr_paquet = 0;

void traiter_paquet(u_char *args, const struct pcap_pkthdr *header,
                    const u_char *paquet) {

    int verbosite = *(int *)args;
    struct ether_header *ethernet_header;
    ethernet_header = (struct ether_header *)paquet;

    const char *type =
        (ntohs(ethernet_header->ether_type) == ETHERTYPE_IP)     ? "IPv4"
        : (ntohs(ethernet_header->ether_type) == ETHERTYPE_IPV6) ? "IPv6"
                                                                 : "";
    printf("========================================\n");
    printf("Trame: %d\n", ++nbr_paquet);
    printf("ETHERNET\n");

    if (verbosite > 1) {

        printf("Adresse MAC destination : %02x:%02x:%02x:%02x:%02x:%02x\n",
               ethernet_header->ether_dhost[0], ethernet_header->ether_dhost[1],
               ethernet_header->ether_dhost[2], ethernet_header->ether_dhost[3],
               ethernet_header->ether_dhost[4],
               ethernet_header->ether_dhost[5]);

        printf("Adresse MAC source : %02x:%02x:%02x:%02x:%02x:%02x\n",
               ethernet_header->ether_shost[0], ethernet_header->ether_shost[1],
               ethernet_header->ether_shost[2], ethernet_header->ether_shost[3],
               ethernet_header->ether_shost[4],
               ethernet_header->ether_shost[5]);
    }
    if (verbosite > 2) {
        printf("Type: %s (0x%02x%02x)\n", type,
               (ntohs(ethernet_header->ether_type) & 0xFF00) >> 8,
               ntohs(ethernet_header->ether_type) & 0x00FF);
        printf("Longueur : %d\n", header->len);
    }

    switch (ntohs(ethernet_header->ether_type)) {
    case ETHERTYPE_IP:
        traiter_ipv4(paquet, verbosite);
        break;
    case ETHERTYPE_ARP:
        printf("ARP\n");
        break;
    case ETHERTYPE_REVARP:
        printf("RARP\n");
        break;
    case ETHERTYPE_IPV6:
        printf("IPV6\n");
        break;
    case ETHERTYPE_LOOPBACK:
        printf("LOOPBACK\n");
        break;
    case ETHERTYPE_VLAN:
        printf("VLAN\n");
        break;
    default:
        printf("Type Ethernet inconnu : %04x\n",
               ntohs(ethernet_header->ether_type));
        break;
    }
}

int main(int argc, char *argv[]) {
    args_t args;
    parse_args(argc, argv, &args);

    char erreur_buffer[PCAP_ERRBUF_SIZE];
    pcap_t *handle;

    // interface
    if (args.interface != NULL) {

        /*Ouverture d'une capture*/
        handle = pcap_open_live(args.interface, BUFSIZ, CONFUS, DELAI,
                                erreur_buffer);

        if (handle == NULL) {
            raler(1, "Impossible d'ouvrir l'interface %s : %s\n",
                  args.interface, erreur_buffer);
        }

        if (pcap_loop(handle, -1, traiter_paquet, (u_char *)&args.verbosite) !=
            0) {
            raler(1, "Impossible de capturer un paquet : %s\n",
                  pcap_geterr(handle));
        }

        // Fermer la session de capture
        pcap_close(handle);

    }
    // fichier
    else {
        /*Ouverture d'une capture*/
        handle = pcap_open_offline(args.fichier, erreur_buffer);

        if (handle == NULL) {
            raler(1, "Impossible d'ouvrir le fichier %s : %s\n", args.fichier,
                  erreur_buffer);
        }

        if (pcap_loop(handle, -1, traiter_paquet, (u_char *)&args.verbosite) !=
            0) {
            raler(1, "Impossible de capturer un paquet : %s\n",
                  pcap_geterr(handle));
        }

        // Fermer la session de capture
        pcap_close(handle);
    }

    return 0;
}
