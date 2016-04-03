#include "func.h"
SOCKET socket_new(void){
	SOCKET recvSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (recvSocket == INVALID_SOCKET)
	{
		printf("ERROR: socket unsuccessful\r\n");
		system("pause");
		exit(EXIT_FAILURE);
	}
	return recvSocket;
}

void connect_to_server(SOCKET recvSocket, SOCKADDR_IN recvSockAddr){
	if (connect(recvSocket, (SOCKADDR*)&recvSockAddr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		printf("ERROR: socket could not connect\r\n");
		closesocket(recvSocket);
		WSACleanup();
		exit(EXIT_FAILURE);
	}
}

void send_initial_request(SOCKET recvSocket, const char* host_name){
	char request[500];
	sprintf(request, "GET /var/12 HTTP/1.1\r\nHost:%s\r\n\r\n", host_name);  // add Host header with host_name value
	send(recvSocket, request, strlen(request), 0);
}
void send_secret_request(SOCKET recvSocket, char* host_name, char* buffer){
	char secret[50];
	char request[200];
	strcpy(secret, strstr(buffer, "secret"));
	sprintf(request, "GET /var/12?%s HTTP/1.1\r\nHost:%s\r\n\r\n", secret, host_name);
	send(recvSocket, request, strlen(request), 0);
}
void receive_response(SOCKET recvSocket, char* buffer){
    int numrcv = recv(recvSocket, buffer, MAXBUFLEN, NO_FLAGS_SET);
    if (numrcv == SOCKET_ERROR)
    {
        printf("ERROR: recvfrom unsuccessful\r\n");
        int status = closesocket(recvSocket);
        if(status == SOCKET_ERROR)
			printf("ERROR: closesocket unsuccessful\r\n");
        status = WSACleanup();
        if (status == SOCKET_ERROR)
			printf("ERROR: WSACleanup unsuccessful\r\n");
        system("pause");
        return(1);
    }
}
void inverse_str(char* buffer)
{
    int len, n;
    char * str = strstr(buffer, "Content-Length: ");
    sscanf(str, "Content-Length: %d", &len);
    sprintf(buffer, "Content-Length: %d\n\n\0", len);
    n = strlen(str);
    for (int i = 0; i < n - strlen(buffer); i++)
        str[i] = str[i + strlen(buffer) + 2];
    str[len] = '\0';
    puts(str);
    for (int i = 0; i < len; i++)
        buffer[i] = str[len - i - 1];
    buffer[len] = '\0';
    sprintf(str, "result=%s", buffer);
    strcpy(buffer ,str);
}

void send_post(SOCKET recvSocket, char* host_name, char * data){

	char request[500];
	sprintf(request, "POST /var/12 HTTP/1.0\r\nHost: %s\r\nContent-length: %d\r\n\r\n%s", host_name, strlen(data), data);
	puts(request);
	send(recvSocket, request, strlen(request), 0);
}

