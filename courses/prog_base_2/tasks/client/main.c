#include "func.h"
int main(void) {
    WSADATA Data;
    SOCKADDR_IN recvSockAddr;
    SOCKET recvSocket;
    int status;
    int numrcv = 0;
    struct hostent * remoteHost;
    char * ip;
    const char * host_name = "pb-homework.appspot.com";
    char * buffer = malloc(sizeof(char) * MAXBUFLEN);;
    memset(buffer,0,MAXBUFLEN);
    // Initialize Windows Socket DLL
    status = WSAStartup(MAKEWORD(2, 2), &Data);
    if(status != 0)
    {
        printf("ERROR: WSAStartup unsuccessful\r\n");
        return 0;
    }
	// Get IP address from host name
	remoteHost = gethostbyname(host_name);
	ip = inet_ntoa(*(struct in_addr *)*remoteHost->h_addr_list);
	printf("IP address is: %s.\n", ip);
    memset(&recvSockAddr, 0, sizeof(recvSockAddr)); // zero the sockaddr_in structure
    recvSockAddr.sin_port=htons(PORT); // specify the port portion of the address
    recvSockAddr.sin_family=AF_INET; // specify the address family as Internet
    recvSockAddr.sin_addr.s_addr= inet_addr(ip); // specify ip address
	// Create socket
	recvSocket = socket_new();
    // Connect
    connect_to_server(recvSocket, recvSockAddr);
    // Send request
    send_initial_request(recvSocket, host_name);
    receive_response(recvSocket, buffer);
    // Receieve
    printf("%s\r\n", buffer);
    send_secret_request(recvSocket, host_name, buffer);
    // Get and make
    free(buffer);
    buffer = malloc(sizeof(char) * MAXBUFLEN);
    receive_response(recvSocket, buffer);
    printf("%s\r\n", buffer);
    inverse_str(buffer);
    // Send
    send_post(recvSocket, host_name, buffer);
    // Get answer
    free(buffer);
    buffer = malloc(sizeof(char) * MAXBUFLEN);
    receive_response(recvSocket, buffer);
	printf("\nServer response:\n\n%s\n", buffer);
	closesocket(recvSocket);
	getchar();

	// Print out receieved socket data

    system("pause");
    return 0;
}
