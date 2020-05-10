#include "RequestHandler.hpp"
#include "Utils.hpp"
#include "Constants.hpp"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>

char* RequestHandler::GET(const char *host, const char *url, 
                            char *query_params, char **headers, 
                            char **headersNames, int headersCount, 
                            char **cookies, int cookies_count) {

    char *message = (char*)calloc(BUFLEN, sizeof(char));
    char *line = (char*)calloc(LINELEN, sizeof(char));

    // Write the method name, URL, request params (if any) and protocol type
    if (query_params != NULL) {
        sprintf(line, "GET %s?%s HTTP/1.1", url, query_params);
    } else {
        sprintf(line, "GET %s HTTP/1.1", url);
    }

    Utils::computeMessage(message, line);

    sprintf(line, "Host: %s", host);
    Utils::computeMessage(message, line);

    // Add headers and/or cookies, according to the protocol format
    if (headers != NULL) {
        for (int i = 0; i < headersCount; i++) {
            sprintf(line, "%s: %s", headersNames[i], headers[i]);
            Utils::computeMessage(message, line);
        }
    }

    if (cookies != NULL) {
        for (int i = 0; i < cookies_count; i++) {
            sprintf(line, "Cookie: %s", cookies[i]);
            Utils::computeMessage(message, line);
        }
    }
    // Add final new line
    Utils::computeMessage(message, "");

    return message;
}

char* RequestHandler::POST(const char *host, const char *url, 
                        const char* content_type, char **headers, 
                        char **headersNames, int headersCount,
                        char *content, char **cookies, int cookies_count) {

    char *message = (char*)calloc(BUFLEN, sizeof(char));
    char *line = (char*)calloc(LINELEN, sizeof(char));
    
    // Write the method name, URL and protocol type
    sprintf(line, "POST %s HTTP/1.1", url);
    Utils::computeMessage(message, line);
    
    // Add the host
    sprintf(line, "Host: %s", host);
    Utils::computeMessage(message, line);

    /* Add necessary headers (Content-Type and Content-Length are mandatory)
        in order to write Content-Length you must first compute the message size
    */
    sprintf(line, "Content-Type: %s", content_type);
    Utils::computeMessage(message, line);
    sprintf(line, "Content-Length: %ld", strlen(content));
    Utils::computeMessage(message, line);

    // Add headers
    if (headers != NULL) {
        for (int i = 0; i < headersCount; i++) {
            sprintf(line, "%s: %s", headersNames[i], headers[i]);
            Utils::computeMessage(message, line);
        }
    }

    // Add cookies
    if (cookies != NULL) {
       for (int i = 0; i < cookies_count; i++) {
            sprintf(line, "Cookie: %s", cookies[i]);
            Utils::computeMessage(message, line);
        }
    }
    // Add new line at end of header
    Utils::computeMessage(message, "");

    // Step 6: add the actual payload data
    memset(line, 0, LINELEN);
    Utils::computeMessage(message, content);

    free(line);
    return message;
}

char* RequestHandler::DELETE(const char *host, const char *url, 
                            char *query_params, char **headers, 
                            char **headersNames, int headersCount, 
                            char **cookies, int cookies_count) {

    char *message = (char*)calloc(BUFLEN, sizeof(char));
    char *line = (char*)calloc(LINELEN, sizeof(char));

    // Write the method name, URL, request params (if any) and protocol type
    if (query_params != NULL) {
        sprintf(line, "DELETE %s?%s HTTP/1.1", url, query_params);
    } else {
        sprintf(line, "DELETE %s HTTP/1.1", url);
    }

    Utils::computeMessage(message, line);

    sprintf(line, "Host: %s", host);
    Utils::computeMessage(message, line);

    // Add headers and/or cookies, according to the protocol format
    if (headers != NULL) {
        for (int i = 0; i < headersCount; i++) {
            sprintf(line, "%s: %s", headersNames[i], headers[i]);
            Utils::computeMessage(message, line);
        }
    }

    if (cookies != NULL) {
        for (int i = 0; i < cookies_count; i++) {
            sprintf(line, "Cookie: %s", cookies[i]);
            Utils::computeMessage(message, line);
        }
    }
    // Add final new line
    Utils::computeMessage(message, "");
    return message;
}

int RequestHandler::getStatusCode(char *message) {
    string str(message);
    str.erase(0, strlen("HTTP/1.1 "));
    string statusCodeStr = str.substr(0, str.find(' '));
    return stoi(statusCodeStr);
}

string RequestHandler::getSessionCookie(char *message) {
    string str(message);
    str.erase(0, str.find("Set-Cookie: "));
    str.erase(0, strlen("Set-Cookie: "));
    str = str.substr(0, str.find(';'));
    return str;
}