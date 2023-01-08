//
// Created by KIM JINJAE on 2023/01/05.
//

#ifndef SOCKET_SERVER_REQUEST_H
#define SOCKET_SERVER_REQUEST_H

#include "library.h"

#define END_LINE    "\r\n"
#define HTTP_VERSION "HTTP/1.1"
#define CONTENT_TYPE "text/html; charset=UTF-8"

// Response Code List
#define OK  "200 OK"
#define NO_CONTENT  "204 No Content"
#define BAD_REQUEST "400 Bad Request"
#define NOT_FOUND "404 Not Found"
#define VERSION_NOT_SUPPORTED   "505 HTTP Version Not Supported"

void    checkRequest(int *clientSocket);
void    createResponseMessage(char* responseMessage, char* request, char* hierarchy, char* version);
int getHtmlFile(char* responseMessage, char* htmlFileBuffer, char* hierarchy);

#endif //SOCKET_SERVER_REQUEST_H
