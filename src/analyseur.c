#include <stdio.h>
#include <pcap.h>
#include <arpa/inet.h>
#include <string.h>  
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>

#define PAQUET_LIMITE 1
#define DELAI         10000  
#define PROMISCUOUS   0
#define CONFUS        1
#define SNAPSHOT_LEN  1028
#define NB_PAQUET     10


void traiter_paquet_UDP(const u_char *paquet){
    
    struct udphdr *udp_en_tete;

    int taille = sizeof(struct ether_header) + sizeof(struct ip);
    udp_en_tete = (struct udphdr *)(paquet + taille);

    printf("Port source UDP : %d\n", ntohs(udp_en_tete->source));
    printf("Port destination UDP : %d\n", ntohs(udp_en_tete->dest));
    printf("Longueur UDP : %d\n", ntohs(udp_en_tete->len));
    printf("Somme de contrôle : %d\n", ntohs(udp_en_tete->check));

}

void traiter_paquet_TCP(const u_char *paquet)
{
    struct tcphdr *tcp_en_tete;

    int taille = sizeof(struct ether_header) + sizeof(struct ip);
    tcp_en_tete = (struct tcphdr *)(paquet + taille);

    printf("Port source TCP : %d\n",ntohs(tcp_en_tete->th_sport));
    printf("Port destination TCP : %d\n",ntohs(tcp_en_tete->th_dport));
    printf("Numéro de séquence TCP : %u\n",ntohs(tcp_en_tete->th_seq));
    printf("Numéro d'acquittement TCP : %u\n",ntohs(tcp_en_tete->th_ack));
    printf("Flags TCP : %x\n",ntohs(tcp_en_tete->th_flags));
    printf("Taille de l'en-tête TCP : %d\n",ntohs(tcp_en_tete->th_off * 4));

    // Traitement des options TCP
    int options_offset = taille + tcp_en_tete->th_off * 4;
    int options_taille = options_offset - sizeof(struct tcphdr *);

    if(options_taille > 0){

    }
}

void traiter_paquet_IP(const u_char *paquet)
{
    struct ip *ip_en_tete;
    
    int taille = sizeof(struct ether_header);
    ip_en_tete = (struct ip *)(paquet + taille);

    printf("Source : %s\n", inet_ntoa(ip_en_tete->ip_src));
    printf("Destination : %s\n", inet_ntoa(ip_en_tete->ip_dst));
    printf("Taille du paquet IP : %d\n", ntohs(ip_en_tete->ip_len));
    
    switch (ip_en_tete->ip_p)
    {
    case IPPROTO_UDP:
        printf("Protocole UDP\n");
        traiter_paquet_UDP(paquet);
        break;
    case IPPROTO_TCP:
        printf("Protocole TCP\n");
        traiter_paquet_TCP(paquet);
        break;
    case IPPROTO_ICMP :
        printf("Protocole ICMP\n");
        break;    
    default:
        break;
    }

}

void traiter_ethernet(u_char *args,const struct pcap_pkthdr *header,const u_char *paquet)
{
    (void) args;

    struct ether_header *ethernet_en_tete;
    ethernet_en_tete = (struct ether_header*) paquet;


    printf("PAQUET ETHERNET\n");
    printf("Adresse MAC \n");
 
    printf("Source : %s\n",ether_ntoa((struct ether_addr *)ethernet_en_tete->ether_shost));
    printf("Destination : %s\n",ether_ntoa((struct ether_addr *)ethernet_en_tete->ether_dhost));
    printf("Taille du paquet : %d\n",header->len);


    switch (ntohs(ethernet_en_tete->ether_type))
    {
    case ETHERTYPE_IP:
        printf("IP\n");
        traiter_paquet_IP(paquet);
        break;
    case ETHERTYPE_ARP:
        printf("ARP\n");
        break;
    case ETHERTYPE_REVARP:
        printf("Reverse ARP\n");
        break;
    default:
        printf("Autre paquet\n");
        break;
    }

}



int main()
{
    char *interface;
    char erreur_buffer[PCAP_ERRBUF_SIZE];
    pcap_t *handle;

    /*Recherche une interface*/
    interface = pcap_lookupdev(erreur_buffer);
    if(interface == NULL)
    {
        printf("Erreur lors de la recherche d'interface %s\n",erreur_buffer);
        return 1;
    }

    /*Ouverture d'une capture */
    handle = pcap_open_live(interface, SNAPSHOT_LEN, CONFUS, DELAI, erreur_buffer);

    if(handle == NULL)
    {
        fprintf(stderr, "Erreur d'ouverture de l'interface %s: %s\n",interface, erreur_buffer);
        return 2;
    }
    
    pcap_loop(handle,NB_PAQUET,traiter_ethernet,NULL);

    pcap_close(handle);
    return 0;
}

