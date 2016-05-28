#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socket.h"
#include "http.h"
#include "json.h"

int http_getPath(const char * const request, char * pathBuf, int maxPathBuf);
void server_homepage(socket_t * client);
void server_notFound(socket_t * client);
http_request_t http_request_parse(const char * const request);
void server_students(socket_t * client, http_request_t * req);
void server_info(socket_t * client);
int main() {
    lib_init();
    socket_t * server = socket_new();
    socket_bind(server, 5000);
    socket_listen(server);
	
   char buf[10000];
    char pathBuf[256];
    socket_t * client = NULL;

    while(1) {
		client = socket_accept(server);
        socket_read(client, buf, sizeof(buf));
		if (strlen(buf) == 0)
			continue;
        printf(">> Got request:\n%s\n", buf);

        http_getPath(buf, pathBuf, sizeof(pathBuf));

        http_request_t request = http_request_parse(buf);

        if (strcmp(request.uri, "/") == 0) {
            server_homepage(client);
        } else if (strcmp(request.uri, "/students") == 0) {
            server_students(client, &request);
        } else if (strcmp(request.uri, "/info") == 0) {
			server_info(client);
		}
		else {
            server_notFound(client);
        }
		socket_free(client);
    }
    socket_free(server);
    lib_free();
    return 0;
}

int http_getPath(const char * const request, char * pathBuf, int maxPathBuf) {
    // get method
    char method[8];
    ptrdiff_t methodLen = strstr(request, " ") - request;  // find first whitespace
    memcpy(method, request, methodLen);
    method[methodLen] = '\0';
    // get uri
    const char * uriStartPtr = request + strlen(method) + 1;
    const char * uriEndPtr = strstr(uriStartPtr, " ");  // find second whitespace
    ptrdiff_t uriLen = uriEndPtr - uriStartPtr;
    memcpy(pathBuf, uriStartPtr, uriLen);
    pathBuf[uriLen] = '\0';
    return uriLen;
}

void server_homepage(socket_t * client) {
    const char pageText[1024] = "<!DOCTYPE html> <html> <head> <title>Page Title</title> </head> <body> <h1>My First Heading</h1> <p> <a href=\"http://127.0.0.1:5000/students\">Show persons</a></p> </body> </html>";
    char homeBuf[1024];
    sprintf(homeBuf,
        "HTTP/1.1 200 OK\n"
        "Content-Type: text/html\n"
        "Content-Length: %u\n"
        "\n%s", strlen(pageText), pageText);
    socket_write_string(client, homeBuf);
    socket_close(client);
}

void server_notFound(socket_t * client) {
    char homeBuf[1024];
	
    const char * pageText = "404 Page Not Found!";
    sprintf(homeBuf,
        "HTTP/1.1 404 \n"
        "Content-Type: text/html\n"
        "Content-Length: %u\n"
        "\n%s", strlen(pageText), pageText);
    socket_write_string(client, homeBuf);
    socket_close(client);
}

http_request_t
http_request_parse(const char * const request) {
    http_request_t req;
    // get method
    ptrdiff_t methodLen = strstr(request, " ") - request;  // find first whitespace
    memcpy(req.method, request, methodLen);
    req.method[methodLen] = '\0';
    // get uri
    const char * uriStartPtr = request + strlen(req.method) + 1;
    const char * uriEndPtr = strstr(uriStartPtr, " ");  // find second whitespace
    ptrdiff_t uriLen = uriEndPtr - uriStartPtr;
    memcpy(req.uri, uriStartPtr, uriLen);
    req.uri[uriLen] = '\0';
    return req;
}

void server_students(socket_t * client, http_request_t * req) {
    char strbuf[10240];
    if (strcmp(req->method, "GET") == 0) {
		char allStudentsJson[10240] = "";
		// <p>My first paragraph.</p> </body> </html>
		char buf[1000];
		FILE * file = fopen("Untitled1.xml", "r");
		while(fgets(buf, 1000, file) != NULL)
		{
			strcat(allStudentsJson, buf);
			puts(buf);
			//allStudentsJson[strlen(allStudentsJson) + 1] = '\0';
			//allStudentsJson[strlen(allStudentsJson)] = '\n';
		}
		puts(allStudentsJson);
		list_t list = xml_to_list(allStudentsJson);
		strcpy (allStudentsJson, "<!DOCTYPE html> <html> <head> <title>Page Title</title> </head> <body> <h1>My First Heading</h1>\0");
		for (int i = 0; i < list_size(list); i++)
		{
			struct person * pers;
			pers = (struct person *)list_get(list, i);
			strcat(allStudentsJson, "<p>");
			strcat(allStudentsJson, pers->name);
			strcat(allStudentsJson, "</p>");
			allStudentsJson[strlen(allStudentsJson) + 1] = '\0';
			allStudentsJson[strlen(allStudentsJson)] = '\n';
		}
		strcat(allStudentsJson, " </body> </html>");
		list_to_xml(list);
        sprintf(strbuf,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %u\n"
            "Connection: keep-alive\n"
            "\n%s", strlen(allStudentsJson), allStudentsJson);
        //free(allStudentsJson);
		fclose(file);
	}
    socket_write_string(client, strbuf);
    socket_close(client);
}


void server_info(socket_t * client)
{
	char homeBuf[1024];
	const char * name = "Anton Salenko";
	const char * group = "KP-52";
	const char * variant = "29";
	char * text = info_to_xml(name, group, variant);
	//xml_parse_info(text, homeBuf);
	//const char * pageText = "404 Page Not Found!";
    sprintf(homeBuf,
        "HTTP/1.1 404 \n"
        "Content-Type: text/xml\n"
        "Content-Length: %u\n"
        "\n%s", strlen(text), text);
    socket_write_string(client, homeBuf);
    socket_close(client);
	free(text);
}