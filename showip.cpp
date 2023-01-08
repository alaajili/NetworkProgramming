#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int ac, char **av) {
    struct  addrinfo hints, *res, *p;
    int     status;
    char   ipstr[INET6_ADDRSTRLEN];

    if (ac != 2) {
        std::cerr << "usage: showip hostname" << std::endl;
        return 1;
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
    hints.ai_socktype = SOCK_STREAM;

    status = getaddrinfo(av[1], NULL, &hints, &res);
    if (status != 0) {
        std::cerr << "getaddrinfo: " << gai_strerror(status) << std::endl;
        return 2;
    }

    std::cout << "IP addresses for " << av[1] << std::endl;

    for (p = res; p != nullptr; p = p->ai_next) {
        void    *addr;
        std::string  ipver;

        if (p->ai_family == AF_INET ) { //  IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        } else { //  IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }

        // convert the IP to a string
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        std::cout << ipver << ":  " << ipstr << std::endl;
    }
    freeaddrinfo(res);

    return 0;
}
