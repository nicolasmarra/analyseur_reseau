#include "arp.h"

void traiter_arp(const u_char *paquet, int verbosite) {
    struct arphdr *arp_header;
    arp_header = (struct arphdr *)(paquet);

    printf("\n");
    printf("ARP\n");

    if (verbosite == 2) {
        // Verbosité de niveau 2
        afficher_type_materiel(ntohs(arp_header->ar_hrd));
        printf(" - ");
        afficher_type_protocole(ntohs(arp_header->ar_pro));
        printf(" - ");
        afficher_operation(ntohs(arp_header->ar_op));
        printf("\n");

    } else if (verbosite == 3) {

        // Verbosité de niveau 3
        afficher_type_materiel(ntohs(arp_header->ar_hrd));
        printf("\n");
        afficher_type_protocole(ntohs(arp_header->ar_pro));
        printf("\n");
        printf("Longueur des adresses matérielles : %d\n", arp_header->ar_hln);
        printf("Longueur des adresses protocole : %d\n", arp_header->ar_pln);
        afficher_operation(ntohs(arp_header->ar_op));
        afficher_adresses(arp_header->ar_hln, arp_header->ar_pln,
                          paquet + sizeof(struct arphdr));
        
        printf("\n");
    }
}

void afficher_type_materiel(int materiel) {

    // Affichage du type de matériel
    printf("Type de matériel : ");
    switch (materiel) {

    case ARPHRD_ETHER:
        printf("Ethernet (%d)", materiel);
        break;
    case ARPHRD_EETHER:
        printf("Ethernet expérimental (%d)", materiel);
        break;
    case ARPHRD_IEEE802:
        printf("IEEE 802 (%d)", materiel);
        break;
    case ARPHRD_ARCNET:
        printf("ARCNET (%d)", materiel);
        break;
    case ARPHRD_APPLETLK:
        printf("APPLEtalk (%d)", materiel);
        break;
    case ARPHRD_NETROM:
        printf("NET/ROM pseudo (%d)", materiel);
        break;
    case ARPHRD_AX25:
        printf("AX.25 Level (%d)", materiel);
        break;
    case ARPHRD_EUI64:
        printf("EUI-64 (%d)", materiel);
        break;
    case ARPHRD_IEEE1394:
        printf("IEEE 1394 IPv4 (%d)", materiel);
        break;
    default:
        printf("Inconnu (%d)", materiel);
        break;
    }
}

void afficher_type_protocole(int protocole) {

    // Affichage du type de protocole
    printf("Type de protocole : ");
    switch (protocole) {
    case ETH_P_IP:
        printf("IPv4 (0x%04x)", protocole);
        break;
    case ETH_P_IPV6:
        printf("IPv6 (0x%04x)", protocole);
        break;
    case ETH_P_ARP:
        printf("ARP (0x%04x)", protocole);
        break;
    case ETH_P_RARP:
        printf("RARP (0x%04x)", protocole);
        break;
    default:
        printf("Inconnu (0x%04x)", protocole);
        break;
    }
}

void afficher_operation(int opcode) {
    printf("Opération : ");

    // Affichage du type d'opération
    switch (opcode) {
    case ARPOP_REQUEST:
        printf("Requête (%d)", opcode);
        break;
    case ARPOP_REPLY:
        printf("Réponse (%d)", opcode);
        break;
    case ARPOP_RREQUEST:
        printf("Requête RARP (%d)", opcode);
        break;
    case ARPOP_RREPLY:
        printf("Réponse RARP (%d)", opcode);
        break;
    case ARPOP_InREQUEST:
        printf("Requête InARP (%d)", opcode);
        break;
    case ARPOP_InREPLY:
        printf("Réponse InARP (%d)", opcode);
        break;
    case ARPOP_NAK:
        printf("NAK InARP (%d)", opcode);
        break;
    default:
        printf("Inconnu (%d)", opcode);
        break;
    }
}

void afficher_adresses(int taille_mac, int taille_ip, const u_char *paquet) {

    // Affichage des adresses
    printf("Adresse MAC source : ");
    for (int i = 0; i < taille_mac; i++) {
        printf("%02x%s", paquet[i], (i < taille_mac - 1) ? ":" : "");
    }
    printf("\n");

    printf("Adresse IP source : ");
    for (int i = 0; i < taille_ip; i++) {
        printf("%d%s", paquet[i + taille_mac], (i < taille_ip - 1) ? "." : "");
    }
    printf("\n");

    printf("Adresse MAC destination : ");
    for (int i = 0; i < taille_mac; i++) {
        printf("%02x%s", paquet[i + taille_mac + taille_ip],
               (i < taille_mac - 1) ? ":" : "");
    }
    printf("\n");

    printf("Adresse IP destination : ");
    for (int i = 0; i < taille_ip; i++) {
        printf("%d%s", paquet[i + 2 * taille_mac + taille_ip],
               (i < taille_ip - 1) ? "." : "");
    }
    printf("\n");
}
