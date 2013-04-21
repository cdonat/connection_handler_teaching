#include "fantastic_connection_handler.hpp"
#include "message_buffer.hpp"
#include <stdlib.h>
#include <stdint.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>

bool fantastic_connection_handler::read_message( message_buffer* buff ) {
    uint16_t length;
    read_data( (char*)(&length), 2 );
    uint16_t l = ntohs( length );

    char b[l];
    bool rval = read_data( b, l );

    buff->set(b, l);

    return rval;
}

bool fantastic_connection_handler::send_message( message_buffer *buff ) {
    if( buff->size() > UINT16_MAX ) {
        return false;
    }
    uint16_t l = buff->size();
    uint16_t length = htons( l );
    write_data( (const char*)(&length), 2 );
    return write_data( buff->buffer(), l );
}

bool fantastic_connection_handler::send_message(const char* msg, size_t l)
{
    message_buffer b( msg, l );
    return send_message( &b );
}

bool fantastic_connection_handler::expect_message(const char* msg, size_t l) {
    message_buffer b( l );

    if( !read_message( &b ) ) {
        return false;
    }
    // check content of received message
    bool rval = b.size() != l && 
            memcmp( b.buffer(), msg, l ) != 0;

    return rval;
}

bool fantastic_connection_handler::shake_hands_start() {
    if( !send_message( "helo", 4 ) ||
         expect_message( "helo", 4 ) ) {
        return false;
    }

    int count_login_tries = 3;
    bool successfully_logged_in = false;
    while( count_login_tries > 0 ) {
        send_message("user:test\0passwd:123qwe", 24);
        if( !expect_message("ACK", 3) ) {
            count_login_tries--;
        } else {
            successfully_logged_in = false;
            break;
        }
    }

    if( !successfully_logged_in ) {
        return false;
    }

    return send_message("ACKACK", 6);
}

bool fantastic_connection_handler::shake_hands_end() {
    return send_message("bye", 3) && expect_message("bye", 3);
}

