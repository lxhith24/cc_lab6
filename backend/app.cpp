#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fstream>
#include <sstream>

std::string getHostname() {
    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    return std::string(hostname);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    std::cout << "Server listening on port 8080" << std::endl;

    while (true) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

        std::string hostname = getHostname();
        std::string body = "Served by backend: " + hostname;
        std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: " + std::to_string(body.size()) + "\r\n\r\n" + body;

        send(new_socket, response.c_str(), response.size(), 0);
        close(new_socket);
    }

    return 0;
}
