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
    socket_ = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);

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

bool tcp_connection_handler::write_data( const char* buff, size_t length ) {
    const char* b = buff;
    size_t l = length;
    while( length != 0 ) {
        ssize_t written_bytes = write( socket_, b, l);
        if( written_bytes < 0 ) {
            return false;
        }
        l -= written_bytes;
        b += written_bytes;
    }
}

bool tcp_connection_handler::read_data( char* buff, size_t length ) {
    char* b = buff;
    size_t l = length;
    while( length != 0 ) {
        ssize_t written_bytes = read( socket_, b, l);
        if( written_bytes < 0 ) {
            return false;
        }
        l -= written_bytes;
        b += written_bytes;
    }
}

