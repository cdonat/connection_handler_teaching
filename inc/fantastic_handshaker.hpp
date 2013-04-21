#ifndef FANTASTIC_HANDSHAKER_H
#define FANTASTIC_HANDSHAKER_H

#include "handshaker.hpp"
#include "connection_handler.hpp"

class fantastic_handshaker: public handshaker {
    public:
        fantastic_handshaker(connection_handler& connection, std::string& username, std::string& password):
            handshaker(connection),
            username_(username),
            password_(password) {};

        virtual void start();
        virtual void end();
    private:
        void send_message(const char* msg, size_t l);
        bool expect_message(const char* msg, size_t l);

        std::string username_;
        std::string password_;
};

#endif /* FANTASTIC_HANDSHAKER_H */
