#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    socklen_t addr_len = sizeof(client_addr);
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

    server_fd = socket(AF_INET, SOCK_STREAM, 0); // Tạo socket TCP IPv4

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
    */

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
        /*
    int listen(int sockfd, int backlog);
    🔹 Mục đích:
    Biến socket thành listening socket, sẵn sàng chấp nhận kết nối đến.

    🔹 Tham số:
    Tham số	Ý nghĩa
    sockfd	Socket đã được bind()
    backlog	Số lượng kết nối tối đa được xếp hàng chờ (thường 5–10)
    */

    listen(server_fd, 5);
    printf("Server dang lang nghe o cong 8080...\n");
        /*
    accept() — Chấp nhận kết nối từ client
    int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

    🔹 Mục đích:

    Chờ client kết nối đến, tạo socket mới để giao tiếp với client đó.

    🔹 Tham số:
    Tham số	Ý nghĩa
    sockfd	Socket đang lắng nghe
    addr	Con trỏ để chứa địa chỉ client (IP + port)
    addrlen	Con trỏ chứa kích thước cấu trúc addr
    */

    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);
    printf("Client ket noi thanh cong!\n");

    read(client_fd, buffer, sizeof(buffer));
    printf("Nhan: %s\n", buffer);

    write(client_fd, "Hello Client!", 13);

    close(client_fd);
    close(server_fd);
    return 0;
}
