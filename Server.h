//
//  Server.h
//
//  Made by Oskar Przybylski on 29/01/2025
//

#ifndef Server_h
#define Server_h

#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFSIZE 65536 

typedef struct Server{

    int domain;
    int service;
    int protocol;
    int port;
    int backlog;

    int socket;

    u_long interface;

    struct sockaddr_in address;
    void (*launch)(struct Server*);

}server_t;

/*  SERVER CONSTRUCTOR */
server_t serverInit(int domain, int service, int protocol, u_long interface, int port, int backlog, void (*launch)(server_t*));

#endif // Server_h