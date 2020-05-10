#include "../Client.hpp"
#include "Includes.hpp"

void Client::enterLibrary() {
    openConnection();

    char **cookies = (char**)malloc(1 * sizeof(char*));
    cookies[0] = new char[sessionCookie.length() + 1];
    strcpy(cookies[0], sessionCookie.c_str());

    message = RequestHandler::GET(CONN_HOST, GET_LIBRARY_ACCESS_ROUTE, NULL, 
                                NULL, NULL, 0, cookies, 1);

    sendToServer(message);
    response = receiveFromServer();
    int statusCode = RequestHandler::getStatusCode(response);

    string jsonStr;
    json jsonVal;

    jsonStr = Utils::basicExtractJsonResponse(response);
    jsonVal = json::parse(jsonStr); 

    switch (statusCode) {
        case 200:
            accessToken = "Bearer " + jsonVal.value("token", "TokenUndefined");
            cout << "Access granted!\n";
            break;
        default:
            cout << "ERROR: " << 
                jsonVal.value("error", "Unknown error") << "\n";
            break;
    }

    delete [] cookies[0];
    delete [] cookies;

    closeConnection();
}