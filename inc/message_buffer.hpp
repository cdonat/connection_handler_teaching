#ifndef MESSAGE_BUFFER_H
#define MESSAGE_BUFFER_H

// C includes
#include <string.h>

// C++ includes
#include <utility>

/** a simple container holding messages
 *
 * all functions are inline here to improve performance
 *
 * @ author Christof Donat
 */
class message_buffer {
    public:
        /** construct a message buffer from its components
         *
         * @param buffer    points to a memory area with data to copy into 
         *                  the buffer
         * @param size      the number of bytes copied ti the buffer
         */
        message_buffer(const char* buffer, const size_t size);

        /** construct an empty message buffer with defined size
         *
         * @param size      the number of bytes allocated for the buffer
         */
        message_buffer(const size_t size);

        /** construct a message buffer from a string§
         *
         * @param other     will copy the contents of the string to the new 
         *                  buffer
         */
        message_buffer(std::string& other);

        /** construct a message from a null terminated C-string
         *
         * @param other     a null terminated C-string that the buffer will
         *                  initialized with
         */
        message_buffer(const char* other);

        /** copy constructor
         *
         * @param other     copy data from here
         */
        message_buffer(message_buffer& other);

        /** move constructor - note this will only work with C++11 compliant 
         *  compilers
         *
         * @param other     move data from here
         */
        message_buffer(message_buffer&& other);

        /** destructor */
        virtual ~message_buffer();


        /** assign value from other message buffer
         *
         * this uses the "copy and swap" idiom to 
         * 1. make sure that move semantics is used where possible and 
         * 2. clean up eventual old data
         *
         * @param other     get data from here
         * @returns         reference to this after assignment
         */
        message_buffer& operator=(message_buffer other);

        /** assign value from std::string
         *
         * this uses the "copy and swap" idiom
         *
         * @param other     get data from here
         * @returns         reference to this after assignment
         */
        message_buffer& operator=(std::string& other);

        /** assign value from null terminated C-string
         *
         * this uses the "copy and swap" idiom
         *
         * @param other     get data from here
         * @returns         reference to this after assignment
         */
        message_buffer& operator=(const char* other);

        /** assign value from memory area and size
         *
         * this uses the "copy and swap" idiom
         *
         * @param other     get data from here
         * @returns         reference to this after assignment
         */
        void set(const char* other, size_t size);


        /** swap contents of two message buffers
         */
        void swap(message_buffer& other);


        /** get the size of the buffer
         *
         * @returns         size of the buffer
         */
        const size_t size() const;
        /** get the content of the buffer
         *
         * @returns         pointer to the buffers content
         */
        char* buffer() const;
    private:
        size_t size_;
        char* buffer_;
};


namespace std
{
    /** specialization of std::swap for message buffers
     *
     * @param left      object to swap contents of parameter "right" with
     * @param right     object to swap contents of parameter "left" with
     */
    template<> inline void swap(message_buffer& left, message_buffer& right)
    { left.swap(right); }
}


inline message_buffer::message_buffer(const char* buffer, const size_t size):
    size_(size),
    buffer_(0) {
        buffer_ = new char[size_];
        memcpy(buffer_, buffer, size_);
};


inline message_buffer::message_buffer(const size_t size):
    size_(size),
    buffer_(0) {
        buffer_ = new char[size_];
};


inline message_buffer::message_buffer(std::string& other):
    size_(other.size()),
    buffer_(0) {
        buffer_ = new char[size_];
        memcpy(buffer_, other.c_str(), size_);
};


inline message_buffer::message_buffer(const char* other):
    size_(strlen(other)),
    buffer_(0) {
        buffer_ = new char[size_];
        memcpy(buffer_, other, size_);
};


inline message_buffer::message_buffer(message_buffer& other):
    size_(other.size_),
    buffer_(0) {
        buffer_ = new char[size_];
        memcpy(buffer_, other.buffer_, size_);
};


inline message_buffer::message_buffer(message_buffer&& other):
    size_(other.size_),
    buffer_(other.buffer_) {
        other.buffer_ = nullptr;
        other.size_ = 0;
};


inline message_buffer::~message_buffer() {
    delete[] buffer_;
};


inline message_buffer& message_buffer::operator=(message_buffer other) {
    std::swap(*this, other);
    return *this;
};


inline message_buffer& message_buffer::operator=(std::string& other) {
    message_buffer b(other);
    std::swap(*this, b);
    return *this;
};


inline message_buffer& message_buffer::operator=(const char* other) {
    message_buffer b(other);
    std::swap(*this, b);
    return *this;
};


inline void message_buffer::set(const char* other, size_t size) {
    message_buffer b(other, size);
    std::swap(*this, b);
};


inline void message_buffer::swap(message_buffer& other) {
    std::swap(size_, other.size_);
    std::swap(buffer_, other.buffer_);
};


inline const size_t message_buffer::size() const {
    return size_;
};


inline char* message_buffer::buffer() const {
    return buffer_;
};


#endif /* MESSAGE_BUFFER_H */

