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

    char *jsonResponse;
    json jsonVal; 

    string responseValue;

    switch (statusCode) {
        case 200:
            jsonResponse = Utils::basicExtractJsonResponse(response);
            if (!jsonResponse) {
                cout << "No books found in your library.\n";
                break;
            }
            responseValue = "[" + string(jsonResponse);
            cout << responseValue << "\n";
            break;
        default:
            jsonResponse = Utils::basicExtractJsonResponse(response);
            jsonVal = json::parse(string(jsonResponse));
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