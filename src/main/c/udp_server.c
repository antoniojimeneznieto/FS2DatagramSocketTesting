#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define PORT 8888

int main() {
    int server_socket, client_addr_size;
    struct sockaddr_in server_addr, client_addr;
    char buf[BUF_SIZE];

    // Create UDP socket
    server_socket = socket(PF_INET, SOCK_DGRAM, 0);
    if (server_socket == -1) {
        perror("socket() error");
        exit(1);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    // Bind server socket to address
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind() error");
        exit(1);
    }

    printf("Server is listening on port %d\n", PORT);

    // Listen for incoming messages and echo them back
    while (1) {
        client_addr_size = sizeof(client_addr);
        int recv_len = recvfrom(server_socket, buf, BUF_SIZE, 0, (struct sockaddr *)&client_addr, &client_addr_size);
        if (recv_len == -1) {
            perror("recvfrom() error");
            exit(1);
        }

        buf[recv_len] = '\0';
        printf("Received from client: %s\n", buf);

        // Echo the message back to the client
        if (sendto(server_socket, buf, recv_len, 0, (struct sockaddr *)&client_addr, client_addr_size) == -1) {
            perror("sendto() error");
            exit(1);
        }
    }

    close(server_socket);
    return 0;
}
