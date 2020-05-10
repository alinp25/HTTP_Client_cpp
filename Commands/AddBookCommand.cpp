#include "../Client.hpp"
#include "Includes.hpp"

void Client::addBook() {
    string title, author, genre, publisher, pageCountStr;
    int pageCount;
    getline(cin, title, '\n'); // Clear buffer
    cout << "Title = "; 
    getline(cin, title, '\n');
    cout << "Author = "; 
    getline(cin, author, '\n');
    cout << "Genre = "; 
    getline(cin, genre, '\n');
    cout << "Publisher = "; 
    getline(cin, publisher, '\n');
    cout << "Page count (positive number) = "; 
    cin >> pageCountStr;

    if (Utils::isPositiveInteger(pageCountStr) == false) {
        cout << "The page count should be a positive number.\n";
        return;
    }

    pageCount = stoi(pageCountStr);

    char **headers = (char**)malloc(1 * sizeof(char*));
    char **headersNames = (char**)malloc(1 * sizeof(char*));
    headers[0] = new char[accessToken.length() + 1];
    headersNames[0] = new char[strlen("Authorization")];
    strcpy(headersNames[0], "Authorization");
    strcpy(headers[0], accessToken.c_str());

    openConnection();

    json newBookJson = {
        { "title", title },
        { "author", author },
        { "genre", genre },
        { "publisher", publisher },
        { "page_count", pageCount }
    };
    string newBookPayload = newBookJson.dump();

    char *payload = new char[newBookPayload.length() + 1];
    strcpy(payload, newBookPayload.c_str());
    
    message = RequestHandler::POST(CONN_HOST, POST_BOOK_ROUTE, 
                                    APPLICATION_JSON_TYPE, 
                                    headers, headersNames, 1,
                                    payload, NULL, 0);
    
    sendToServer(message);
    response = receiveFromServer();
    int statusCode = RequestHandler::getStatusCode(response);

    string errorJsonStr;
    json errorJson;

    switch (statusCode) {
        case 200:
            cout << "Book added successfully" << "\n";
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
            break;
    }

    delete [] headers[0];
    delete [] headersNames[0];
    delete [] headers;
    delete [] headersNames;
    delete [] payload;

    closeConnection();
}