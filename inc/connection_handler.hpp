#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H

#include "message_buffer.hpp"
#include <string>
#include <stdint.h>

class connection_handler {
    public:
        virtual bool establish_connection(std::string hostname, uint16_t port) = 0;
        virtual bool shake_hands_start() = 0;
        virtual bool shake_hands_end() = 0;
        virtual bool close_connection() = 0;

        virtual bool read_message( message_buffer* buff ) = 0;
        virtual bool send_message( message_buffer* buff ) = 0;
    protected:
        std::string hostname_;
        uint16_t port_;
};

#endif /* CONNECTION_HANDLER_H */
