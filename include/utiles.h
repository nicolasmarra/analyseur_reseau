#ifndef UTILES_H
#define UTILES_H

#include "netinet/if_ether.h"
#include "netinet/ip.h"
#include "netinet/ip6.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>

#include "ip.h"
#include "udp.h"

#define PROMISCUOUS 0
#define CONFUS 1
#define DELAI 1000

noreturn void raler(int syserr, const char *msg, ...);

#endif