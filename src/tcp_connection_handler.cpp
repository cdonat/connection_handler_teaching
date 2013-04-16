#include "tcp_connection_handler.hpp"
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

bool tcp_connection_handler::establish_connection(std::string hostname, uint16_t port) {
    hostname_ = hostname;
    port_ = port;
    socket_ = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 6);
    // TODO addr und addrlen müssen noch erzeugt werden
/*    if( connect(socket_, addr, addrlen) < 0 ) {
        return false;
    }
  */  //...
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

