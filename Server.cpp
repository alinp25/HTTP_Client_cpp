#include "Server.hpp"
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

Server::Server() {
    isRunning = true;
}

void Server::run() {
    cout << "Server started...\n";
    string input;
    while (isRunning) {
        cout << "-------------------------------------------\n";
        cout << "> ";
        cin >> input;
        if (input == "exit") {
            isRunning = false;
            break;
        }
        if (input == "register") {
            if (sessionCookie.length() > 0) {
                cout << "You are logged in.\n";
                cout << "Please log out before you register a new account.\n";
                continue;
            } 
            registerUser();
            continue;
        }
        if (input == "login") {
            if (sessionCookie.length() > 0) {
                cout << "You are logged in.\n";
                cout << "To log in with another account please log out.\n";
                continue;
            }
            loginUser();
            continue;
        }
        if (input == "enter_library") {
            enterLibrary();
            continue;
        }
        if (input == "get_books") {
            getBooks();
            continue;
        }
        if (input == "get_book") {
            getBook();
            continue;
        }
        if (input == "add_book") {
            addBook();
            continue;
        }
        if (input == "delete_book") {
            deleteBook();
            continue;
        }
        if (input == "logout") {
            logoutUser();
            continue;
        }
    }
    cout << "-------------------------------------------\n";
    cout << "Exiting server...\n";
}



void Server::openConnection() {
    struct sockaddr_in serv_addr;
    socketFD = socket(CONN_IP_TYPE, CONN_SOCK_TYPE, CONN_FLAGS);
    if (socketFD < 0)
        cout << "ERROR opening socket\n";
    //     error("ERROR opening socket");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = CONN_IP_TYPE;
    serv_addr.sin_port = htons(CONN_PORT);
    inet_aton(CONN_HOST_IP, &serv_addr.sin_addr);

    if (connect(socketFD, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
        // error("ERROR connecting");
        cout << "ERROR connecting...\n";
}

void Server::closeConnection() {
    close(socketFD);
}

void Server::sendToServer(char *message) {
    int bytes, sent = 0;
    int total = strlen(message);

    do {
        bytes = write(socketFD, message + sent, total - sent);
        if (bytes < 0) {
            // error("ERROR writing message to socket");
            cout << "ERROR writing message to socket\n";
        }

        if (bytes == 0) {
            break;
        }

        sent += bytes;
    } while (sent < total);
}

char* Server::receiveFromServer() {
    char response[BUFLEN];
    Buffer buffer;
    int header_end = 0;
    int content_length = 0;
    do {
        int bytes = read(socketFD, response, BUFLEN);
        if (bytes < 0){
            // error("ERROR reading response from socket");
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
            // error("ERROR reading response from socket");
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