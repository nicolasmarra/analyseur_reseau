# Projet Analyseur Réseau

Ce projet vise à développer un analyseur réseau sous Linux en utilisant la librairie pcap pour capturer et analyser les paquets circulant sur le réseau. L'objectif est d'afficher les informations des protocoles suivants : Ethernet, IP, UDP, TCP, ICMP, ARP, ainsi que certains protocoles applicatifs tels que BOOTP (DHCP), DNS, HTTP, FTP, SMTP, POP et IMAP.

Pour implémenter le protocole BOOTP, j'ai utilisé le fichier bootp.h disponible sur le site suivant : https://opensource.apple.com/source/tcpdump/tcpdump-1/tcpdump/bootp.h.auto.html


## Conception du projet et diffucultés rencontrées

J'ai réussi à mettre en place tous les protocoles demandés. Ce projet a été une excellente opportunité pour approfondir ma compréhension du fonctionnement de chacun de ces protocoles. Les protocoles BOOTP et DNS ont posé les plus grands défis ; pour le BOOTP, bien que je n'aie pas traité toutes les options, mon programme arrive à identifier une option non traitée comme inconnue. La mise en place du protocole Telnet a aussi présenté pas mal de difficultés.

Je reconnais qu'il reste des améliorations à apporter à ce programme, en particulier : L'affichage des informations, notamment en fonction du niveau de verbosité.
Ce projet a exigé beaucoup d'heures de travail, et j'ai dû consulter plusieurs RFC pour comprendre le fonctionnement des protocoles mis en place.


## Organisation des répertoires

- bin/ -> contient le fichier exécutable (analyseur). Il est généré automatiquement par le makefile.
- include/ -> contient les fichiers d'en-tête(.h).
- obj/ -> contient les objets (.o) générés par le makefile.
- src/ -> contient les fichiers .c.
- assets/ -> contient les fichiers utilisés pour tester le programme en mode offline.


## Exécution du programme

### Compilation 

Pour compiler le programme, il faut utiliser la commande suivante :

```bash
    make
```

Cette commande crée un dossier "bin" où se trouvera le fichier exécutable "analyseur".

Pour supprimer les fichiers de compilation, il faut utiliser la commande suivante :

```bash
    make clean
```

### Lancer le programme

Pour lancer le programme, on doit lancer l'exécutable généré par la commande "make" et respecter les arguments du programme. D'abord, on choisit le mode de capture (-i (nom de l'interface - en ligne) ou -o (nom du fichier - hors ligne)). Pour le mode en ligne, il faut exécuter le programme en mode sudo.

Pour utiliser ce programme, il faut utiliser les arguments suivants:

* -i <interface> : interface pour l'analyse en direct
* -o <fichier> : fichier d'entrée pour l'analyse hors ligne
* -f <filtre> : filtre BPF (optionnel)
* -v <1..3> : niveau de verbosité (1=très concis ; 2=synthétique ; 3=complet)

Pour le filtrage, on peut utiliser des filtres pour les protocoles suivants : IP, TCP, UDP, ARP et ICMP. En ce qui concerne les protocoles TCP et UDP, il est également possible de filtrer les ports à l'aide de la commande suivante, par exemple : -f "tcp port 80".
Lorsque le niveau de verbosité n'est pas défini, le programme s'exécute quand même en utilisant le niveau de verbosité 3 (complet).


#### Lancement du programme hors ligne


```bash
bin/analyseur -o <fichier> -v <verbosité>
```

- Exemple :


```bash
bin/analyseur -o assets/ftp.cap -v 3
```

#### Lancement du programme online

```bash
sudo bin/analyseur -i <interface> -v <verbosité>
```

- Exemple :

```bash
sudo bin/analyseur -i wlo1 -v 3
```

### Auteur

Nicolas MARRA - nicolasmarra12@gmail.com
