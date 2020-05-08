#include "../Server.hpp"
#include "Includes.hpp"

void Server::registerUser() {
    string username, password;
    getline(cin, username, '\n'); // Clear buffer
    cout << "Username = "; 
    getline(cin, username, '\n');
    cout << "Password = "; 
    getline(cin, password, '\n');
    openConnection();

    json registerJson = {
        { "username", username },
        { "password", password }
    };
    string registerJsonString = registerJson.dump();

    char *jsonString = new char[registerJsonString.length() + 1];
    strcpy(jsonString, registerJsonString.c_str());
    
    message = RequestHandler::POST(CONN_HOST, REGISTER_ROUTE, 
                                    APPLICATION_JSON_TYPE, NULL, NULL, 0,
                                    jsonString, NULL, 0);
    
    sendToServer(message);
    response = receiveFromServer();
    int statusCode = RequestHandler::getStatusCode(response);

    string errorJsonStr;
    json errorJson;

    switch (statusCode) {
        case 200:
            cout << "Registered successfully. Welcome, " << username << "!\n";
            break;
        case 201:
            cout << "Registered successfully. Welcome, " << username << "!\n";
            break;
        case 400:
            errorJsonStr = Utils::basicExtractJsonResponse(response);
            errorJson = json::parse(errorJsonStr); 
            cout << "ERROR: " << 
                errorJson.value("error", "Unknown error") << "\n";
            break;
        default:
            errorJsonStr = Utils::basicExtractJsonResponse(response);
            errorJson = json::parse(errorJsonStr); 
            cout << "ERROR: " << 
                errorJson.value("error", "Unknown error") << "\n";
            break;
    }

    delete [] jsonString;

    closeConnection();
}