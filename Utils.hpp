#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstring>

using namespace std;

class Utils {
 public:
    static void computeMessage(char *message, const char *line);
    static char* basicExtractJsonResponse(char *str);
};

#endif