#ifndef BUFFER_HPP
#define BUFFER_HPP


class Buffer {
 public:
   Buffer();
   ~Buffer();
   void add(const char *data, __uint128_t data_size);
   bool isEmpty();
   int find(const char *data, __uint128_t data_size);
   int findInsensitive(const char *data, __uint128_t data_size);
   char *getData();
   __uint128_t getSize();
 private:
   char *data;
   __uint128_t size;
};

#endif