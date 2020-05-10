#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstring>

using namespace std;

class Utils {
 public:
    /**
     * Concatenates a line to the message
     *
     * @param message The initial message
     * @param line The line that is being appended to the message
     */
    static void computeMessage(char *message, const char *line);

    /**
     * Extracts a pointer to the beginning of the JSON from the string
     *
     * @param message The initial message
     * @param line The line that is being appended to the message
     * @return pointer at the beginning of the JSON
     */
    static char* basicExtractJsonResponse(char *str);
};

#endif