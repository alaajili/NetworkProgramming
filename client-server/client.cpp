//
// Created by Abderrahmane Laajili on 1/9/23.
//
#include <cstdio>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdlib>
#include <netinet/in.h>
#include <cstring>
#include <iostream>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock;
    long val_read;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Socket Creation Error" << std::endl;
        exit(1);
    }

    memset(&serv_addr, 0, sizeof serv_addr);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        exit(1);
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof serv_addr) < 0) {
        std::cerr << "Connection Failed" << std::endl;
        exit(1);
    }
    send(sock, "Hello from client", 17, 0);
    std::cout << "Hello message sent" << std::endl;
    val_read = read(sock, buffer, 1024);
    std::cout << buffer << std::endl;
    return 0;
}