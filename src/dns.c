#include "dns.h"

void traiter_dns(const u_char *paquet, int taille, int verbosite) {

    (void)taille;
    printf("\n");
    printf("DNS\n");

    struct dnshdr *dns_header;
    dns_header = (struct dnshdr *)(paquet);

    if (verbosite > 1) {
         if ((ntohs(dns_header->flags) & 0x8000) == 0) 
            printf("Type : Requête\n");
         else 
            printf("Type : Réponse\n");
        
        printf("Transaction ID : 0x%.4x\n", ntohs(dns_header->id));
        printf("Flags : 0x%.4x\n", ntohs(dns_header->flags));

        printf("Questions : %d\n", ntohs(dns_header->questions));
        printf("Answer RRs : %d\n", ntohs(dns_header->answers));
        printf("Authority RRs : %d\n", ntohs(dns_header->authority));
        printf("Additional RRs : %d\n", ntohs(dns_header->additional));
    }

    if (verbosite > 2) {

        const u_char *requetes = paquet + sizeof(struct dnshdr);

        // Affichage dess questions DNS
        printf("\n");
        int position =
            afficher_questions_dns(requetes, ntohs(dns_header->questions), 0);



        // Affichage des réponses DNS
        position += sizeof(struct dnshdr);
        // en raison de la compression de nom, qui est utilisée pour réduire la taille des paquets DNS, dans les réponses, les serveurs de noms et les informations supplémentaires
        //il faut donc passer le paquet complet aux fonctions suivantes
        position = afficher_info_dns(paquet, ntohs(dns_header->answers),
                                     position, ANSWER);

        // Affichage des serveurs DNS
        position = afficher_info_dns(paquet, ntohs(dns_header->authority),
                                     position, NAME_SERVER);

        // Affichage dess informations supplémentaires DNS
        position = afficher_info_dns(paquet, ntohs(dns_header->additional),
                                     position, ADITIONNAL_INFO);
    }
}

int afficher_questions_dns(const u_char *requetes, int nb_questions,
                           int position) {
    if (nb_questions > 0) {

        printf("Requêtes DNS : \n");
        for (int i = 0; i < nb_questions; i++) {

            printf("- ");
            position = afficher_nom_dns(requetes, position);
            position += 1;

            // On récupère le type de la question
            printf(" Type ");
            uint16_t type = *(uint16_t *)(requetes + position);
            afficher_type_dns(ntohs(type));
            position += 2;

            // On récupère la classe de la question
            printf(", Class ");
            uint16_t classe = *(uint16_t *)(requetes + position);
            afficher_class_dns(ntohs(classe));
            position += 2;

            printf("\n");
        }
    }
    return position;
}

int afficher_nom_dns(const u_char *nom, int position) {

    while (nom[position] != 0) {
        if (nom[position] == 0xC0) {
            afficher_nom_dns(nom, nom[position + 1]);
            return position + 1;
        }

        int taille = nom[position];
        for (int i = 0; i < taille; i++) {
            printf("%c", nom[position + i + 1]);
        }

        if (nom[position + taille + 1] != 0) {
            printf(".");
        }

        position += taille + 1;
    }

    return position;
}

void afficher_type_reponse(int type) {
    switch (type) {
    case ANSWER:
        printf("Réponses DNS : \n");
        break;
    case NAME_SERVER:
        printf("Serveurs de noms : \n");
        break;
    case ADITIONNAL_INFO:
        printf("Informations supplémentaires : \n");
        break;
    default:
        break;
    }
}

void afficher_nombre_type_reponse(int type, int n) {
    switch (type) {
    case ANSWER:
        printf("Réponse DNS : %d\n", n);
        break;
    case NAME_SERVER:
        printf("Serveur de nom : %d\n", n);
        break;
    case ADITIONNAL_INFO:
        printf("Information supplémentaire : %d\n", n);
        break;
    default:
        break;
    }
}

int afficher_info_dns(const u_char *requetes, int nb_info, int position,
                      int type) {
    if (nb_info > 0) {

        printf("\n");
        afficher_type_reponse(type);

        for (int i = 0; i < nb_info; i++) {
            afficher_nombre_type_reponse(type, i + 1);
            printf("Name : ");

            position = afficher_nom_dns(requetes, position);
            printf("\n");
            position += 1;

            // On récupère le type de la réponse
            uint16_t type = *(uint16_t *)(requetes + position);
            printf("Type : ");
            afficher_type_dns(ntohs(type));
            printf(" (%d) \n", ntohs(type));
            position += 2;

            // On récupère la classe de la réponse
            uint16_t classe = *(uint16_t *)(requetes + position);
            printf("Class : ");
            afficher_class_dns(ntohs(classe));
            printf("\n");
            position += 2;

            // On récupère le TTL de la réponse
            uint32_t ttl = *(uint32_t *)(requetes + position);
            printf("Time to Live : %d \n", ntohl(ttl));
            position += 4;

            uint16_t longueur = *(uint16_t *)(requetes + position);
            printf("Longueur : %d\n", ntohs(longueur));
            position += 2;

            int nouvelle_position = position;
            switch (ntohs(type)) {

            case 1:
                printf("Address : ");
                for (int i = 0; i < ntohs(longueur); i++) {
                    printf("%d", requetes[position + i]);
                    if (i < ntohs(longueur) - 1)
                        printf(".");
                }
                printf("\n");
                break;
            case 2:
                printf("Name Server : ");
                afficher_nom_dns(requetes, nouvelle_position);
                printf("\n");
                break;
            case 5:
                printf("CNAME : ");
                afficher_nom_dns(requetes, nouvelle_position);
                printf("\n");
                break;
            case 6:
                printf("Primary Name Server : ");
                nouvelle_position =
                    afficher_nom_dns(requetes, nouvelle_position);
                nouvelle_position += 1;
                printf("\n");

                printf("Responsible Authority's Mailbox : ");
                nouvelle_position =
                    afficher_nom_dns(requetes, nouvelle_position);
                nouvelle_position += 1;
                printf("\n");

                printf("Serial Number : ");
                printf("%d",
                       ntohl(*(uint32_t *)(requetes + nouvelle_position)));
                nouvelle_position += 4;
                printf("\n");

                printf("Refresh Interval : ");
                printf("%d",
                       ntohl(*(uint32_t *)(requetes + nouvelle_position)));
                nouvelle_position += 4;
                printf("\n");

                printf("Retry Interval : ");
                printf("%d",
                       ntohl(*(uint32_t *)(requetes + nouvelle_position)));
                nouvelle_position += 4;
                printf("\n");

                printf("Expire Limit : ");
                printf("%d",
                       ntohl(*(uint32_t *)(requetes + nouvelle_position)));
                nouvelle_position += 4;
                printf("\n");

                printf("Minimum TTL : ");
                printf("%d",
                       ntohl(*(uint32_t *)(requetes + nouvelle_position)));
                nouvelle_position += 4;
                printf("\n");

                break;
            case 12:
                printf("Domain Name : ");
                afficher_nom_dns(requetes, nouvelle_position);
                printf("\n");
                break;
            case 15:
                printf("Preference: %d\n",
                       ntohs(*(uint16_t *)(requetes + nouvelle_position)));
                nouvelle_position += 2;
                printf("MAIL EXCHANGE: ");
                afficher_nom_dns(requetes, nouvelle_position);
                printf("\n");
                break;
            case 16:
                printf("TXT : ");
                afficher_nom_dns(requetes, nouvelle_position);
                printf("\n");
                break;
            case 28:
                printf("AAAA Address: ");
                for (int i = 0; i < ntohs(longueur); i++) {
                    printf("%x", requetes[nouvelle_position + i]);
                    if (i < ntohs(longueur) - 1) {
                        printf(":");
                    }
                }
                printf("\n");
                break;
            case 33:
                printf("SRV : ");
                printf("%d",
                       ntohs(*(uint16_t *)(requetes + nouvelle_position)));
                nouvelle_position += 2;
                printf(", ");
                printf("%d",
                       ntohs(*(uint16_t *)(requetes + nouvelle_position)));
                nouvelle_position += 2;
                printf(", ");
                printf("%d",
                       ntohs(*(uint16_t *)(requetes + nouvelle_position)));
                nouvelle_position += 2;
                printf(", ");
                afficher_nom_dns(requetes, nouvelle_position);
                printf("\n");
                break;
            case 41:
                printf("OPT : ");
                printf("\n");
                break;
            case 43:
                printf("DS : ");
                printf("%d",
                       ntohs(*(uint16_t *)(requetes + nouvelle_position)));
                nouvelle_position += 2;
                printf(", ");
                printf("%d",
                       ntohs(*(uint16_t *)(requetes + nouvelle_position)));
                nouvelle_position += 2;
                printf(", ");
                printf("%d",
                       ntohs(*(uint16_t *)(requetes + nouvelle_position)));
                nouvelle_position += 2;
                printf(", ");
                nouvelle_position =
                    afficher_nom_dns(requetes, nouvelle_position);
                printf("\n");
                break;
            case 46:
                printf("RRSIG : ");
                printf("%d",
                       ntohs(*(uint16_t *)(requetes + nouvelle_position)));
                nouvelle_position += 2;
                printf(", ");
                printf("%d",
                       ntohs(*(uint16_t *)(requetes + nouvelle_position)));
                nouvelle_position += 2;
                printf(", ");
                printf("%d",
                       ntohl(*(uint32_t *)(requetes + nouvelle_position)));
                nouvelle_position += 4;
                printf(", ");
                printf("%d",
                       ntohl(*(uint32_t *)(requetes + nouvelle_position)));
                nouvelle_position += 4;
                printf(", ");
                printf("%d",
                       ntohl(*(uint32_t *)(requetes + nouvelle_position)));
                nouvelle_position += 4;
                printf(", ");
                printf("%d",
                       ntohs(*(uint16_t *)(requetes + nouvelle_position)));
                nouvelle_position += 2;
                printf(", ");
                nouvelle_position =
                    afficher_nom_dns(requetes, nouvelle_position);
                printf("\n");
                break;
            case 47:
                printf("NSEC : ");
                position = afficher_nom_dns(requetes, nouvelle_position);
                printf("\n");
                break;
            case 48:
                printf("DNSKEY : ");
                printf("%d",
                       ntohs(*(uint16_t *)(requetes + nouvelle_position)));
                nouvelle_position += 2;
                printf(", ");
                printf("%d",
                       ntohs(*(uint16_t *)(requetes + nouvelle_position)));
                nouvelle_position += 2;
                printf(", ");
                printf("%d",
                       ntohs(*(uint16_t *)(requetes + nouvelle_position)));
                nouvelle_position += 2;
                printf(", ");
                afficher_nom_dns(requetes, nouvelle_position);
                printf("\n");
                break;
            default:
                printf("Inconnu");

                break;
            }
            printf("\n");

            position += ntohs(longueur);
        }
    }
    return position;
}

void afficher_type_dns(int type) {
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

void afficher_class_dns(int class) {
    switch (class) {
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