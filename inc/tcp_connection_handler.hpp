#ifndef TCP_CONNECTION_HANLER_H
#define TCP_CONNECTION_HANDLER_H

#include <string>
#include <functional>
#include "connection_handler.hpp"
#include <stdint.h>

class tcp_connection_handler: public connection_handler {
    public:
        virtual bool establish_connection(std::string hostname, uint16_t port);
        virtual bool close_connection();

    protected:
        bool write_data(char* buff, size_t length);
        bool read_data(char* buff, size_t length);

    private:
        bool read_or_write_data(char* buff, size_t length, std::function<ssize_t (int, void*, size_t)> callback);
        int socket_;
};

#endif /* TCP_CONNECTION_HANDLER_H */
