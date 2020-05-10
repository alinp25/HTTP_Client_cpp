#include "../Client.hpp"
#include "Includes.hpp"

void Client::getBook() {
    int id;
    cout << "Book id = "; cin >> id;
    openConnection();

    char **headers = (char**)malloc(1 * sizeof(char*));
    char **headersNames = (char**)malloc(1 * sizeof(char*));
    headers[0] = new char[accessToken.length() + 1];
    headersNames[0] = new char[strlen("Authorization")];
    strcpy(headersNames[0], "Authorization");
    strcpy(headers[0], accessToken.c_str());

    string bookRouteStr = GET_BOOK_ROUTE + to_string(id);
    char *bookRoute = new char[bookRouteStr.length() + 1];
    strcpy(bookRoute, bookRouteStr.c_str());

    message = RequestHandler::GET(CONN_HOST, bookRoute, NULL,
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
            cout << jsonStr << "\n";
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
    delete [] bookRoute;

    closeConnection();
}