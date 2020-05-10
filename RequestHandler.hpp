#ifndef REQUEST_HANDLER_HPP
#define REQUEST_HANDLER_HPP

#include <string>

using namespace std;

class RequestHandler {
 public:
    /***
     * Builds up the GET request based on the query params, headers and cookies
     * 
     * @param host Connection's host URL
     * @param url Route for the request
     * @param queryParams String of query parameters
     * @param headers Array of headers stored as strings
     * @param headersNames Corresponding header names array for the headers array
     * @param headersCount The number of headers
     * @param cookies Array of cookies stored as strings
     * @param cookies_count The number of cookies
     * 
     * @return The GET request as a string
     */
    static char* GET(const char *host, const char *url, char *query_params, char **headers, 
                    char **headersNames, int headersCount, char **cookies, 
                    int cookies_count);

    /***
     * Builds up the POST request based on the query params, headers and cookies
     * 
     * @param host Connection's host URL
     * @param url Route for the request
     * @param content_type The content type as string
     * @param headers Array of headers stored as strings
     * @param headersNames Corresponding header names array for the headers array
     * @param headersCount The number of headers
     * @param cookies Array of cookies stored as strings
     * @param cookies_count The number of cookies
     * 
     * @return The POST request as a string
     */
    static char* POST(const char *host, const char *url, const char* content_type, 
                        char **headers, char **headersNames, int headersCount,
                        char *content, char **cookies, int cookies_count);

    /***
     * Builds up the DELETE request based on the query params, headers and cookies
     * 
     * @param host Connection's host URL
     * @param url Route for the request
     * @param queryParams String of query parameters
     * @param headers Array of headers stored as strings
     * @param headersNames Corresponding header names array for the headers array
     * @param headersCount The number of headers
     * @param cookies Array of cookies stored as strings
     * @param cookies_count The number of cookies
     * 
     * @return The DELETE request as a string
     */
    static char* DELETE(const char *host, const char *url, char *query_params, 
                        char **headers, char **headersNames, int headersCount, 
                        char **cookies, int cookies_count);

    /***
     * Retrieve the status code from the response
     * 
     * @param message The response as string
     * 
     * @return The status code
     */
    static int getStatusCode(char *message);

    /***
     * Retrieve the session cookie as string from the log in request
     * 
     * @param message The response as string
     * 
     * @return The session cookie as string
     */
    static string getSessionCookie(char *message);
};

#endif  