#include<stdio.h>
#include<string.h> //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h> //write
#define PORT 8080

int main(int argc , char *argv[]) {
    int soc_desc , client_soc , c , read_size;
    struct sockaddr_in serv , client;
    char client_message[2000];
    
    //Create socket
    soc_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (soc_desc == -1) {
        printf("Could not create socket");
    }
    puts("Socket created");
    
    //Prepare the sockaddr_in structure
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(PORT);
    
    //Bind
    if( bind(soc_desc,(struct sockaddr *)&serv , sizeof(serv)) < 0) {
    //print the error message
        perror("bind failed");
        return 1;
    }
    puts("bind done");
    
    //Listen
    listen(soc_desc , 3);
    
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    
    //accept connection from an incoming client
    client_soc = accept(soc_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_soc < 0) {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");
    
    //Receive a message from client
    while( (read_size = recv(client_soc , client_message , 2000 , 0)) > 0 ) {
    //Send the message back to client
        write(client_soc , client_message , strlen(client_message));
    }
    
    if(read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    } else if(read_size == -1) {
        perror("recv failed");
    }
    
    return 0;
}

