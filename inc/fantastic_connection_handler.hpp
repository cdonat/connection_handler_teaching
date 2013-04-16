#ifndef FANTASTIC_CONNECTION_HANDLER_H
#define FANTASTIC_CONNECTION_HANDLER_H

#include "tcp_connection_handler.hpp"

class fantastic_connection_handler: public tcp_connection_handler {
    public:
        virtual bool read_message( message_buffer* buff );
        virtual bool send_message( message_buffer* buff );
        virtual bool shake_hands_start();
        virtual bool shake_hands_end();
};

#endif /* FANTASTIC_CONNECTION_HANDLER_H */
