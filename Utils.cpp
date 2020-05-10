#include "Utils.hpp"

#include <algorithm>

using namespace std;

void Utils::computeMessage(char *message, const char *line) {
    strcat(message, line);
    strcat(message, "\r\n");
}

char* Utils::basicExtractJsonResponse(char *str) {
    return strstr(str, "{\"");
}

bool Utils::isPositiveInteger(string s) {
    return !s.empty() && s.find_first_not_of("0123456789") == std::string::npos;
}