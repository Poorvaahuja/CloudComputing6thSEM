#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server. Type messages below:\n");

    char buffer[BUFFER_SIZE];
    while (1) {
        printf("You: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        send(sock, buffer, strlen(buffer), 0);

        int bytes_received = recv(sock, buffer, BUFFER_SIZE, 0);
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';
            printf("Server: %s", buffer);
        }
    }

    close(sock);
    return 0;
}
