#ifndef FANTASTIC_CONNECTION_HANDLER_H
#define FANTASTIC_CONNECTION_HANDLER_H

#include "tcp_connection_handler.hpp"

class fantastic_connection_handler: public tcp_connection_handler {
    public:
        fantastic_connection_handler(std::string hostname, uint16_t port);
        virtual ~fantastic_connection_handler();

        virtual void read_message( message_buffer* buff );
        virtual void send_message( message_buffer* buff );
 
    private:
        void send_message(const char* msg, size_t l);
        bool expect_message(const char* msg, size_t l);
        void shake_hands_start();
        void shake_hands_end();

};

#endif /* FANTASTIC_CONNECTION_HANDLER_H */
