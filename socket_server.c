#include <stdio.h>      //libreria standard per input/output
#include <stdlib.h>     //libreria standard per funzioni generiche (es. exit)
#include <string.h>     //per la manipolazione delle stringhe
#include <unistd.h>     //per funzioni di sistema (es. close)
#include <arpa/inet.h>  //per socket e funzioni di rete

#define PORT 5700              //porta del server
#define BUFFER_SIZE 1024       //dimensione massima del buffer per i dati

//gestisce la comunicazione con un client
void handle_client(int client_socket){
    char buffer[BUFFER_SIZE];
    char *responses[] = {
        "hey, buongiorno miele!",
        "come siamo belli questa mattina :)",
        "il sole bacia i belli e te hai tanta vitamina D!",
        "scrivendomi mi hai migliorato la giornata!"
    };

    memset(buffer, 0, BUFFER_SIZE);              //inizializza il buffer a zero
    read(client_socket, buffer, BUFFER_SIZE);    //legge i dati dal client
    printf("messaggio ricevuto: %s\n", buffer);
    
    int response_index = rand() % 4;                                                            //seleziona una risposta casuale
    send(client_socket, responses[response_index], strlen(responses[response_index]), 0);      //invia la risposta al client
    close(client_socket);                                                                      //chiude la connessione con il client
}

int main(){
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;        //strutture per memorizzare gli indirizzi del server e del client
    socklen_t addr_len = sizeof(client_addr);          //dimensione della struttura dell'indirizzo del client

    server_socket = socket(AF_INET, SOCK_STREAM, 0);        //crea il socket del server
    
    server_addr.sin_family = AF_INET;             //specifica la famiglia di indirizzi (IPv4)
    server_addr.sin_addr.s_addr = INADDR_ANY;     //accetta connessioni da qualsiasi indirizzo
    server_addr.sin_port = htons(PORT);           //converte il numero di porta in formato di rete

    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));        //collega il socket alla porta specificata
    listen(server_socket, 5); //mette il server in ascolto
    printf("server in ascolto sulla porta %d...\n", PORT);

    while(1){
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_len);       //accetta connessioni in arrivo
        handle_client(client_socket);                                                           //gestisce la comunicazione con il client
    }

    close(server_socket);        //chiude il socket del server 
    return 0;
}
