#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024] = "Hello Server!";

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    write(sock, buffer, strlen(buffer));
    read(sock, buffer, sizeof(buffer));
    printf("Phan hoi tu server: %s\n", buffer);

    close(sock);
    return 0;
}
