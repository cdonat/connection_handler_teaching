#ifndef TCP_CONNECTION_HANLER_H
#define TCP_CONNECTION_HANDLER_H

#include <string>
#include <functional>
#include <exception>
#include "connection_handler.hpp"
#include <stdint.h>

class read_write_failure: public std::exception {
    public:
        read_write_failure(std::string what): what_(what) {};
        virtual const char* what() const noexcept {
            return what_.c_str();
        };
    private:
        std::string what_;
};


class tcp_connection_handler: public connection_handler {
    public:
        virtual void establish_connection(std::string hostname, uint16_t port);
        virtual void close_connection();

    protected:
        void write_data(char* buff, size_t length);
        void read_data(char* buff, size_t length);

    private:
        void read_or_write_data(char* buff, size_t length, std::function<ssize_t (int, void*, size_t)> callback);
        int socket_;
};

// a simple helper function makes code better readable
inline void throw_on_error( bool do_throw ) {
    if( do_throw ) {
        std::string what = strerror(errno);
        throw read_write_failure(what);
    }
}

#endif /* TCP_CONNECTION_HANDLER_H */
