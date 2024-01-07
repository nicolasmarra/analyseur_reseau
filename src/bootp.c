#include "bootp.h"

void traiter_bootp(const u_char *paquet, int verbosite) {

    printf("\n");
    printf("BOOTP\n");

    struct bootp *bootp_header = (struct bootp *)paquet;

    // Verbosité de niveau 2
    if (verbosite == 2) {

        afficher_type_message_bootp(bootp_header->bp_op);
        printf(" - ");

        printf("Type de matériel: ");
        if (bootp_header->bp_htype == 1)
            printf("Ethernet (%d)\n", bootp_header->bp_htype);
        else
            printf("(%d)\n", bootp_header->bp_htype);

    }
    // Verbosité de niveau 3
    else if (verbosite == 3) {

        afficher_type_message_bootp(bootp_header->bp_op);
        printf("\n");

        printf("Type de matériel: ");
        if (bootp_header->bp_htype == 1)
            printf("Ethernet (%d)\n", bootp_header->bp_htype);
        else
            printf("(%d)\n", bootp_header->bp_htype);

        printf("Longueur de l'adresse matérielle: %d\n", bootp_header->bp_hlen);

        printf("Nombre de sauts (Hops): %d\n", bootp_header->bp_hops);

        printf("Identifiant de transaction: 0x%.2x \n",
               ntohl(bootp_header->bp_xid));

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

        if (bootp_header->bp_sname[0])
            printf("Nom du serveur: %s\n", bootp_header->bp_sname);
        else
            printf("Nom du serveur: Non renseigné\n");

        if (bootp_header->bp_file[0])
            printf("Nom du fichier: %s\n", bootp_header->bp_file);
        else
            printf("Nom du fichier: Non renseigné\n");

        if (bootp_header->bp_vend[0] == 99 && bootp_header->bp_vend[1] == 130 &&
            bootp_header->bp_vend[2] == 83 && bootp_header->bp_vend[3] == 99) {
            
            // Magic cookie correspond à DHCP, alors il y a des options DHCP
            printf("Magic Cookie : DHCP\n");
            
            afficher_options_bootp(bootp_header->bp_vend);
        } else {

            printf("Magic cookie: %.2x%.2x%.2x%.2x\n", bootp_header->bp_vend[0],
                   bootp_header->bp_vend[1], bootp_header->bp_vend[2],
                   bootp_header->bp_vend[3]);
            printf("Options: non présentes!\n");
        }
    }
}

void afficher_type_message_bootp(uint8_t type) {
    printf("Type de message: ");
    switch (type) {
    case BOOTREQUEST:
        printf("Boot Request (%d)", type);
        break;
    case BOOTREPLY:
        printf("Boot Reply (%d)", type);
        break;
    default:
        printf("(%d)", type);
        break;
    }
}

void afficher_options_bootp(uint8_t *vendor_specific) {
    printf("\n");
    printf("Options DHCP:\n");

    uint8_t *options = vendor_specific + 4;
    int i = 0;
    while (options[i] != TAG_END) {
        int temps = 0;

        switch (options[i]) {

        case TAG_PAD:
            //La longueur de cette option est toujours 0
            printf("PAD\n");
            i++;
            break;
        case TAG_SUBNET_MASK:
            //La longueur de cette option est toujours 4
            if(options[i+1] == 4){
                printf("Subnet mask: %d.%d.%d.%d\n", options[i + 2], options[i + 3],
                   options[i + 4], options[i + 5]);
            }
            else{
                printf("Error/Protocol : option length is not 4\n");
            }
            i += options[i + 1] + 2;
            break;
        case TAG_TIME_OFFSET:
            // La longueur de cette option est toujours 4
            if(options[i+1] == 4){
            temps = options[i + 2] * 256 * 256 * 256 +
                    options[i + 3] * 256 * 256 + options[i + 4] * 256 +
                    options[i + 5];
            afficher_temps("Time offset", temps);
            }
            else{
                printf("Error/Protocol : option length is not 4\n");
            }
            i += options[i + 1] + 2;
            break;
        case TAG_GATEWAY:

            // La longueur de cette option est toujours est de 4 ou un multiple de 4
            afficher_adresse_bootp("Gateway", i, options);
            i += options[i + 1] + 2;
            break;
        case TAG_TIME_SERVER:
            // La longueur de cette option est toujours est de 4 ou un multiple de 4
            afficher_adresse_bootp("Time server", i, options);
            i += options[i + 1] + 2;
            break;
        case TAG_NAME_SERVER:
            // La longueur de cette option est toujours est de 4 ou un multiple de 4
            afficher_adresse_bootp("Name server", i, options);
            i += options[i + 1] + 2;
            break;
        case TAG_DOMAIN_SERVER:
            // La longueur de cette option est toujours est de 4 ou un multiple de 4
            afficher_adresse_bootp("Domain name server", i, options);
            i += options[i + 1] + 2;
            break;
        case TAG_LOG_SERVER:
            // La longueur de cette option est toujours est de 4 ou un multiple de 4
            afficher_adresse_bootp("Log server", i, options);
            i += options[i + 1] + 2;
            break;
        case TAG_COOKIE_SERVER:
            // La longueur de cette option est toujours est de 4 ou un multiple de 4
            afficher_adresse_bootp("Cookie server", i, options);
            i += options[i + 1] + 2;
            break;
        case TAG_LPR_SERVER:
            // La longueur de cette option est toujours est de 4 ou un multiple de 4
            afficher_adresse_bootp("LPR server", i, options);
            i += options[i + 1] + 2;
            break;
        case TAG_IMPRESS_SERVER:
            // La longueur de cette option est toujours est de 4 ou un multiple de 4
            afficher_adresse_bootp("Impress server", i, options);
            i += options[i + 1] + 2;
            break;
        case TAG_RLP_SERVER:
            // La longueur de cette option est toujours est de 4 ou un multiple de 4
            afficher_adresse_bootp("RLP server", i, options);
            i += options[i + 1] + 2;
            break;
        case TAG_HOSTNAME:
            // La longueur de cette option est toujours est de N
            printf("Hostname: ");
            afficher_info(options + i + 2, options[i + 1], 1);
            i += options[i + 1] + 2;
            break;
        case TAG_BOOTSIZE:
            // La longueur de cette option est toujours est de 2
            printf("Boot File Size : ");
            if(options[i+1] == 2)
            {
            printf("%d\n", options[i + 2] * 256 + options[i + 3]);    
            }
            i += options[i + 1] + 2;
            break;
        case TAG_DUMPPATH:
            printf("Dump path: ");
            afficher_info(options + i + 2, options[i + 1], 1);
            i += options[i + 1] + 2;
            break;
        case TAG_DOMAINNAME:
            printf("Domain name: ");
            afficher_info(options + i + 2, options[i + 1], 1);
            i += options[i + 1] + 2;
            break;
        case TAG_SWAP_SERVER:
            printf("Swap server : ");
            afficher_info(options + i + 2, options[i + 1], 1);
            i += options[i + 1] + 2;
            break;
        case TAG_ROOTPATH:
            printf("Root path: ");
            afficher_info(options + i + 2, options[i + 1], 1);
            i += options[i + 1] + 2;
            break;
        case TAG_EXTPATH:
            printf("Extensions path: ");
            afficher_info(options + i + 2, options[i + 1], 1);
            i += options[i + 1] + 2;
            break;
        case TAG_IP_FORWARD:
            printf("IP Forwarding: ");
            switch (options[i + 2]) {
            case 0:
                printf("Off (%d)\n", options[i + 2]);
                break;
            case 1:
                printf("On (%d)\n", options[i + 2]);
                break;
            default:
                printf("(%d)\n", options[i + 2]);
                break;
            }
            i += options[i + 1] + 2;
            break;
        case TAG_NL_SRCRT:
            printf("Non-Local Source Routing: ");
            switch (options[i + 2]) {
            case 0:
                printf("Off (%d)\n", options[i + 2]);
                break;
            case 1:
                printf("On (%d)\n", options[i + 2]);
                break;
            default:
                printf("(%d)\n", options[i + 2]);
                break;
            }
            i += options[i + 1] + 2;
            break;
        case TAG_PFILTERS:
            printf("Policy Filter: ");
            afficher_info(options + i + 2, options[i + 1], 1);
            i += options[i + 1] + 2;
            break;
        case TAG_REASS_SIZE:
            printf("Max DG Reassembly Size: %d\n",
                   options[i + 2] * 256 + options[i + 3]);
            i += options[i + 1] + 2;
            break;
        case TAG_DEF_TTL:
            printf("Default IP TTL: %d\n", options[i + 2]);
            i += options[i + 1] + 2;
            break;
        case TAG_MTU_TIMEOUT:
             if(options[i+1] == 4){
            temps = options[i + 2] * 256 * 256 * 256 +
                    options[i + 3] * 256 * 256 + options[i + 4] * 256 +
                    options[i + 5];
            printf("Path MTU Aging Timeout: %d(s)\n", temps);
            }
            else{
                printf("Error/Protocol : option length is not 4\n");
            }
            
            i += options[i + 1] + 2;
            break;
        case TAG_REQUESTED_IP:
            printf("Requested IP address: %d.%d.%d.%d\n", options[i + 2],
                   options[i + 3], options[i + 4], options[i + 5]);
            i += options[i + 1] + 2;
            break;
        case TAG_IP_LEASE:
            temps = options[i + 2] * 256 * 256 * 256 +
                    options[i + 3] * 256 * 256 + options[i + 4] * 256 +
                    options[i + 5];
            afficher_temps("IP lease time", temps);
            i += options[i + 1] + 2;
            break;
        case TAG_OPT_OVERLOAD:
            printf("Option overload: ");
            switch (options[i + 2]) {
            case 1:
                printf("Boot File (%d)\n", options[i + 2]);
                break;
            case 2:
                printf("Server host names (%d)\n", options[i + 2]);
                break;
            case 3:
                printf("Boot file and server host names (%d)\n",
                       options[i + 2]);
                break;
            default:
                printf("(%d)\n", options[i + 2]);
                break;
            }
            i += options[i + 1] + 2;
            break;
        case TAG_DHCP_MESSAGE:
            printf("DHCP message type: ");
            afficher_message_dhcp(options[i + 2]);
            i += options[i + 1] + 2;
            break;
        case TAG_SERVER_ID:
            printf("Server identifier: %d.%d.%d.%d\n", options[i + 2],
                   options[i + 3], options[i + 4], options[i + 5]);
            i += options[i + 1] + 2;
            break;
        case TAG_PARM_REQUEST:
            printf("Parameter request list: \n");
            int item = 0;
            while (item != options[i + 1]) {
                printf("Param Request List Item : (%d) ",
                       options[i + 2 + item]);

                afficher_liste_parametres(options[i + 2 + item]);
                item++;
            }
            printf("\n");
            i += options[i + 1] + 2;
            break;
        case TAG_MAX_MSG_SIZE:
            printf("Maximum DHCP message size: %d\n",
                   options[i + 2] * 256 + options[i + 3]);
            i += options[i + 1] + 2;
            break;
        case TAG_RENEWAL_TIME:
            temps = options[i + 2] * 256 * 256 * 256 +
                    options[i + 3] * 256 * 256 + options[i + 4] * 256 +
                    options[i + 5];

            afficher_temps("Renewal time", temps);
            i += options[i + 1] + 2;
            break;
        case TAG_REBIND_TIME:
            temps = options[i + 2] * 256 * 256 * 256 +
                    options[i + 3] * 256 * 256 + options[i + 4] * 256 +
                    options[i + 5];

            afficher_temps("Rebinding time", temps);
            i += options[i + 1] + 2;
            break;
        case TAG_VENDOR_CLASS:
            printf("Vendor class identifier: ");
            afficher_info(options + i + 2, options[i + 1], 1);
            i += options[i + 1] + 2;
            break;
        case TAG_CLIENT_ID:
            printf("Client identifier: ");
            // on vérifie si ce champ contient une option supplémentaire pour le
            // type de matériel du client

            if (options[i + 1] == 7) {
                printf("\n");
                if (options[i + 2] == 1)
                    printf("Type de matériel : Ethernet (%d)\n",
                           options[i + 2]);
                else
                    printf("Type de matériel : (%d)\n", options[i + 2]);

                printf("Adresse MAC client: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",
                       options[i + 3], options[i + 4], options[i + 5],
                       options[i + 6], options[i + 7], options[i + 8]);

            } else {
                afficher_info(options + i + 2, options[i + 1], 1);
            }

            i += options[i + 1] + 2;
            break;
        case TAG_TFTP_SERVER:
            printf("TFTP server name: ");
            afficher_info(options + i + 2, options[i + 1], 1);
            i += options[i + 1] + 2;
            break;
        case TAG_AGENT_CIRCUIT:
            printf("Agent Information Option: \n");
            switch (options[i + 2]) {
            case 1:
                printf("Circuit ID (%d) : ", options[i + 2]);
                afficher_info(options + i + 4, options[i + 3], 2);
                break;
            case 2:
                printf("Remote ID (%d) : ", options[i + 2]);
                afficher_info(options + i + 4, options[i + 3], 2);

                break;
            default:
                printf("(%d)\n", options[i + 2]);
                break;
            }
            printf("\n");
            i += options[i + 1] + 2;
            break;
        case TAG_AUTH:
            printf("Authentication: ");
            printf("Protocole : ");
            switch (options[i + 2]) {
            case 1:
                printf("Delayed Authentication (%d)\n", options[i + 2]);
                break;
            case 2:
                printf("Reconfigure Key (%d)\n", options[i + 2]);
                break;
            case 3:
                printf("HMAC-MD5 (%d)\n", options[i + 2]);
                break;
            case 4:
                printf("HMAC-SHA1 (%d)\n", options[i + 2]);
                break;
            default:
                printf("(%d)\n", options[i + 2]);
                break;
            }
            printf("Algorithme : ");
            switch (options[i + 3]) {
            case 1:
                printf("HMAC-MD5 (%d)\n", options[i + 3]);
                break;
            case 2:
                printf("HMAC-SHA1 (%d)\n", options[i + 3]);
                break;
            default:
                printf("(%d)\n", options[i + 3]);
                break;
            }
            printf("Replay Detection Method: ");
            switch (options[i + 4]) {
            case 0:
                printf("Monotonically-increasing Counter (%d)\n",
                       options[i + 4]);
                break;
            case 1:
                printf("Replay detection (%d)\n", options[i + 4]);
                break;
            case 2:
                printf("Replay detection and broadcast-multicast (%d)\n",
                       options[i + 4]);
                break;
            default:
                printf("(%d)\n", options[i + 4]);
                break;
            }

            printf("RMD Replay Detection Value: 0x");
            // ce champ fait 8 octets et est affiché en hexa
            afficher_info(options + i + 5, 8, 2);

            printf("Secret ID: 0x");
            // ce champ fait 4 octets et est affiché en hexa
            afficher_info(options + i + 13, 4, 2);

            printf("HMAC MD5 Hash: ");
            // ce champ fait 16 octets et est affiché en hexa
            afficher_info(options + i + 17, 16, 2);
            printf("\n");

            i += options[i + 1] + 2;
            break;
        case TAG_CLIENT_LAST_TRANSACTION_TIME:
            temps = options[i + 2] * 256 * 256 * 256 +
                    options[i + 3] * 256 * 256 + options[i + 4] * 256 +
                    options[i + 5];

            afficher_temps("Client Last Transaction Time", temps);
            i += options[i + 1] + 2;
            break;
        case TAG_SIP_SERVERS:

            printf("SIP Servers:\n");
            printf("SIP encoding: ");
            switch (options[i + 2]) {
            case 1:
                printf("IPv4 (%d)\n", options[i + 2]);
                break;
            case 2:
                printf("IPv6 (%d)\n", options[i + 2]);
                break;
            default:
                printf("(%d)\n", options[i + 2]);
                break;
            }
            printf("SIP servers address: %d.%d.%d.%d\n", options[i + 3],
                   options[i + 4], options[i + 5], options[i + 6]);

            printf("\n");
            i += options[i + 1] + 2;
            break;


        case TAG_TFTP_SERVER_ADDRESS:

            afficher_adresse_bootp("TFTP server address", i, options);

            i += options[i + 1] + 2;
            break;
        default:
            printf("Option non reconnue (%d) -  Taille : %d\n", options[i],
                   options[i + 1]);
            i += options[i + 1] + 2;
            break;
        }
    }

    printf("End\n");
}

void afficher_adresse_bootp(char *description, int position, uint8_t *options) {

    int taille = 0;
    while (taille != options[position + 1]) {

        if (options[position + 1] - taille >= 4 ||
            options[position + 1] - taille % 4 == 0) {
            printf(
                "%s: %d.%d.%d.%d\n",description,
                options[position + 2 + taille], options[position + 3 + taille],
                options[position + 4 + taille], options[position + 5 + taille]);
        } else {
            printf("Error/Protocol : option length is not a multiple "
                   "of 4\n");
            break;
        }
        taille += 4;
    }

    printf("\n");
}

void afficher_temps(char *description, int temps) {
    if (temps >= 3600)
        printf("%s: (%ds) %d hour(s)...\n", description, temps, temps / 3600);
    else if (temps >= 60)
        printf("%s: (%ds) %d minute(s)...\n", description, temps, temps / 60);
    else
        printf("%s: (%ds) %d second(s)...\n", description, temps, temps);
}

void afficher_liste_parametres(int item) {
    switch (item) {
    case TAG_SUBNET_MASK:
        printf("Subnet mask\n");
        break;
    case TAG_GATEWAY:
        printf("Gateway\n");
        break;
    case TAG_TIME_SERVER:
        printf("Time server\n");
        break;
    case TAG_DOMAIN_SERVER:
        printf("Domain name server\n");
        break;
    case TAG_LOG_SERVER:
        printf("Log server\n");
        break;
    case TAG_COOKIE_SERVER:
        printf("Cookie server\n");
        break;
    case TAG_HOSTNAME:
        printf("Hostname\n");
        break;
    case TAG_BOOTSIZE:
        printf("Bootsize\n");
        break;
    case TAG_DOMAINNAME:
        printf("Domain name\n");
        break;
    case TAG_STATIC_ROUTE:
        printf("Static route\n");
        break;
    case TAG_ARP_TIMEOUT:
        printf("ARP cache timeout\n");
        break;
    case TAG_NETBIOS_NS:
        printf("NetBIOS name server\n");
        break;
    case TAG_IP_LEASE:
        printf("IP lease time\n");
        break;

    case TAG_DHCP_MESSAGE:
        printf("DHCP message type\n");
        break;
    case TAG_SERVER_ID:
        printf("Server identifier\n");
        break;
    case TAG_PARM_REQUEST:
        printf("Parameter request list\n");
        break;
    case TAG_RENEWAL_TIME:
        printf("Renewal time\n");
        break;
    case TAG_REBIND_TIME:
        printf("Rebind time\n");
        break;
    case TAG_VENDOR_CLASS:
        printf("Vendor class identifier\n");
        break;
    case TAG_CLIENT_ID:
        printf("Client identifier\n");
        break;
    case TAG_TFTP_SERVER:
        printf("TFTP server name\n");
        break;
    case TAG_BOOTFILENAME:
        printf("Bootfile name\n");
        break;
    case TAG_MAX_MSG_SIZE:
        printf("Maximum DHCP message size\n");
        break;
    case TAG_AUTH:
        printf("Authentication\n");
        break;
    case TAG_SIP_SERVERS:
        printf("SIP Servers\n");
        break;
    case TAG_AGENT_CIRCUIT:
        printf("Agent Information Option\n");
        break;
    case TAG_SLP_DA:
        printf("SLP Directory Agent\n");
        break;
    case TAG_TFTP_SERVER_ADDRESS:
        printf("TFTP server address\n");
        break;
    case TAG_VENDOR_OPTS:
        printf("Vendor-Specific Information\n");
        break;
    default:
        printf("(%d)\n", item);
        break;
    }
}

void afficher_info(uint8_t *info, uint8_t taille, int type) {
    int i = 0;
    while (i != taille) {
        if (type == 1)
            printf("%c", info[i]);
        else
            printf("%.2x", info[i]);
        i++;
    }

    printf("\n");
}

void afficher_message_dhcp(int type_message) {
    switch (type_message) {
    case DHCPDISCOVER:
        printf("DHCP Discover (%d)\n", type_message);
        break;
    case DHCPOFFER:
        printf("DHCP Offer (%d)\n", type_message);
        break;
    case DHCPREQUEST:
        printf("DHCP Request (%d)\n", type_message);
        break;
    case DHCPDECLINE:
        printf("DHCP Decline (%d)\n", type_message);
        break;
    case DHCPACK:
        printf("DHCP ACK (%d)\n", type_message);
        break;
    case DHCPNAK:
        printf("DHCP NACK (%d)\n", type_message);
        break;
    case DHCPRELEASE:
        printf("DHCP Release (%d)\n", type_message);
        break;
    case DHCPINFORM:
        printf("DHCP Inform (%d)\n", type_message);
        break;
    case DHCPLEASEQUERY:
        printf("DHCP Lease Query (%d)\n", type_message);
        break;
    default:
        printf("(%d)\n", type_message);
        break;
    }
}