#include <sys/types.h> /* Voir NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <strings.h>
#include <errno.h>
#define IP "127.0.0.1"
#define PORT 8081


int main(){
    int sockfd ,csock;
    int id = 0;
    struct sockaddr_in myaddr;
    socklen_t len;

    // #1 SOCKET
    // create socket fd
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1){
        perror("socket failed. Error");
        exit(1);
    }
    else 
        printf("creation socket done\n");

    //init socketaddr
    bzero((struct sockaddr *) &myaddr,sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    inet_aton(IP,  &myaddr.sin_addr);
    myaddr.sin_port = htons(PORT);

    //bind sockfd and socketaddr
    if (bind(sockfd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0){
        perror("bind failed. Error");
        exit(1);
    }
    else 
        printf("bind done\n");

    // #2 LAUNCH SERVER
    // listen on sockfd
    if (listen(sockfd, 10) == -1){
        perror("listen failed. Error");
        exit(1);
    }
    else
        printf("listening on [%s:%d] ...\n", IP, PORT);
        len = sizeof(myaddr);
        if ((csock = accept(sockfd, (struct sockaddr *)&myaddr, &len)) < 0){
            perror("connection server failed. Error");
            exit(1);
        }
        else{
            printf("client %d: [%s:%d]\n", 
            id, inet_ntoa(myaddr.sin_addr), ntohs(myaddr.sin_port));
        }
        
        if (send(csock, "You are client 0\n", 20, 0) < 0){
            perror("send failed. Error");
            exit(1);
        }

    return (0);
}