# HTTP Client Homework - Communication Protocols (ACS, UPB)

#### _Student: Pisica Alin-Georgian | Year 2, 324CC_

## 1. Homework goal

- understanding the HTTP comunication mechanisms
- interaction with a REST API
- understanding notions about JSONs and JWTs
- using external libraries for handling JSONs

## 2. Homework description

Implement a C++ client that interacts with a server. The server expose a REST API and simulates an online library. The client accepts user input and sends requests and handles responses from the server. Client's goal is to work like a interface for the virtual library.

## 3. Implementation

### 3.1 Client-Server Connection

The connection details are stored in the _Connection.hpp_ file and the connection handling (opening and closing) are done in the _Client_ itself (closeConnection, openConnection methods). 

The connection is handled through a Socket File Descriptor that is stored as private information inside the client.

### 3.2 The Client-Server interaction

Since the client is going to act like an interface between the user and the server, I structured the interaction with it as a continuous loop of user-input-awaiting, where each action is triggered by one of the following commands:

* **register**
    * handles a registration
    * if the user tries accessing the command while logged in, he will be prompted with an error message
    * if the register process starts succesfully the user is prompted to choose an username and a password

* **login**
    * handles a login process
    * if the user tries accessing the command while being already logged in, he will be prompted with an error message
    * if the login process starts succesfully the user is prompted to enter his credentials

* **enter_library**
    * the enter_library command should be executed after the login process, to gain access in the library (it provides de JWT Token needed for the Authorization to be successful)

* **get_books**
    * returns a list of all the user's books

* **get_book**
    * the user is prompted to enter an id, then a json containing all the book's details are provided

* **add_book**
    * inserts a new book into the library
    * prompts the user with input fields for title, author, genre, publisher and page count

* **delete_book**
    * delete a book based on an id that the user is prompted to provide

* **logout**
    * logs out the user from the system

* **exit**
    * closes the client

The error handling for input is done right into the client, but if there appear any server-errors (like duplicate book names, strings too long, wrong username and password) we expect the server to provide them in a not-OK response status, together with the error message in a JSON as `{error: 'Error message'}`. All the erors are prompted to the user, the client not failing on receiving any error message or wrong input.

### 3.3 JSON Handling

The JSON handling is done using the [_nlohmann_ library](https://github.com/nlohmann/json). Even though, retrieving the JSON from the request's response is done using the method _basicExtractJsonResponse_ implemented in _Utils_ that simply queries the string, returning the position of the first JSON string (that, happily, is situated at the end of the response, so no other text that can bother us is following it). 

The library was used for creating the JSONs needed for the POST requests and also for extracting the fields (error fields mostly) from the JSONs received as request responses.

### 3.4 Project structure

The project consists of 4 main classes: _Client, Buffer, Utils, RequestHandler_, that are situated in the parent folder. The _nlohmann_ folder contains the JSON library presented at the previous point. The Commands folder contains the implementations for all the commands provided for the user through the client interface.

Each method has a short documentation of it's action, parameters and return type. The methods are pretty self-explanatory by their name, and their implementation is not something that tends to rocket-sience that needs to be explained, it can be easily understood from the code.

## 4. Running the project

Running the project can be done by compiling the source code using the &nbsp; `make` command, followed by running the client using &nbsp; `./client`.

The build's output is generated in the _build_ folder, while in the source folder will be created a sym-link to the `client` executable. 

## 5. References

1. https://ocw.cs.pub.ro/courses/pc/laboratoare/10
2. https://developer.mozilla.org/en-US/docs/Web/HTTP/Overview
3. https://restfulapi.net/