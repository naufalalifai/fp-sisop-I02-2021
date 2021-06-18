#include <stdio.h> //printf
#include <string.h> //strlen
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr
#include <unistd.h>
#define PORT 8080

int main(int argc , char *argv[]) {
    int soc;
    struct sockaddr_in server;
    char message[1000] , reply[2000];
 
    //Create socket
    soc = socket(AF_INET , SOCK_STREAM , 0);
    if(soc == -1) {
        printf("Socket creation error\n");
    }
    puts("Socket created\n");
    
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    //Connect to remote server
    if(connect(soc , (struct sockaddr *)&server , sizeof(server)) < 0) {
        perror("Connection failed\n");
        return 1;
    }
    puts("Connected\n");
    
    //communicating with server
    while(1) {
        printf("Enter message : ");
        scanf("%s" , message);
    
        //Send some data
        if(send(soc , message , strlen(message) , 0) < 0) {
            puts("Send failed\n");
            return 1;
        }
        
        //Receive a reply from the server
        if(recv(soc , reply , 2000 , 0) < 0) {
            puts("recv failed\n");
            break;
        }
        
        puts("Server reply :");
        puts(reply);
    }
    
    close(soc);
    return 0;
}
