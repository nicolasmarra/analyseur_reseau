#include "icmp.h"

void traiter_icmp(const u_char *paquet, int verbosite) {
    
    struct icmphdr *icmp_header;
    icmp_header = (struct icmphdr *)(paquet);


    printf("\n");
    printf("ICMP\n");

    if (verbosite > 1) {

    }

    if (verbosite > 2) {
        afficher_type(icmp_header->type);
    }
}

void afficher_type(int type)
{
    printf("Type : ");
    switch (type)
    {
    case ICMP_ECHOREPLY:
        printf("Echo Reply (%d)\n", type);
        break;
    case ICMP_DEST_UNREACH:
        printf("Destination Unreachable (%d)\n", type);
        break;
    case ICMP_SOURCE_QUENCH:
        printf("Source Quench (%d)\n", type);
        break;
    case ICMP_REDIRECT:
        printf("Redirect (%d)\n", type);
        break;
    case ICMP_ECHO:
        printf("Echo (%d)\n", type);
        break;
    case ICMP_TIME_EXCEEDED:
        printf("Time Exceeded (%d)\n", type);
        break;
    case ICMP_PARAMETERPROB:
        printf("Parameter Problem (%d)\n", type);
        break;
    case ICMP_TIMESTAMP:
        printf("Timestamp (%d)\n", type);
        break;
    case ICMP_TIMESTAMPREPLY:
        printf("Timestamp Reply (%d)\n", type);
        break;
    case ICMP_INFO_REQUEST:
        printf("Information Request (%d)\n", type);
        break;
    case ICMP_INFO_REPLY:
        printf("Information Reply (%d)\n", type);
        break;
    case ICMP_ADDRESS:
        printf("Address Mask Request (%d)\n", type);
        break;
    case ICMP_ADDRESSREPLY:
        printf("Address Mask Reply (%d)\n", type);
        break;
    default:
        printf("Inconnu (%d)\n", type);
        break;
    }
}