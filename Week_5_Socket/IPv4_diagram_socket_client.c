#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_fd;
    struct sockaddr_in server_addr;
    char buffer[1024] = "Hello Server";
    socklen_t addr_len = sizeof(server_addr);

    client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_fd < 0) {
        perror("socket failed");
        return -1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    while (1) {
        sendto(client_fd, buffer, strlen(buffer), 0,
               (struct sockaddr*)&server_addr, sizeof(server_addr));
        ssize_t recv_len = recvfrom(client_fd, buffer, sizeof(buffer) - 1, 0, NULL, NULL);
        if (recv_len > 0) {
            buffer[recv_len] = '\0';
            printf("Server: %s\n", buffer);
        }
        sleep(1);
    }

    close(client_fd);
    return 0;
}
