#include "../Client.hpp"
#include "Includes.hpp"

void Client::getBooks() {
    openConnection();

    char **headers = (char**)malloc(1 * sizeof(char*));
    char **headersNames = (char**)malloc(1 * sizeof(char*));
    headers[0] = new char[accessToken.length() + 1];
    headersNames[0] = new char[strlen("Authorization")];
    strcpy(headersNames[0], "Authorization");
    strcpy(headers[0], accessToken.c_str());

    message = RequestHandler::GET(CONN_HOST, GET_BOOKS_SUMMARY_ROUTE, NULL,
                                headers, headersNames, 1, NULL, 0);

    sendToServer(message);
    response = receiveFromServer();
    int statusCode = RequestHandler::getStatusCode(response);

    string jsonStr;
    json jsonVal; 

    string responseValue;

    switch (statusCode) {
        case 200:
            jsonStr = Utils::basicExtractJsonResponse(response);
            responseValue = "[" + string(jsonStr);
            cout << responseValue << "\n";
            break;
        default:
            jsonStr = Utils::basicExtractJsonResponse(response);
            jsonVal = json::parse(jsonStr);
            cout << "ERROR: " << 
                jsonVal.value("error", "Unknown error") << "\n";
            break;
    }

    delete [] headers[0];
    delete [] headersNames[0];
    delete [] headers;
    delete [] headersNames;

    closeConnection();
}