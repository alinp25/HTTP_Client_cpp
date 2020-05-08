#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <sys/socket.h>
#include <netinet/in.h> 
#include <netdb.h> 

#define CONN_IP_TYPE AF_INET
#define CONN_SOCK_TYPE SOCK_STREAM
#define CONN_FLAGS 0
#define CONN_PORT 8080
#define CONN_HOST_IP "3.8.116.10"
#define CONN_HOST "ec2-3-8-116-10.eu-west-2.compute.amazonaws.com"

#define REGISTER_ROUTE "/api/v1/tema/auth/register"
#define AUTH_ROUTE "/api/v1/tema/auth/login"
#define GET_LIBRARY_ACCESS_ROUTE "/api/v1/tema/library/access"
#define GET_BOOKS_SUMMARY_ROUTE "/api/v1/tema/library/books"
#define GET_BOOK_ROUTE "/api/v1/tema/library/books/"
#define POST_BOOK_ROUTE "/api/v1/tema/library/books"
#define DELETE_BOOK_ROUTE "/api/v1/tema/library/books/"
#define LOGOUT_ROUTE "/api/v1/tema/auth/logout"

#endif