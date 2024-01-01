#include "ip.h"

void traiter_ipv4(const u_char *paquet, int verbosite) {
    struct ip *ip_header = (struct ip *)(paquet);

    printf("\n");
    printf("IPV4\n");

    if (verbosite > 2) {
        printf("Version : %d\n", ip_header->ip_v);
        printf("Longueur de l'en-tête : %d bytes (%d)\n", ip_header->ip_hl * 4,
               ip_header->ip_hl);
        printf("Type de service : %d\n", ip_header->ip_tos);
        printf("Longueur totale : %d\n", ntohs(ip_header->ip_len));
        printf("Identification : 0x%.2x (%d)\n", ntohs(ip_header->ip_id),
               ntohs(ip_header->ip_id));
        printf("Flags : 0x%.2x\n", ntohs(ip_header->ip_off));
        printf("TTL : %d\n", ip_header->ip_ttl);
        printf("Protocole : ");
        afficher_type_protocole_IP(ip_header->ip_p);
        printf("Somme de contrôle : 0x%.2x (%d)\n", ntohs(ip_header->ip_sum),
               ntohs(ip_header->ip_sum));
    }

    if (verbosite > 1) {
        printf("Adresse IP source : %s\n", inet_ntoa(ip_header->ip_src));
        printf("Adresse IP destination : %s\n", inet_ntoa(ip_header->ip_dst));
    }

    int taille = ntohs(ip_header->ip_len) - (ip_header->ip_hl * 4);
    traiter_protocoles(paquet + (ip_header->ip_hl * 4),taille , verbosite,
                       ip_header->ip_p,VERSION_IPV4);
    
}

void afficher_type_protocole_IP(int protocole)
{
    switch (protocole)
    {
    case IPPROTO_ICMP:
        printf("ICMP (%d)\n", protocole);
        break;
    
    case IPPROTO_TCP:
        printf("TCP (%d)\n", protocole);
        break;
    
    case IPPROTO_UDP:
        printf("UDP (%d)\n", protocole);
        break;
    case IPPROTO_IPIP:
        printf("IP in IP (%d)\n", protocole);
        break;
    default:
        printf("(%d)\n", protocole);
        break;
    }
}

void traiter_ipv6(const u_char *paquet, int verbosite) {
    struct ip6_hdr *ip6_header = (struct ip6_hdr *)(paquet);

    printf("\n");
    printf("IPV6\n");

    char adresse_source[INET6_ADDRSTRLEN];
    char adresse_destination[INET6_ADDRSTRLEN];

    if (verbosite > 2) {
        printf("Version : %d\n", ip6_header->ip6_vfc >> 4);
        printf("Classe de trafic: 0x%.2x\n",
               (ntohl(ip6_header->ip6_flow) >> 20) & 0xFF);
        printf("Flow label: 0x%.5x\n", ntohl(ip6_header->ip6_flow) & 0xFFFFF);
        printf("Longueur de la Payload: %d\n", ntohs(ip6_header->ip6_plen));
        printf("Header suivant : ");
        afficher_type_protocole_IP(ip6_header->ip6_nxt);
        printf("Limite de saut : %d\n", ip6_header->ip6_hlim);
    }

    if (verbosite > 1) {
        inet_ntop(AF_INET6, &(ip6_header->ip6_src), adresse_source,
                  INET6_ADDRSTRLEN);
        inet_ntop(AF_INET6, &(ip6_header->ip6_dst), adresse_destination,
                  INET6_ADDRSTRLEN);
        printf("Adresse IP source : %s\n", adresse_source);
        printf("Adresse IP destination : %s\n", adresse_destination);
    }

    traiter_protocoles(paquet + sizeof(struct ip6_hdr), ntohs(ip6_header->ip6_plen), verbosite,
                       ip6_header->ip6_nxt, VERSION_IPV6);
 
}

void traiter_protocoles(const u_char *paquet, int taille, int verbosite, int protocole, int version)
{
    switch (protocole)
    {
    case IPPROTO_UDP:
        traiter_udp(paquet, taille, verbosite);
        break;
    case IPPROTO_TCP:
        traiter_tcp(paquet, taille, verbosite);
        break;
    case IPPROTO_ICMP:
        traiter_icmp(paquet, taille, verbosite);
        break;
    case IPPROTO_IPIP:
        if (version == VERSION_IPV4)
        traiter_ipv4(paquet, verbosite);
        else if(version == VERSION_IPV6)
        traiter_ipv6(paquet, verbosite);
        
        break;
    default:
        break;
    }
}