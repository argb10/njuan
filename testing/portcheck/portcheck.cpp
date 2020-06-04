#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <future>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
/*
This function checks if a TCP port is open: retrieving info, creating socket and trying to connect
Original code from:
https://codereview.stackexchange.com/questions/155755/simple-and-effective-port-checker-in-c
*/
bool port_is_open(std::string domain, int PORT){
    std::string port = std::to_string(PORT);

    addrinfo *result;                       // addrinfo structure to proper connection
    addrinfo hints{};                       // addrinfo structure with the type of service requested
    hints.ai_family = AF_UNSPEC;            // either IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;        // connection-based protocol (TCP)
    char addressString[INET6_ADDRSTRLEN];   // blank address string for the ntop
    const char *retval = nullptr;           // result of the connection

    if (0 != getaddrinfo(domain.c_str(), port.c_str(), &hints, &result)) {
        std::cout << "NjuanAlert: Invalid domain/port";
    }

    for (addrinfo *addr = result; addr != nullptr; addr = addr->ai_next) {
        int handle = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (handle == -1) {
            continue; //fail creating socket
        }
        if (connect(handle, addr->ai_addr, addr->ai_addrlen) != -1) {
            switch(addr->ai_family) {
                case AF_INET: //IPV4
                    retval = inet_ntop(addr->ai_family, &(reinterpret_cast<sockaddr_in *>(addr->ai_addr)->sin_addr), addressString, INET6_ADDRSTRLEN);
                    break;
                case AF_INET6: //IPV6
                    retval = inet_ntop(addr->ai_family, &(reinterpret_cast<sockaddr_in6 *>(addr->ai_addr)->sin6_addr), addressString, INET6_ADDRSTRLEN);
                    break;
                default:
                    // unknown family
                    retval = nullptr;
            }
            close(handle);
            break;
        }
    }
    freeaddrinfo(result);

    return retval!=nullptr? true : false;
}

int main(int argc, char *argv[]) {
    std::string domain = "127.0.0.1";

    printf("Testing ports Njuan\n");
    for( int i = 1; i < 65535; i++)
    if(port_is_open(domain, i))
        printf("%d is open\n", i);
    
}