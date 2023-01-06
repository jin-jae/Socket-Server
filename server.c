//
// Created by KIM JINJAE on 2022/12/28.
//

#include "library.h"

void    Server(char* port) {
    ft_print("--------------- Server Program made by KIM JINJAE ---------------\n");
    ft_print("Server will try to open port number "); ft_print(port); ft_print("...\n");

    int serverSocket;
    int clientSocket;

    struct sockaddr_in  serverAddress;
    struct sockaddr_in  clientAddress;

    socklen_t   clientAddressSize;
    /* socket function : parameters
     *  domain - Determines which domain that communication happens.
     *  type - Indicates semantics of communication. (TCP 연결)
     *  protocol -
     *  written from "man socket" from linux System Calls Manual
    */
    ft_print("Setting server socket... ");
    serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
        throwException("SOCK_ERR");
    ft_print("done!\n");

    ft_print("Setting server address... ");
    memset(&serverAddress, 0, sizeof(serverAddress));
    /* IPV4 체계를 이용해 통신합니다. */
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(ft_atoi(port));
    ft_print("done!\n");

    ft_print("Bind server address... ");
    if (bind(serverSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) == -1)
        throwException("BIND_ERR");
    ft_print("done!\n");
    ft_print("Listen to port... ");
    if (listen(serverSocket, 5) == -1)
        throwException("LISTEN_ERR");

    while (1)
    {
        ft_print("Trying to accept client socket... ");
        clientAddressSize = sizeof(clientAddress);
        clientSocket = accept(serverSocket, (struct sockaddr*) &clientAddress, &clientAddressSize);
        if (clientSocket == -1)
        {
            throwException("ACCEPT_ERR");
            break ;
        }
        ft_print("done!\n");
        checkRequest(clientSocket);
    }
    close(clientSocket);
    close(serverSocket);
    ft_print("------------------------- Server ended --------------------------\n");
}