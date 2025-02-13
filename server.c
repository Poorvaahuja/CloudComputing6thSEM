#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_CLIENTS 5
#define BUFFER_SIZE 1024

void *handle_client(void *client_socket) {
    int sock = *(int *)client_socket;
    char buffer[BUFFER_SIZE];
    int bytes_read;

    while ((bytes_read = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
        buffer[bytes_read] = '\0';
        printf("Client %d: %s\n", sock, buffer);
        send(sock, buffer, strlen(buffer), 0);
    }

    printf("Client %d disconnected.\n", sock);
    close(sock);
    free(client_socket);
    return NULL;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    pthread_t thread_id;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) >= 0) {
        printf("New connection accepted: %d\n", new_socket);
        int *client_sock = malloc(sizeof(int));
        *client_sock = new_socket;
        pthread_create(&thread_id, NULL, handle_client, (void *)client_sock);
        pthread_detach(thread_id);
    }

    close(server_fd);
    return 0;
}
