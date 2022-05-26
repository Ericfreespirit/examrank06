#include <sys/types.h> /* Voir NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>



int main(){

/*
    create socket
    bind

    listen 
    accept
*/
    int sockfd;
    struct sockaddr_in myaddr;

    // #1 SOCKET
    // create socket fd
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd == -1){
        printf("creation socket failed\n");
        exit(1);
    }
    else 
        printf("creation socket done\n");

    //init socketaddr
    myaddr.sin_family = AF_UNIX;
    inet_aton("127.0.0.1", &myaddr.sin_addr);
    myaddr.sin_port = htons(80);

    //bind sockfd and socketaddr
    if (bind(sockfd, (struct sockaddr *)&myaddr, sizeof(myaddr)) == -1){
        printf("bind failed\n");
        exit(1);
    }
    else 
        printf("bind done\n");

    // #2 LAUNCH SERVER
    // listen on sockfd
    if (listen(sockfd, 10) == -1){
        printf("listen failed\n");
        exit(1);
    }
    else
        printf("listening on [127.0.0.1:80] ...\n");
    if (accept(sockfd, (struct sockaddr *)&myaddr, (socklen_t *)sizeof(myaddr)) == -1){
        printf("connexion failed\n");
        exit(1);
    }
    else
        printf("connexion done\n");

    
    return (0);
}