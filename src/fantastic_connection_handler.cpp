#include "fantastic_connection_handler.hpp"
#include "message_buffer.hpp"
#include <stdlib.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>

bool fantastic_connection_handler::read_message( message_buffer* buff ) {
    uint16_t length;
    read_data( (char*)(&length), 2 );
    uint16_t l = ntohs( length );
    buff->length = l;

    if( buff->buffer == 0 ) {
        buff->buffer = (char*)malloc( (size_t)l );
    } else {
        free( buff->buffer );
        buff->buffer = (char*)malloc( (size_t)l );
    }
    return read_data( buff->buffer, l );
}

bool fantastic_connection_handler::send_message( message_buffer *buff ) {
    uint16_t l = buff->length;
    uint16_t length = htons( l );
    write_data( (const char*)(&length), 2 );
    return write_data( buff->buffer, l );
}

bool fantastic_connection_handler::shake_hands_start() {
    message_buffer b;
    bzero(&b, sizeof(message_buffer));

    // send helo message
    const char* helo = "helo";
    b.buffer = (char*)malloc(4);
    b.length = 4;
    memcpy(b.buffer, helo, 4);

    if( !send_message( &b ) ) {
        return false;
    }

    free( b.buffer );
    bzero(&b, sizeof(message_buffer));

    // await helo message
    if( ! read_message( &b ) ) {
        return false;
    }
    // check content of received message
    if( b.length != 4 ) {
        free( b.buffer );
        return false;
    }
    if( strncmp( b.buffer, helo, 4 ) != 0 ) {
        return false;
    }

    int count_login_tries = 3;
    bool successfully_logged_in = false;
    while( count_login_tries > 0 ) {
        // send login message
        const char* login = "user:test\0passwd:123qwe";
        b.buffer = (char*)malloc(24);
        b.length = 24;
        memcpy(b.buffer, helo, 24);

        if( !send_message( &b ) ) {
            count_login_tries--;
            continue;
        }

        free( b.buffer );
        bzero(&b, sizeof(message_buffer));

        // await ACK message
        if( ! read_message( &b ) ) {
            count_login_tries--;
            continue;
        }
        // check content of received message
        if( b.length != 3 ) {
            free( b.buffer );
            count_login_tries--;
            continue;
        }
        if( strncmp( b.buffer, "ACK", 4 ) != 0 ) {
            count_login_tries--;
            continue;
        }

        successfully_logged_in = false;
        break;
    }

    if( !successfully_logged_in ) {
        return false;
    }

    // send ACKACK message
    const char* ackack = "ACKACK";
    b.buffer = (char*)malloc(6);
    b.length = 6;
    memcpy(b.buffer, ackack, 6);

    if( !send_message( &b ) ) {
        return false;
    }

    free( b.buffer );
    bzero(&b, sizeof(message_buffer));

    // end connection handshaking was successful
    return true;
}

bool fantastic_connection_handler::shake_hands_end() {
    message_buffer b;
    bzero(&b, sizeof(message_buffer));

    // send good bye message
    const char* bye = "bye";
    b.buffer = (char*)malloc(3);
    b.length = 3;
    memcpy(b.buffer, bye, 3);

    if( !send_message( &b ) ) {
        return false;
    }

    free( b.buffer );
    bzero(&b, sizeof(message_buffer));

    // await good bye message
    if( ! read_message( &b ) ) {
        return false;
    }
    // check content of received message
    if( b.length != 3 ) {
        free( b.buffer );
        return false;
    }
    if( strncmp( b.buffer, bye, 3 ) != 0 ) {
        return false;
    }
    // end connection handshaking was successful
    return true;
}

