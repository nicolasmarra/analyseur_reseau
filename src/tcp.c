#include "tcp.h"

void traiter_tcp(const u_char *paquet, int verbosite) {

    struct tcphdr *tcp_header = (struct tcphdr *)(paquet);

    printf("\n");
    printf("TCP\n");

    if (verbosite > 1) {
        printf("Port source: %d\n", ntohs(tcp_header->source));
        printf("Port destination: %d\n", ntohs(tcp_header->dest));
    }
    if (verbosite > 2) {
        printf("Numéro de sequence: %d\n", ntohl(tcp_header->seq));
        printf("Numéro d'acquittement: %d\n", ntohl(tcp_header->ack_seq));
        printf("Data offset: %d\n", tcp_header->doff);
        printf("Reserved: %d\n", tcp_header->res1);
        printf("Flags: %d", tcp_header->res2);
        //traiter_flags(tcp_header);
        printf("Fenêtre: %d\n", ntohs(tcp_header->window));
        printf("Somme de contrôle: %d\n", ntohs(tcp_header->check));
        printf("Urgent pointer: %d\n", ntohs(tcp_header->urg_ptr));
    }

    // Traitement des options
    //traiter_options(tcp_header);
}
/*
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
        printf("Options présentes\n");
    } else {
        printf("Pas d'options\n");
    }
}
*/