#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string>

#include "tcp_connection_handler.hpp"
#include "read_write_failure.hpp"


tcp_connection_handler::tcp_connection_handler(std::string hostname, uint16_t port): connection_handler(hostname, port) {
    hostname_ = hostname;
    port_ = port;
    socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    throw_on_error( socket_ < 0 );

    struct sockaddr_in srv;
    memset(&srv,0,sizeof(struct sockaddr_in));
    srv.sin_family = AF_INET;
    throw_on_error( inet_pton(AF_INET,hostname.c_str(),&srv.sin_addr) == 0 );
    srv.sin_port = htons(port);
 
    throw_on_error( connect(socket_,(struct sockaddr*)&srv,sizeof(struct sockaddr_in)) < 0 );
}


tcp_connection_handler::~tcp_connection_handler() {
    close(socket_);
}

void tcp_connection_handler::write_data(char* buff, size_t length) {
    read_or_write_data(buff, length, write);
}


void tcp_connection_handler::read_data(char* buff, size_t length) {
    read_or_write_data(buff, length, read);
}


inline void tcp_connection_handler::read_or_write_data(char* buff, size_t length, std::function<ssize_t (int, void*, size_t)> callback) {
    while( length != 0 ) {
        ssize_t bytes = callback( socket_, buff, length);
        throw_on_error( bytes < 0 );
        length -= bytes;
        buff += bytes;
    }
}


