#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H

#include "message_buffer.hpp"
#include <string>
#include <stdint.h>

class connection_handler {
    public:
        connection_handler(std::string hostname, uint16_t port):
            hostname_(hostname), port_(port) {};
        virtual ~connection_handler() {};

        virtual void read_message( message_buffer* buff ) = 0;
        virtual void send_message( message_buffer* buff ) = 0;
    protected:
        std::string hostname_;
        uint16_t port_;
};

#endif /* CONNECTION_HANDLER_H */
