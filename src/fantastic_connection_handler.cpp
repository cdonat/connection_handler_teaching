#include <stdlib.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>

#include "message_buffer.hpp"
#include "read_write_failure.hpp"
#include "fantastic_connection_handler.hpp"


fantastic_connection_handler::fantastic_connection_handler(std::string hostname, uint16_t port, handshaker& shake_hands): 
    tcp_connection_handler(hostname, port),
    shake_hands_(shake_hands) {
        shake_hands_.start();
}

fantastic_connection_handler::~fantastic_connection_handler() {
    try {
        shake_hands_.end();
    } catch(read_write_failure e) {
        return;
    }
}

void fantastic_connection_handler::read_message( message_buffer* buff ) {
    uint16_t length;
    read_data( (char*)(&length), 2 );
    uint16_t l = ntohs( length );

    char b[l];
    read_data( b, l );

    buff->set(b, l);
}

void fantastic_connection_handler::send_message( message_buffer *buff ) {
    if( buff->size() > 65536 ) {
        std::string what("value out of range");
        throw read_write_failure(what);
    }

    uint16_t l = buff->size();
    uint16_t length = htons( l );

    write_data( (char*)(&length), 2 );
    write_data( buff->buffer(), l );
}


