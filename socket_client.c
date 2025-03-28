#include <stdio.h>      //libreria standard per input/output
#include <stdlib.h>     //libreria standard per funzioni generiche (es. exit)
#include <string.h>     //per la manipolazione delle stringhe
#include <unistd.h>     //per funzioni di sistema (es. close)
#include <arpa/inet.h>  //per socket e funzioni di rete

#define SERVER_IP "127.0.0.1"  //indirizzo IP del server (localhost)
#define PORT 5700              //porta del server
#define BUFFER_SIZE 1024       //dimensione massima del buffer per i dati

int main(){
    int sock;                   //socket descriptor
    struct sockaddr_in server_addr;  //struttura per l'indirizzo del server
    char buffer[BUFFER_SIZE];    //buffer per invio/ricezione dei dati

    sock = socket(AF_INET, SOCK_STREAM, 0); //creazione del socket TCP
    
    //configurazione dell'indirizzo del server
    server_addr.sin_family = AF_INET;              //IPv4
    server_addr.sin_port = htons(PORT);            //conversione della porta in formato di rete
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);  //conversione dell'indirizzo IP in binario
    
    connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)); //connessione al server
    
    printf("inserisci il messaggio: "); //lettura di un messaggio dall'utente
    fgets(buffer, BUFFER_SIZE, stdin);  //acquisizione dell'input con protezione del buffer
    
    send(sock, buffer, strlen(buffer), 0); //invio del messaggio al server
    
    memset(buffer, 0, BUFFER_SIZE); //pulizia del buffer prima di ricevere la risposta
    
    read(sock, buffer, BUFFER_SIZE); //lettura della risposta dal server
    
    printf("risposta dal server: %s\n", buffer); //stampa della risposta ricevuta
    
    close(sock); //chiusura del socket
    return 0;
}
