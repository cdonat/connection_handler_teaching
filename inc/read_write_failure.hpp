#ifndef READ_WRITE_FAILURE_H
#define READ_WRITE_FAILURE_H

#include <exception>

class read_write_failure: public std::exception {
    public:
        read_write_failure(std::string what): what_(what) {};
        virtual const char* what() const noexcept {
            return what_.c_str();
        };
    private:
        std::string what_;
};

// a simple helper function makes code better readable
inline void throw_on_error( bool do_throw ) {
    if( do_throw ) {
        std::string what = strerror(errno);
        throw read_write_failure(what);
    }
}


#endif /* READ_WRITE_FAILURE_H */
