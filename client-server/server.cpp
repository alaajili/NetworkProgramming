#include <cstdio>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdlib>
#include <netinet/in.h>
#include <cstring>
#include <iostream>

#define PORT 8080

int main()
{
    int                 server_fd;
    int                 new_socket;
    long                val_read;
    struct sockaddr_in  address;
    int                 addr_len;

    addr_len = sizeof address;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "Error in socket" << std::endl;
        exit(1);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    memset(address.sin_zero, '\0', sizeof address.sin_zero);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof address) < 0) {
        std::cerr << "Error in bind" << std::endl;
        exit(1);
    }
    if (listen(server_fd, 10) < 0) {
        std::cerr << "Error in listen" << std::endl;
        exit(1);
    }

    while (1337) {
        std::cout << "\n++++++++ Waiting for new connection ++++++++\n" << std::endl;
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addr_len);
        if (new_socket < 0) {
            std::cerr << "Error in accept" << std::endl;
            exit(1);
        }

        char buffer[30000] = {0};
        val_read = read(new_socket, buffer, 30000);
        std::cout << buffer << std::endl;
        write(new_socket, "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!", 200);
        std::cout << "---------- Message sent ----------" << std::endl;
        close(new_socket);
    }
    return 0;
}