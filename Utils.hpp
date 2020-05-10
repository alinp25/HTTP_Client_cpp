#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstring>
#include <string>

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

    /**
     * Check if a string represents a positive integer number
     * 
     * @param s String to check
     * @return bool that represents the truth-value
    */
    static bool isPositiveInteger(string s);
};

#endif