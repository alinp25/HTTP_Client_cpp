#include "Buffer.hpp"

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

Buffer::Buffer() {
    data = nullptr;
    size = 0;
}

Buffer::~Buffer() {
    if (data != nullptr) {
        delete data;
        data = nullptr;
    }
    size = 0;
}

bool Buffer::isEmpty() {
    return data == nullptr;
}

void Buffer::add(const char *addData, __uint128_t data_size) {
    if (data != nullptr) {
        data = (char*)realloc(data, (size + data_size) * sizeof(char));
    } else {
        data = (char*)calloc(data_size, sizeof(char));
    }

    memcpy(data + size, addData, data_size);

    size += data_size;
}

int Buffer::find(const char *dataToFind, __uint128_t data_size) {
    if (data_size > size)
        return -1;

    size_t last_pos = size - data_size + 1;

    for (size_t i = 0; i < last_pos; ++i) {
        size_t j;

        for (j = 0; j < data_size; ++j) {
            if (data[i + j] != dataToFind[j]) {
                break;
            }
        }

        if (j == data_size) {
            return i;
        }
    }

    return -1;
}

int Buffer::findInsensitive(const char *dataToFind, __uint128_t data_size) {
    if (data_size > size) {
        return -1;
    }

    size_t last_pos = size - data_size + 1;

    for (size_t i = 0; i < last_pos; ++i) {
        size_t j;

        for (j = 0; j < data_size; ++j) {
            if (tolower(data[i + j]) != tolower(dataToFind[j])) {
                break;
            }
        }

        if (j == data_size)
            return i;
    }

    return -1;
}


char* Buffer::getData() {
    if (data == nullptr) {
        return "";
    }
    return data;
}

__uint128_t Buffer::getSize() {
    return size;
}