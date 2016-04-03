#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#pragma comment(lib, "ws2_32.lib")

#define NO_FLAGS_SET 0
#define PORT 80
#define MAXBUFLEN 20480 // How much is printed out to the screen

SOCKET socket_new(void);
void connect_to_server(SOCKET recvSocket, SOCKADDR_IN recvSockAddr);
void send_initial_request(SOCKET recvSocket, const char* host_name);
void send_secret_request(SOCKET recvSocket, char* host_name, char* buffer);
void receive_response(SOCKET recvSocket, char* buffer);
void inverse_str(char* buffer);
void send_post(SOCKET recvSocket, char* host_name, char * data);
#endif // FUNC_H_INCLUDED
