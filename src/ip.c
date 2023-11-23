#include "ip.h"
#include <stdio.h>
#include <netdb.h>

void traiter_ipv4(const u_char *paquet, int verbosite) {
    (void)paquet;
    struct ip *ip_header;

    int taille = sizeof(struct ether_header);
    ip_header = (struct ip *)(paquet + taille);

    printf("\n");
    printf("IPV4\n");

    if (verbosite > 2) {
        printf("Version : %d\n", ip_header->ip_v);
        printf("Longueur de l'en-tête : %d bytes (%d)\n",ip_header->ip_hl*4, ip_header->ip_hl);
        printf("Type de service : %d\n", ip_header->ip_tos);
        printf("Longueur totale : %d\n", ntohs(ip_header->ip_len));
        printf("Identification : 0x%.2x (%d)\n",ntohs(ip_header->ip_id), ntohs(ip_header->ip_id));
        printf("Flags : 0x%.2x\n", ntohs(ip_header->ip_off));
        printf("TTL : %d\n", ip_header->ip_ttl);
        printf("Protocole : %s (%d)\n", getprotobynumber(ip_header->ip_p)->p_name, ip_header->ip_p);
        printf("Somme de contrôle : 0x%.2x (%d)\n",ntohs(ip_header->ip_sum), ntohs(ip_header->ip_sum));
    }

    if (verbosite > 1) {
        printf("Adresse IP source : %s\n", inet_ntoa(ip_header->ip_src));
        printf("Adresse IP destination : %s\n", inet_ntoa(ip_header->ip_dst));
    }

    switch (ip_header->ip_p) {
    case IPPROTO_UDP:
        printf("UDP\n");
        // traiter_udp(paquet, verbosite);
        break;
    case IPPROTO_TCP:
        printf("TCP\n");
        // traiter_tcp(paquet, verbosite);
        break;
    case IPPROTO_ICMP:
        printf("ICMP\n");
        // traiter_icmp(paquet, verbosite);
        break;
    default:
        break;
    }
}

/*
void traiter_ipv6(const u_char *paquet, int verbosite) {
    struct ip6_hdr *ip6_header;
    ip6_header = (struct ip6_hdr *)paquet;

    printf("\n");
    printf("IPV6\n");

    if (verbosite > 1) {
        printf("Adresse IP source : %s\n", inet_ntoa(ip6_header->ip6_src));
        printf("Adresse IP destination : %s\n", inet_ntoa(ip6_header->ip6_dst));
    }

    if (verbosite > 2) {
        printf("Version : %d\n", ip6_header->ip6_vfc);
        printf("Classe de trafic : %d\n", ip6_header->ip6_flow);
        printf("Etiquette de flux : %d\n", ip6_header->ip6_flow);
        printf("Longueur de la charge utile : %d\n",
               ntohs(ip6_header->ip6_plen));
        printf("Suivant en-tête : %d\n", ip6_header->ip6_nxt);
        printf("Limite de saut : %d\n", ip6_header->ip6_hlim);
    }

    switch (ip6_header->ip6_nxt) {
    case IPPROTO_UDP:
        printf("UDP\n");
        // traiter_udp(paquet, verbosite);
        break;
    case IPPROTO_TCP:
        printf("TCP\n");
        // traiter_tcp(paquet, verbosite);
        break;
    case IPPROTO_ICMP:
        printf("ICMP\n");
        // traiter_icmp(paquet, verbosite);
        break;
    default:
        break;
    }
}*/