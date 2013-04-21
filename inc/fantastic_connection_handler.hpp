#ifndef FANTASTIC_CONNECTION_HANDLER_H
#define FANTASTIC_CONNECTION_HANDLER_H

#include "handshaker.hpp"
#include "tcp_connection_handler.hpp"

class fantastic_connection_handler: public tcp_connection_handler {
    public:
        fantastic_connection_handler(std::string hostname, uint16_t port, handshaker& shake_hands);
        virtual ~fantastic_connection_handler();

        virtual void read_message( message_buffer* buff );
        virtual void send_message( message_buffer* buff );
 
    private:
        handshaker& shake_hands_;
};

#endif /* FANTASTIC_CONNECTION_HANDLER_H */
