#include "Utils.hpp"

using namespace std;

/**
 * Concatenates a line to the message
 *
 * @param message The initial message
 * @param line The line that is being appended to the message
 */
void Utils::computeMessage(char *message, const char *line) {
    strcat(message, line);
    strcat(message, "\r\n");
}

/**
 * Extracts a pointer to the beginning of the JSON
 *
 * @param message The initial message
 * @param line The line that is being appended to the message
 */
char* Utils::basicExtractJsonResponse(char *str) {
    return strstr(str, "{\"");
}
