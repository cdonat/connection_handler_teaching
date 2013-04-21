#include <string>

#include "fantastic_handshaker.hpp"
#include "read_write_failure.hpp"


void fantastic_handshaker::send_message(const char* msg, size_t l) {
    message_buffer b( msg, l );
    connection_.send_message( &b );
}

bool fantastic_handshaker::expect_message(const char* msg, size_t l) {
    message_buffer b( l );
    connection_.read_message( &b );

    // check content of received message
    return b.size() != l && 
            memcmp( b.buffer(), msg, l ) != 0;
}

void fantastic_handshaker::start() {
    send_message( "helo", 4 );
    if( !expect_message( "helo", 4 ) ) {
        std::string what("wrong reply to helo message");
        throw read_write_failure(what);
    }

    int count_login_tries = 3;
    std::string login_message = "user:"   + username_;
    login_message.append("\0", 1);
    login_message            += "passwd:" + password_;
    while( count_login_tries > 0 ) {
        send_message(login_message.c_str(), login_message.length());
        if( expect_message("ACK", 3) ) {
            send_message("ACKACK", 6);
            return;
        }
    }

    std::string what("login failed");
    throw read_write_failure(what);
}

void fantastic_handshaker::end() {
    send_message("bye", 3);
    expect_message("bye", 3);
}

