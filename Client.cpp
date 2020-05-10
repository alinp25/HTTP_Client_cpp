#include "Client.hpp"
#include "Utils.hpp"
#include "Connection.hpp"
#include "Buffer.hpp"
#include "Constants.hpp"
#include "RequestHandler.hpp"
#include "RequestConstants.hpp"

#include <iostream>
#include <string>
#include <string.h>
#include <arpa/inet.h>

#include "nlohmann/json.hpp"


using namespace std;
using json = nlohmann::json;

Client::Client() {
    isRunning = true;
}

void Client::run() {
    cout << "Client started...\n";
    string input;
    while (isRunning) {
        // Retrieve the user input
        cout << "-------------------------------------------\n";
        cout << "> ";
        cin >> input;
        // Handle the input 
        if (input == "exit") {
            isRunning = false;
            break;
        }
        if (input == "register") {
            // Available only if there is no user logged in at the moment
            if (sessionCookie.length() > 0) {
                cout << "You are logged in.\n";
                cout << "Please log out before you register a new account.\n";
                continue;
            } 
            registerUser();
            continue;
        }
        if (input == "login") {
            // Available only if there is no user logged in at the moment
            if (sessionCookie.length() > 0) {
                cout << "You are logged in.\n";
                cout << "To log in with another account please log out.\n";
                continue;
            }
            loginUser();
            continue;
        }
        if (input == "enter_library") {
            if (sessionCookie.empty()) {
                cout << "Please log in first.\n";
                continue;
            }
            enterLibrary();
            continue;
        }
        if (input == "get_books") {
            if (accessToken.empty()) {
                cout << "Please enter library first. (Hint: enter_library)\n";
                continue;
            }
            getBooks();
            continue;
        }
        if (input == "get_book") {
            if (accessToken.empty()) {
                cout << "Please enter library first. (Hint: enter_library)\n";
                continue;
            }
            getBook();
            continue;
        }
        if (input == "add_book") {
            if (accessToken.empty()) {
                cout << "Please enter library first. (Hint: enter_library)\n";
                continue;
            }
            addBook();
            continue;
        }
        if (input == "delete_book") {
            if (accessToken.empty()) {
                cout << "Please enter library first. (Hint: enter_library)\n";
                continue;
            }
            deleteBook();
            continue;
        }
        if (input == "logout") {
            logoutUser();
            continue;
        }
        cout << "Command not found\n";
    }
    cout << "-------------------------------------------\n";
    cout << "Exiting client...\n";
}



void Client::openConnection() {
    struct sockaddr_in serv_addr;
    socketFD = socket(CONN_IP_TYPE, CONN_SOCK_TYPE, CONN_FLAGS);
    if (socketFD < 0) {
        cout << "ERROR opening socket\n";
        return ;
    }

    // Setting the serv_addr content to the desired connection
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = CONN_IP_TYPE;
    serv_addr.sin_port = htons(CONN_PORT);
    inet_aton(CONN_HOST_IP, &serv_addr.sin_addr);

    if (connect(socketFD, (struct sockaddr*)&serv_addr, 
                                                    sizeof(serv_addr)) < 0) {
        cout << "ERROR connecting...\n";
        return ;
    }
}

void Client::closeConnection() {
    close(socketFD);
}

void Client::sendToServer(char *message) {
    int bytes, sent = 0;
    int total = strlen(message);

    do {
        bytes = write(socketFD, message + sent, total - sent);
        if (bytes < 0) {
            cout << "ERROR writing message to socket\n";
        }

        if (bytes == 0) {
            break;
        }

        sent += bytes;
    } while (sent < total);
}

char* Client::receiveFromServer() {
    char response[BUFLEN];
    Buffer buffer;
    int header_end = 0;
    int content_length = 0;

    do {
        int bytes = read(socketFD, response, BUFLEN);
        if (bytes < 0) {
            cout << "ERROR reading response from socket\n";
        }
        if (bytes == 0) {
            break;
        }

        buffer.add(response, bytes);
        
        header_end = buffer.find(HEADER_TERMINATOR, HEADER_TERMINATOR_SIZE);

        if (header_end >= 0) {
            header_end += HEADER_TERMINATOR_SIZE;
            
            int content_length_start = buffer.findInsensitive(CONTENT_LENGTH, 
                                                        CONTENT_LENGTH_SIZE);
            
            if (content_length_start < 0) {
                continue;           
            }

            content_length_start += CONTENT_LENGTH_SIZE;
            content_length = strtol(buffer.getData() + content_length_start, 
                                                                    NULL, 10);
            break;
        }
    } while (1);

    size_t total = content_length + (size_t) header_end;

    while (buffer.getSize() < total) {
        int bytes = read(socketFD, response, BUFLEN);

        if (bytes < 0) {
            cout << "ERROR reading response from socket\n";
        }

        if (bytes == 0) {
            break;
        }

        buffer.add(response, bytes);
    }
    
    buffer.add("", 1);
    return strdup(buffer.getData());
}