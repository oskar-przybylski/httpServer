//
//  test.c
//
//  Made by Oskar Przybylski on 29/01/2025
//

#include "Server.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void launch(server_t* server){
    while(1){
        printf("[~] Wainting for new connection. \n");

        int addrLen = sizeof(server->address);

        int newSocket = accept(server->socket,(struct sockaddr*)&server->address,(socklen_t*)&addrLen);

        if(newSocket < 0){
            perror("[-] Error while connecting with client! \n");
            exit(EXIT_FAILURE);
        }

        fprintf("[+] Connected with new Client \n");

        char buffer[BUFFSIZE];

        read(newSocket,buffer,BUFFSIZE);

        fprintf(stdout,"[+] Clients Ask: \n %s \n",buffer);

        char* hello = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n <html><body><h1>Homo Deus !</h1></body></html>";

        write(newSocket,hello,strlen(hello));

        close(newSocket);
    }
}

int main(){
    server_t s1 = serverInit(AF_INET,SOCK_STREAM,0,INADDR_ANY,80,10,launch);
    s1.launch(&s1);

    return 0;
}