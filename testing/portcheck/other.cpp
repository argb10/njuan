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

bool isPortOpen(const std::string &domain, const std::string &port)
{
    addrinfo *result;
    addrinfo hints{}; 
    hints.ai_family = AF_UNSPEC;   // either IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; 
    char addressString[INET6_ADDRSTRLEN];
    const char *retval = nullptr;
    if (0 != getaddrinfo(domain.c_str(), port.c_str(), &hints, &result)) {
        return "";
    }
    for (addrinfo *addr = result; addr != nullptr; addr = addr->ai_next) {
        int handle = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (handle == -1) {
            continue;
        }
        if (connect(handle, addr->ai_addr, addr->ai_addrlen) != -1) {
            switch(addr->ai_family) {
                case AF_INET:
                    retval = inet_ntop(addr->ai_family, &(reinterpret_cast<sockaddr_in *>(addr->ai_addr)->sin_addr), addressString, INET6_ADDRSTRLEN);
                    break;
                case AF_INET6:
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
    return retval==nullptr ? false : true;
}

int main(int argc, char *argv[]) {
    std::string domain = "127.0.0.1";

    for(int port=1 ; port < 5 ; port++)
        if(isPortOpen(domain, std::to_string(port)) == 0)
            printf("Port %d: Open\n", port);
}