#include "bootp.h"

void traiter_bootp(const u_char *paquet, int taille, int verbosite) {

    printf("\n");

    (void)taille;

    struct bootp *bootp_header = (struct bootp *)paquet;
    if (bootp_header->bp_vend[0] == 0x63 && bootp_header->bp_vend[1] == 0x82 &&
        bootp_header->bp_vend[2] == 0x53 && bootp_header->bp_vend[3] == 0x63)
        printf("DHCP\n");
    else
        printf("BOOTP\n");

    if (verbosite > 1) {

        printf("Type de message: ");
        switch (bootp_header->bp_op) {
        case BOOTREQUEST:
            printf("Boot Request (%d)\n", bootp_header->bp_op);
            break;
        case BOOTREPLY:
            printf("Boot Reply (%d)\n", bootp_header->bp_op);
            break;
        default:
            printf("Inconnu (%d)\n", bootp_header->bp_op);
            break;
        }
    }

    if (verbosite > 2) {

        printf("Type de matériel: ");
        switch (bootp_header->bp_htype) {
        case HTYPE_ETHERNET:
            printf("Ethernet (%d)\n", bootp_header->bp_htype);
            break;
        default:
            printf("Inconnu (%d)\n", bootp_header->bp_htype);
            break;
        }

        printf("Longueur de l'adresse matérielle: %d\n", bootp_header->bp_hlen);

        printf("Nombre de sauts (Hops): %d\n", bootp_header->bp_hops);

        printf("Identifiant de transaction: 0x%.2x (%d)\n",
               ntohl(bootp_header->bp_xid), ntohl(bootp_header->bp_xid));

        printf("Secondes écoulées : %d\n", ntohs(bootp_header->bp_secs));

        printf("Bootp flags: 0x%.4x %s\n", ntohs(bootp_header->bp_flags),
               (ntohs(bootp_header->bp_flags) & 0x8000) ? "(Broadcast)"
                                                        : "(Unicast)");

        printf("Adresse IP client: %s\n", inet_ntoa(bootp_header->bp_ciaddr));

        printf("Mon adresse IP client: %s\n",
               inet_ntoa(bootp_header->bp_yiaddr));

        printf("Adresse IP serveur: %s\n", inet_ntoa(bootp_header->bp_siaddr));

        printf("Adresse IP passerelle: %s\n",
               inet_ntoa(bootp_header->bp_giaddr));

        printf("Adresse MAC client: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",
               bootp_header->bp_chaddr[0], bootp_header->bp_chaddr[1],
               bootp_header->bp_chaddr[2], bootp_header->bp_chaddr[3],
               bootp_header->bp_chaddr[4], bootp_header->bp_chaddr[5]);

        if (bootp_header->bp_sname[0] != '\0')
            printf("Nom du serveur: %s\n", bootp_header->bp_sname);
        else
            printf("Nom du serveur: Non renseigné\n");

        if (bootp_header->bp_file[0] != '\0')
            printf("Nom du fichier: %s\n", bootp_header->bp_file);
        else
            printf("Nom du fichier: Non renseigné\n");

        printf("Options: \n");
        // afficher_options_bootp(bootp_header->bp_vend, verbosite);
    }
}