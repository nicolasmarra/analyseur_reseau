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
#include "pop3.h"
#include "imap.h"
#include "http.h"
#include "smtp.h"
#include "telnet.h"
#include "bootp.h"
#include "dns.h"
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
#include "ctype.h"

#define PROMISCUOUS 1
#define CONFUS 0
#define DELAI 1000

#define PORT_FTP 21
#define PORT_FTP_DATA 20
#define PORT_POP 110
#define PORT_IMAP 143
#define PORT_HTTP 80
#define PORT_SMTP 25
#define PORT_SMTP_ALT 587
#define PORT_SMTPS 465
#define PORT_TELNET 23
#define PORT_DNS 53


noreturn void raler(int syserr, const char *msg, ...);

#endif