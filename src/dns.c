#include "dns.h"

void traiter_dns(const u_char *paquet, int taille, int verbosite) {

    (void)paquet;
    (void)taille;
    printf("\n");
    printf("DNS\n");

    struct dnshdr *dns_header;
    dns_header = (struct dnshdr *)(paquet);

    if (verbosite > 1) {

        printf("Transaction ID : 0x%.4x\n", ntohs(dns_header->id));
        printf("Flags : 0x%.4x\n", ntohs(dns_header->flags));

        printf("Questions : %d\n", ntohs(dns_header->questions));
        printf("Answer RRs : %d\n", ntohs(dns_header->answers));
        printf("Authority RRs : %d\n", ntohs(dns_header->authority));
        printf("Additional RRs : %d\n", ntohs(dns_header->additional));


        // Afficher les questions DNS
        afficher_requetes(paquet + sizeof(struct dnshdr), ntohs(dns_header->questions));

    }
}

void afficher_requetes(const u_char *requetes, int questions)
{
    printf("Queries: \n");

    for (int i = 0; i < questions; i++)
    {
        // Afficher le nom de la requête DNS
        while (*requetes != 0)
        {
            int taille = *requetes;
            requetes++;

            for (int j = 0; j < taille; j++)
            {
                printf("%c", *requetes);
                requetes++;
            }

            if (*requetes != 0)
                printf(".");
            
        }

        // Avancer le pointeur pour passer au champ QTYPE (Type)
        requetes += 1;

        // Afficher le type de la requête DNS
        uint16_t qtype = *(uint16_t *)requetes;
        afficher_type_dns(ntohs(qtype));

        // Avancer le pointeur pour passer au champ QCLASS (Class)
        requetes += 2;

        // Afficher la classe de la requête DNS
        uint16_t qclass = *(uint16_t *)requetes;
        afficher_class_dns(ntohs(qclass));
        
        // Avancer le pointeur pour passer à la prochaine requête
        requetes += 2;

        printf("\n");
    }
    
}

void afficher_type_dns(int type) {
    printf(" Type ");
    switch (type) {
        case 1:
            printf("A");
            break;
        case 2:
            printf("NS");
            break;
        case 3:
            printf("MD");
            break;
        case 4:
            printf("MF");
            break;
        case 5:
            printf("CNAME");
            break;
        case 6:
            printf("SOA");
            break;
        case 7:
            printf("MB");
            break;
        case 8:
            printf("MG");
            break;
        case 9:
            printf("MR");
            break;
        case 10:
            printf("NULL");
            break;
        case 11:
            printf("WKS");
            break;
        case 12:
            printf("PTR");
            break;
        case 15:
            printf("MX");
            break;
        case 16:
            printf("TXT");
            break;
        case 28:
            printf("AAAA");
            break;
        case 33:
            printf("SRV");
            break;
        case 41:
            printf("OPT");
            break;
        case 43:
            printf("DS");
            break;
        case 46:
            printf("RRSIG");
            break;
        case 47:
            printf("NSEC");
            break;
        case 48:
            printf("DNSKEY");
            break;
        case 50:
            printf("NSEC3");
            break;
        case 51:
            printf("NSEC3PARAM");
            break;
        case 52:
            printf("TLSA");
            break;
        case 59:
            printf("CAA");
            break;
        case 99:
            printf("SPF");
            break;
        case 250:
            printf("TSIG");
            break;
        case 251:
            printf("IXFR");
            break;
        case 252:
            printf("AXFR");
            break;
        case 255:
            printf("ANY");
            break;
        default:
            printf("Inconnu");
            break;
    }
}

void afficher_class_dns(int class)
{
    printf(", Class ");
    switch (class)
    {
    case 0:
        printf("Reserved");
        break;
    case 1:
        printf("IN");
        break;
    case 2:
        printf("CS");
        break;
    case 3:
        printf("CH");
        break;
    case 4:
        printf("HS");
        break;
    case 255:
        printf("ANY");
        break;
    default:
        printf("Inconnu");
        break;
    }
}