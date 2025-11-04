#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    /*
    int socket(int domain, int type, int protocol);
    Tạo ra một endpoint (điểm giao tiếp) để truyền dữ liệu qua mạng.

        🔹 Tham số:
        Tham số	Ý nghĩa	Giá trị thường dùng
        domain	Loại địa chỉ	AF_INET (IPv4)
                                AF_INET6 (IPv6)
                                AF_UNIX (local IPC)
        type	Loại kết nối	SOCK_STREAM (TCP)
                                SOCK_DGRAM (UDP)
        protocol	Giao thức cụ thể	0 (mặc định theo type)
        hoặc IPPROTO_TCP, IPPROTO_UDP
    */
    server_fd = socket(AF_INET, SOCK_DGRAM, 0); // Tạo socket TCP IPv4
    /*
    int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

    🔹 Mục đích:

        Ràng buộc socket với địa chỉ IP và port cụ thể (áp dụng cho server).

        🔹 Tham số:
        Tham số	Ý nghĩa
        sockfd	Socket được tạo bởi socket()
        addr	Con trỏ tới cấu trúc địa chỉ (IPv4/IPv6/UNIX)
        addrlen	Kích thước của cấu trúc addr
    */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(server_fd);
        return -1;
    }

    printf("UDP server is running on port 8080...\n");
    printf("Waiting for client");
    while (1) {
        recvfrom(server_fd, buffer, sizeof(buffer), 0,
                (struct sockaddr*)&client_addr, &addr_len);
        printf("Received: %s\n", buffer);
        sendto(server_fd, "Hello Client", 12, 0,
            (struct sockaddr*)&client_addr, addr_len);
    }
    return 0;
}