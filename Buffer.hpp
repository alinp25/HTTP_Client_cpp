#ifndef BUFFER_HPP
#define BUFFER_HPP


/**
 * The Buffer class consists of a string and it's size.
 * It is used inside the request builders and the request sending/receive
 * for building the buffer, searching and concatenating messages.
*/
class Buffer {
 public:
    /**
     * Instantiates the buffer
     */
    Buffer();

    /**
     * Destroy the buffer and empty its allocated memory
     */
    ~Buffer();

    /**
     * Concatenate a string to the current buffer
     */
    void add(const char *data, __uint128_t data_size);

    /**
     * Check if the buffer is empty
     * 
     * @return the buffer's emptiness value
     */
    bool isEmpty();

    /**
     * Searches the buffer for a string
     * 
     * @param data the string to search for
     * @param data_size string's size
     * 
     * @return position of the substring if found, -1 if not found
     */
    int find(const char *data, __uint128_t data_size);

    /**
     * Searches the buffer for a string, not keeping track of capital letters
     * 
     * @param data the string to search for
     * @param data_size string's size
     * 
     * @return position of the substring if found, -1 if not found
     */
    int findInsensitive(const char *data, __uint128_t data_size);

    /**
     * Get the buffer's content as string
     * 
     * @return buffer
     */
    char *getData();

    /**
     * Get the buffer's size
     * 
     * @return buffer size
     */
    __uint128_t getSize();
 private:
    char *data;
    __uint128_t size;
};

#endif