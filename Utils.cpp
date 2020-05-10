#include "Utils.hpp"

using namespace std;

void Utils::computeMessage(char *message, const char *line) {
    strcat(message, line);
    strcat(message, "\r\n");
}

char* Utils::basicExtractJsonResponse(char *str) {
    return strstr(str, "{\"");
}
