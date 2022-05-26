#include <sys/types.h> /* Voir NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h> 
#include <string.h>
#define IP "127.0.0.1"
#define PORT 8081

int main(){
/*
    create socket
    init socket addr
    connect

*/
    int sockfd;
    struct sockaddr_in myaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        perror("socket failed. Error");
        exit(1);
    }
    else
        printf("socket fd create\n");
    
    myaddr.sin_family = AF_INET;
    inet_aton(IP,  &myaddr.sin_addr);
    myaddr.sin_port = htons(PORT);
    
    if (connect(sockfd, (struct sockaddr *) &myaddr, sizeof(myaddr)) < 0){
        perror("connexion failed. Error");
        exit (1);
    }
    else 
        printf ("client connection done" );

    return (0);
}