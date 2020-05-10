#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <sys/socket.h>
#include <netinet/in.h> 
#include <netdb.h>     
#include <unistd.h>
#include <string>

using namespace std;

class Client {
public:
    /**
     * Instantiates the client
     */
    Client();

    /**
     * Executes a loop for handling the user input and treating the case for
     * each type of input command
     */
    void run();
private:
    bool isRunning;
    int socketFD;

    string sessionCookie;
    string accessToken;

    char *message;
    char *response;

    /**
     * Executes and handles the <register> command
     */
    void registerUser();

    /**
     * Executes and handles the <login> command
     */
    void loginUser();

    /**
     * Executes and handles the <enter_library> command
     */
    void enterLibrary();

    /**
     * Executes and handles the <get_books> command
     */
    void getBooks();

    /**
     * Executes and handles the <get_book> command
     */
    void getBook();

    /**
     * Executes and handles the <add_book> command
     */
    void addBook();

    /**
     * Executes and handles the <delete_book> command
     */
    void deleteBook();

    /**
     * Executes and handles the <logout> command
     */
    void logoutUser();

    /**
     * Executes the connection closing
     */
    void closeConnection();

    /**
     * Executes the connection opening
     */
    void openConnection();

    /**
     * Send a message to the server
     * 
     * @param message the desired message to be sent to the server
     */
    void sendToServer(char *message);

    /**
     * Receives a message from the server 
     * 
     * @return the message received from the server
     */
    char *receiveFromServer();
};

#endif