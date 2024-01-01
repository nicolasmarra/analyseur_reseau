#include "icmp.h"

void traiter_icmp(const u_char *paquet, int taille, int verbosite) {
    
    if(taille > 0)
    {
        
    struct icmphdr *icmp_header;
    icmp_header = (struct icmphdr *)(paquet);


    printf("\n");
    printf("ICMP\n");

    if (verbosite > 1) {
        
    }

    if (verbosite > 2) {
        afficher_type(icmp_header->type);
        printf("Code : %d\n", icmp_header->code);
        printf("Somme de contrôle : 0x%.2x\n", ntohs(icmp_header->checksum));
        printf("Identifiant : %d (0x%.2x)\n", ntohs(icmp_header->un.echo.id), ntohs(icmp_header->un.echo.id));
        printf("Numéro de séquence : %d (0x%.2x)\n", ntohs(icmp_header->un.echo.sequence), ntohs(icmp_header->un.echo.sequence));
    }

    }
}

void afficher_type(int type)
{
    printf("Type : ");
    switch (type)
    {
    case ICMP_ECHOREPLY:
        printf("%d (Echo reply) \n", type);
        break;
    case ICMP_DEST_UNREACH:
        printf("%d (Destination unreachable)\n", type);
        break;
    case ICMP_SOURCE_QUENCH:
        printf("%d (Source quench)\n", type);
        break;
    case ICMP_REDIRECT:
        printf("%d (Redirect)\n", type);
        break;
    case ICMP_ECHO:
        printf("%d (Echo request)\n", type);
        break;
    case ICMP_ROUTERADVERT:
        printf("%d (Router advertisement)\n", type);
        break;
    case ICMP_ROUTERSOLICIT:
        printf("%d (Router solicitation)\n", type);
        break;
    case ICMP_TIME_EXCEEDED:
        printf("%d (Time exceeded)\n", type);
        break;
    case ICMP_PARAMETERPROB:
        printf("%d (Parameter problem)\n", type);
        break;
    case ICMP_TIMESTAMP:
        printf("%d (Timestamp request)\n", type);
        break;
    case ICMP_TIMESTAMPREPLY:
        printf("%d (Timestamp reply)\n", type);
        break;
    case ICMP_INFO_REQUEST:
        printf("%d (Information request)\n", type);
        break;
    case ICMP_INFO_REPLY:
        printf("%d (Information reply)\n", type);
        break;
    case ICMP_ADDRESS:
        printf("%d (Address mask request)\n", type);
        break;
    case ICMP_ADDRESSREPLY:
        printf("%d (Address mask reply)\n", type);
        break;
    default:
        printf("%d\n", type);
        break;
    }
}