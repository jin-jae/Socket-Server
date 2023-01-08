//
// Created by KIM JINJAE on 2022/12/28.
//

#include "library.h"

void    Server(void)
{
    printf("--------------- Server Program made by KIM JINJAE ---------------\n");
    printf("Enter which port to open >> ");
    // 개방할 port를 입력받음
    int port;

    scanf("%d", &port);
    printf("Server will try to open port number %d...\n", port);

    int serverSocket;
    int clientSocket;

    struct sockaddr_in  serverAddress;
    struct sockaddr_in  clientAddress;

    socklen_t   clientAddressSize;
    /* socket function : parameters
     *  domain - Determines which domain that communication happens.
     *  type - Indicates semantics of communication. (TCP 연결)
     *  protocol - Determines which protocol to be used in the socket.
    */
    printf("Setting server socket... ");
    serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    // 성공적으로 열지 못하면 -1 반환
    if (serverSocket == -1)
        throwException("SOCK_ERR");
    printf("done!\n");

    printf("Setting server address... ");
    // serverAddress 메모리 내용을 초기화
    memset(&serverAddress, 0, sizeof(serverAddress));
    // serverAddress 내용 설정
    // UDP or TCP
    serverAddress.sin_family = AF_INET;
    // 어떠한 IP Address로부터의 요청도 받아들임
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    // 개방할 Port Number 설정
    serverAddress.sin_port = htons(port);
    printf("done!\n");

    printf("Binding server address... ");
    // server 포트를 bind
    // 성공 시 0, 실패 시 -1 반환
    if (bind(serverSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) == -1)
        throwException("BIND_ERR");
    printf("done!\n");
    printf("Listening to port... ");
    // socket의 연결을 들음 (최대 대기 queue는 5로 설정)
    if (listen(serverSocket, 5) == -1)
        throwException("LISTEN_ERR");
    printf("done!\n");

    // server는 24시간 열려 있어 client 의 요청을 언제나 받아들인다는 설정
    while (1)
    {
        printf("Trying to accept client socket... ");
        clientAddressSize = sizeof(clientAddress);
        // client로부터 요청을 받아들이기까지 이 위치에서 기다림
        clientSocket = accept(serverSocket, (struct sockaddr*) &clientAddress, &clientAddressSize);
        if (clientSocket == -1)
        {
            throwException("ACCEPT_ERR");
            break ;
        }
        printf("caught message!!\n");
        // 메시지를 잡으면 처리하러 가는 함수 checkRequest 실행
        checkRequest(&clientSocket);
    }
    close(clientSocket);
    close(serverSocket);
    printf("------------------------- Server ended --------------------------\n");
}
