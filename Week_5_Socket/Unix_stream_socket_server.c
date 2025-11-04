#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SERVER_PATH "/tmp/unix_udp_server"
#define CLIENT_PATH "/tmp/unix_udp_client"

int main() {
    int sock;
    struct sockaddr_un server_addr, client_addr;
    char buf[128];

    sock = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    unlink(SERVER_PATH);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SERVER_PATH);

    if (bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    printf("Server waiting for message...\n");

    socklen_t len = sizeof(client_addr);
    recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&client_addr, &len);
    printf("Server received: %s\n", buf);

    const char *reply = "Hello from UNIX UDP server!";
    sendto(sock, reply, strlen(reply) + 1, 0, (struct sockaddr*)&client_addr, len);

    close(sock);
    unlink(SERVER_PATH);
    return 0;
}
