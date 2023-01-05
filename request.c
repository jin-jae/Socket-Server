//
// Created by KIM JINJAE on 2023/01/05.
//

#include "request.h"

void    checkRequest(int clientSocket)
{
    char message[1024];
    scanf("%[^\n]s", message);
    write(clientSocket, message, sizeof(message));
}