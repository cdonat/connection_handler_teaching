#ifndef TCP_CONNECTION_HANDLER_H
#define TCP_CONNECTION_HANDLER_H

#include <stdint.h>

#include <string>
#include <functional>

#include "connection_handler.hpp"

class tcp_connection_handler: public connection_handler {
    public:
        tcp_connection_handler(std::string hostname, uint16_t port);
        virtual ~tcp_connection_handler();

    protected:
        void write_data(char* buff, size_t length);
        void read_data(char* buff, size_t length);

    private:
        void read_or_write_data(char* buff, size_t length, std::function<ssize_t (int, void*, size_t)> callback);
        int socket_;
};

#endif /* TCP_CONNECTION_HANDLER_H */
