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

    unlink(CLIENT_PATH);

    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sun_family = AF_UNIX;
    strcpy(client_addr.sun_path, CLIENT_PATH);

    if (bind(sock, (struct sockaddr*)&client_addr, sizeof(client_addr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SERVER_PATH);

    const char *msg = "Hello from UNIX UDP client!";
    sendto(sock, msg, strlen(msg) + 1, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));

    recvfrom(sock, buf, sizeof(buf), 0, NULL, NULL);
    printf("Client received: %s\n", buf);

    close(sock);
    unlink(CLIENT_PATH);
    return 0;
}
