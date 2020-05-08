#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/socket.h>
#include <netinet/in.h> 
#include <netdb.h>     
#include <unistd.h>
#include <string>

using namespace std;

class Server {
public:
    Server();
    void run();
private:
    bool isRunning;
    int socketFD;

    string sessionCookie;
    string accessToken;

    char *message;
    char *response;

    void registerUser();
    void loginUser();
    void enterLibrary();
    void getBooks();
    void getBook();
    void addBook();
    void deleteBook();
    void logoutUser();

    void closeConnection();
    void openConnection();
    void sendToServer(char *message);
    char *receiveFromServer();
};

#endif