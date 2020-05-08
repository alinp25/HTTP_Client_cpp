#ifndef REQUEST_HANDLER_HPP
#define REQUEST_HANDLER_HPP

#include <string>

using namespace std;

class RequestHandler {
 public:
    static char* GET(char *host, char *url, char *query_params, char **headers, 
                    char **headersNames, int headersCount, char **cookies, 
                    int cookies_count);
    static char* POST(char *host, char *url, char* content_type, 
                        char **headers, char **headersNames, int headersCount,
                        char *content, char **cookies, int cookies_count);
    static char* DELETE(char *host, char *url, char *query_params, 
                        char **headers, char **headersNames, int headersCount, 
                        char **cookies, int cookies_count);
    static int getStatusCode(char *message);
    static string getSessionCookie(char *message);
};

#endif  