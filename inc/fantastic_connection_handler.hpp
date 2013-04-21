#ifndef FANTASTIC_CONNECTION_HANDLER_H
#define FANTASTIC_CONNECTION_HANDLER_H

#include "tcp_connection_handler.hpp"

class fantastic_connection_handler: public tcp_connection_handler {
    public:
        virtual void read_message( message_buffer* buff );
        virtual void send_message( message_buffer* buff );
        virtual bool shake_hands_start();
        virtual bool shake_hands_end();

    private:
        void send_message(const char* msg, size_t l);
        bool expect_message(const char* msg, size_t l);

};

#endif /* FANTASTIC_CONNECTION_HANDLER_H */
