#ifndef HANDSHAKER_H
#define HANDSHAKER_H

#include "connection_handler.hpp"

class handshaker {
    public:
        handshaker(connection_handler& connection): connection_(connection) {}

        virtual void start() = 0;
        virtual void end() = 0;
    protected:
        connection_handler& connection_;
};

#endif /* HANDSHAKER_H */
