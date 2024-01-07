#include "tcp.h"

int port_ftp_data;

void traiter_tcp(const u_char *paquet, int taille, int verbosite) {

    struct tcphdr *tcp_header = (struct tcphdr *)(paquet);

    printf("\n");
    printf("TCP\n");

    if (verbosite > 1) {
        printf("Port source: %d\n", ntohs(tcp_header->source));
        printf("Port destination: %d\n", ntohs(tcp_header->dest));
    }
    if (verbosite > 2) {
        printf("Numéro de sequence: %u\n", ntohl(tcp_header->seq));
        printf("Numéro d'acquittement: %u\n", ntohl(tcp_header->ack_seq));
        printf("Data offset: %d\n", tcp_header->doff);
        printf("Reserved: %d\n", tcp_header->res1);
        printf("Flags: %d ", tcp_header->res2);
        traiter_flags(tcp_header);
        printf("Fenêtre: %d\n", ntohs(tcp_header->window));
        printf("Somme de contrôle: 0x%.x\n", ntohs(tcp_header->check));
        printf("Urgent pointer: %d\n", ntohs(tcp_header->urg_ptr));

        // Traitement des options

        traiter_options(tcp_header);
    }

    // Traitement des ports
    traiter_port_tcp(ntohs(tcp_header->source), ntohs(tcp_header->dest),
                     paquet + 4 * tcp_header->th_off,
                     taille - 4 * tcp_header->th_off, verbosite);
}

void traiter_flags(struct tcphdr *tcp_header) {
    if (tcp_header->urg) {
        printf("URG ");
    }
    if (tcp_header->ack) {
        printf("ACK ");
    }
    if (tcp_header->psh) {
        printf("PSH ");
    }
    if (tcp_header->rst) {
        printf("RST ");
    }
    if (tcp_header->syn) {
        printf("SYN ");
    }
    if (tcp_header->fin) {
        printf("FIN ");
    }
    printf("\n");
}

void traiter_options(struct tcphdr *tcp_header) {
    if (tcp_header->doff > 5) {
        printf("\n");
        printf("Options présentes: \n");

        uint8_t *options = (uint8_t *)tcp_header + sizeof(struct tcphdr);

        int taille_options = (tcp_header->doff - 5) * 4;

        for (int i = 0; i < taille_options;) {

            switch (options[i]) {
            case TCPOPT_NOP:
                printf("- NO-Operation (NOP) \n");
                i++;
                break;
            case TCPOPT_MAXSEG:
                printf("- Max Segment Size : ");
                if (taille_options - i >= 4) {
                    uint16_t taille = ntohs(*(uint16_t *)(options + i + 2));
                    printf("%d", taille);
                }
                printf("\n");
                i += options[i + 1];
                break;

            case TCPOPT_SACK_PERMITTED:
                printf("- SACK Permitted\n");
                i += options[i+1];
                break;
            case TCPOPT_SACK:
                printf("- SACK ");
                /*
                if (taille_options - i >= 10) {
                    uint32_t bloc_1 = ntohl(*(uint32_t *)(options + i + 2));
                    uint32_t bloc_2 = ntohl(*(uint32_t *)(options + i + 6));
                    printf("Bloc 1: %u Bloc 2: %u", bloc_1, bloc_2);
                }
                */
                printf("\n");
                i += options[i+1];
                break;
            case TCPOPT_WINDOW:
                printf("- Window Scale : ");
                if (taille_options - i >= 3) {
                    uint8_t window_scale = options[i + 2];
                    printf("%u\n", window_scale);
                }
                i += options[i+1];
                break;
            case TCPOPT_TIMESTAMP:
                printf("- Timestamp : ");
                if (taille_options - i >= 10) {
                    uint32_t ts_val = ntohl(*(uint32_t *)(options + i + 2));
                    uint32_t ts_ecr = ntohl(*(uint32_t *)(options + i + 6));
                    printf("TSval %u, TSecr %u", ts_val, ts_ecr);
                }
                printf("\n");
                i += options[i+1];
                break;
            case TCPOPT_EOL:
                printf("- End of Options List (EOL)\n");
                i = taille_options;
                break;
            default:
                printf("- Option inconnue\n");
                if(taille_options - i >= 2)
                    i += options[i+1];
                else
                    i++;
                break;
            }
        }
    } else {
        printf("Pas d'options\n");
    }
}
void traiter_port_tcp(int port_source, int port_destination,
                      const u_char *paquet, int taille, int verbosite) {
    // FTP
    if ((port_source == PORT_FTP || port_source == PORT_FTP_DATA) ||
        (port_destination == PORT_FTP_DATA || port_destination == PORT_FTP) ||
        ((port_destination == port_ftp_data || port_source == port_ftp_data) &&
         port_ftp_data != 0)) {

        if (taille > 0) {

            int port = traiter_ftp(paquet, taille, verbosite);
            if (port > 0)
                port_ftp_data = port;
        }
    }

    // POP
    if (port_source == PORT_POP || port_destination == PORT_POP) {
        if (taille > 0)
            traiter_pop(paquet, taille, verbosite);
    }

    // IMAP
    if (port_source == PORT_IMAP || port_destination == PORT_IMAP) {
        if (taille > 0)
            traiter_imap(paquet, taille, verbosite);
    }

    // HTTP
    if (port_source == PORT_HTTP || port_destination == PORT_HTTP ||
        port_source == PORT_HTTP_ALT || port_destination == PORT_HTTP_ALT) {
        if (taille > 0)
            traiter_http(paquet, taille, verbosite);
    }

    // SMTP
    if (port_source == PORT_SMTP || port_destination == PORT_SMTP ||
        port_source == PORT_SMTP_ALT || port_destination == PORT_SMTP_ALT ||
        port_source == PORT_SMTPS || port_destination == PORT_SMTPS) {
        if (taille > 0)
            traiter_smtp(paquet, taille, verbosite);
    }

    // TELNET
    if (port_source == PORT_TELNET || port_destination == PORT_TELNET) {
        if (taille > 0)
            traiter_telnet(paquet, taille, verbosite);
    }

    // DNS
    if (port_source == PORT_DNS || port_destination == PORT_DNS) {
        if (taille > 0)
            traiter_dns(paquet + 2, taille, verbosite);
    }
}
