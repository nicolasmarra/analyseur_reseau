#include "arp.h"

void traiter_arp(const u_char *paquet, int verbosite) {
    struct arphdr *arp_header;
    arp_header = (struct arphdr *)(paquet);

    printf("\n");
    printf("ARP\n");

    if (verbosite > 2) {
        afficher_type_materiel(ntohs(arp_header->ar_hrd));
        afficher_type_protocole(ntohs(arp_header->ar_pro));
        printf("Longueur des adresses matérielles : %d\n", arp_header->ar_hln);
        printf("Longueur des adresses protocole : %d\n", arp_header->ar_pln);
        afficher_operation(ntohs(arp_header->ar_op));

    }

    if (verbosite > 1) {
    afficher_adresses(arp_header->ar_hln, arp_header->ar_pln, paquet + sizeof(struct arphdr));
    }

    
}


void afficher_type_materiel(int materiel) {

    printf("Type de matériel : ");
    switch (materiel) {

    case ARPHRD_ETHER:
        printf("Ethernet (%d)\n", materiel);
        break;
    case ARPHRD_EETHER:
        printf("Ethernet expérimental (%d)\n", materiel);
        break;
    case ARPHRD_IEEE802:
        printf("IEEE 802 (%d)\n", materiel);
        break;
    case ARPHRD_ARCNET:
        printf("ARCNET (%d)\n", materiel);
        break;
    case ARPHRD_APPLETLK:
        printf("APPLEtalk (%d)\n", materiel);
        break;
    case ARPHRD_NETROM:
        printf("NET/ROM pseudo (%d)\n", materiel);
        break;
    case ARPHRD_AX25:
        printf("AX.25 Level (%d)\n", materiel);
        break;
    case ARPHRD_EUI64:
        printf("EUI-64 (%d)\n", materiel);
        break;
    case ARPHRD_IEEE1394:
        printf("IEEE 1394 IPv4 (%d)\n", materiel);
        break;
    default:
        printf("Inconnu (%d)\n", materiel);
        break;
    }
}

void afficher_type_protocole(int protocole) {
    printf("Type de protocole : ");
    switch (protocole) {
    case ETH_P_IP:
        printf("IP (0x%04x)\n", protocole);
        break;
    case ETH_P_IPV6:
        printf("IPv6 (0x%04x)\n", protocole);
        break;
    case ETH_P_ARP:
        printf("ARP (0x%04x)\n", protocole);
        break;
    case ETH_P_RARP:
        printf("RARP (0x%04x)\n", protocole);
        break;
    default:
        printf("Inconnu (0x%04x)\n", protocole);
        break;
    }
}

void afficher_operation(int opcode) {
    printf("Opération : ");
    switch (opcode) {
    case ARPOP_REQUEST:
        printf("Requête (%d)\n", opcode);
        break;
    case ARPOP_REPLY:
        printf("Réponse (%d)\n", opcode);
        break;
    case ARPOP_RREQUEST:
        printf("Requête RARP (%d)\n", opcode);
        break;
    case ARPOP_RREPLY:
        printf("Réponse RARP (%d)\n", opcode);
        break;
    case ARPOP_InREQUEST:
        printf("Requête InARP (%d)\n", opcode);
        break;
    case ARPOP_InREPLY:
        printf("Réponse InARP (%d)\n", opcode);
        break;
    case ARPOP_NAK:
        printf("NAK InARP (%d)\n", opcode);
        break;
    default:
        printf("Inconnu (%d)\n", opcode);
        break;
    }
}

void afficher_adresses(int taille_mac, int taille_ip, const u_char *paquet)
{
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
        printf("%02x%s", paquet[i + taille_mac + taille_ip], (i < taille_mac - 1) ? ":" : "");
    }
    printf("\n");

    printf("Adresse IP destination : ");
    for (int i = 0; i < taille_ip; i++) {
        printf("%d%s", paquet[i + 2 * taille_mac + taille_ip], (i < taille_ip - 1) ? "." : "");
    }
    printf("\n");
}
