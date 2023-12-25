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
        printf("Somme de contrôle: %d\n", ntohs(tcp_header->check));
        printf("Urgent pointer: %d\n", ntohs(tcp_header->urg_ptr));
    }

    // Traitement des options
    traiter_options(tcp_header);

    // Traitement des ports
    traiter_port_tcp(ntohs(tcp_header->source), ntohs(tcp_header->dest),
                     paquet + 4 * tcp_header->th_off, taille - 4 *tcp_header->th_off, verbosite);
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
        printf("Options présentes\n");
    } else {
        printf("Pas d'options\n");
    }
}

void traiter_port_tcp(int port_source, int port_destination, const u_char *paquet,int taille, int verbosite)
{
    // FTP

    if ((port_source == PORT_FTP || port_source == PORT_FTP_DATA) || (port_destination == PORT_FTP_DATA || port_destination == PORT_FTP) || ((port_destination == port_ftp_data || port_source == port_ftp_data) && port_ftp_data != 0)) {
        
        if(taille > 0){
            
        int port = traiter_ftp(paquet, taille, verbosite);
        if (port > 0)
        {
            port_ftp_data = port;
        }   

        } 
    }

}
