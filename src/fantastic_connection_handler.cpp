#include "fantastic_connection_handler.hpp"
#include "message_buffer.hpp"
#include <stdlib.h>
#include <stdint.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>

fantastic_connection_handler::fantastic_connection_handler(std::string hostname, uint16_t port): tcp_connection_handler(hostname, port) {
    shake_hands_start();
}

fantastic_connection_handler::~fantastic_connection_handler() {
    try {
        shake_hands_end();
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
    if( buff->size() > UINT16_MAX ) {
        std::string what("value out of range");
        throw read_write_failure(what);
    }

    uint16_t l = buff->size();
    uint16_t length = htons( l );

    write_data( (char*)(&length), 2 );
    write_data( buff->buffer(), l );
}

void fantastic_connection_handler::send_message(const char* msg, size_t l) {
    message_buffer b( msg, l );
    send_message( &b );
}

bool fantastic_connection_handler::expect_message(const char* msg, size_t l) {
    message_buffer b( l );

    read_message( &b );
    // check content of received message
    return b.size() != l && 
            memcmp( b.buffer(), msg, l ) != 0;
}

void fantastic_connection_handler::shake_hands_start() {
    send_message( "helo", 4 );
    if( !expect_message( "helo", 4 ) ) {
        std::string what("wrong reply to helo message");
        throw read_write_failure(what);
    }

    int count_login_tries = 3;
    while( count_login_tries > 0 ) {
        send_message("user:test\0passwd:123qwe", 24);
        if( expect_message("ACK", 3) ) {
            send_message("ACKACK", 6);
            return;
        }
    }

    std::string what("login failed");
    throw read_write_failure(what);
}

void fantastic_connection_handler::shake_hands_end() {
    send_message("bye", 3);
    expect_message("bye", 3);
}

