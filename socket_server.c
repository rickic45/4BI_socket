#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5700
#define BUFFER_SIZE 1024

void handle_client(int client_socket){
    char buffer[BUFFER_SIZE];
    char *responses[] = {
        "hey, buongiorno miele!",
        "come siamo belli questa mattina :)",
        "il sole bacia i belli e te hai tanta vitamina D!",
        "scrivendomi mi hai migliorato la giornata!"
    };

    memset(buffer, 0, BUFFER_SIZE);
    read(client_socket, buffer, BUFFER_SIZE);
    printf("messaggio ricevuto: %s\n", buffer);
    
    int response_index = rand() % 4;
    send(client_socket, responses[response_index], strlen(responses[response_index]), 0);
    close(client_socket);
}

int main(){
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_socket, 5);
    printf("server in ascolto sulla porta %d...\n", PORT);

    while(1){
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_len);
        handle_client(client_socket);
    }

    close(server_socket);
    return 0;
}
