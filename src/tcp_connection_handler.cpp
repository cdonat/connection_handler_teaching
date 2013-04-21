#include "tcp_connection_handler.hpp"
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>


bool tcp_connection_handler::establish_connection(std::string hostname, uint16_t port) {
    hostname_ = hostname;
    port_ = port;
    socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in srv;
 
    memset(&srv,0,sizeof(struct sockaddr_in));
 
    srv.sin_family = AF_INET;
    inet_pton(AF_INET,"1.2.3.4",&srv.sin_addr); // Schreibe IP-Adresse des Servers in die sockaddr_in-Struktur
    srv.sin_port = htons(1234); // Schreibe Port in Network-Byte-Order (Big Endian) in das Feld sin_port
 
    if( connect(socket_,(struct sockaddr*)&srv,sizeof(struct sockaddr_in)) < 0 ) {
        return false;
    }

    return true;
}


bool tcp_connection_handler::close_connection() {
    return close(socket_) == 0;
}


bool tcp_connection_handler::write_data(char* buff, size_t length) {
    return read_or_write_data(buff, length, write);
}


bool tcp_connection_handler::read_data(char* buff, size_t length) {
    return read_or_write_data(buff, length, read);
}


bool tcp_connection_handler::read_or_write_data(char* buff, size_t length, std::function<ssize_t (int, void*, size_t)> callback) {
    while( length != 0 ) {
        ssize_t bytes = callback( socket_, buff, length);
        if( bytes < 0 ) {
            return false;
        }
        length -= bytes;
        buff += bytes;
    }
    return true;
}


