#ifndef UTILES_H
#define UTILES_H

#include "ip.h"
#include "netinet/if_ether.h"
#include "netinet/ip.h"
#include "netinet/ip6.h"
#include "tcp.h"
#include "udp.h"
#include "arp.h"
#include "ftp.h"
#include "icmp.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <netinet/in.h>
#include <string.h>

#define PROMISCUOUS 0
#define CONFUS 1
#define DELAI 1000

#define PORT_FTP 21
#define PORT_FTP_DATA 20

noreturn void raler(int syserr, const char *msg, ...);

#endif