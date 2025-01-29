//
//  Server.c
//
//  Made by Oskar Przybylski on 29/01/2025
//

#include "Server.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

server_t serverInit(int domain, int service, int protocol, u_long interface, int port, int backlog, void (*launch)(server_t*)){
    server_t server;

    memset(&server,0,sizeof(struct Server));

    server.domain = domain;
    server.service = service;
    server.protocol = protocol;
    server.interface = interface;
    server.port = port;
    server.backlog = backlog;

    server.address.sin_family = domain;
    server.address.sin_port = htons(port);
    server.address.sin_addr.s_addr = htonl(interface);

    server.socket = socket(domain,service,protocol);

    if (server.socket == 0){
        perror("[-] Failed to connect to socket! \n");
        exit(EXIT_FAILURE);
    }

    if( (bind(server.socket,(struct sockaddr *)&server.address,sizeof(server.address))) != 0){
        perror("[-] Failed to bind socket to network! \n");
        shutdown(server.socket,SHUT_RDWR);
        exit(EXIT_FAILURE);
    }

    if((listen(server.socket,server.backlog)) == -1){
        perror("[-] Failed to make socket listening! \n");
        shutdown(server.socket,SHUT_RDWR);
        exit(EXIT_FAILURE);
    }

    fprintf(stdout,"[+] Created new server \n");

    server.launch = launch;

    return server;
}

