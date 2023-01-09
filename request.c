//
// Created by KIM JINJAE on 2023/01/05.
//

#include "request.h"

void    checkRequest(int *clientSocket)
{
    char message[BUFFER_SIZE];
    int receiveClientSocket = *(int *) clientSocket;
    // client 에서 메시지를 받아옵니다.
    if (recv(receiveClientSocket, message, BUFFER_SIZE - 1, 0) <= 0)
        throwException("RECEIVE_ERR");
    // 확인을 위해 받은 메시지를 출력합니다.
    printf("!!!!!!!!!!!!!!!!! Caught New Request from Client !!!!!!!!!!!!!!!!!\n");
    printf("%s", message);
    printf("!!!!!!!!!!!!!!!!!!!!!!!!! End of Message !!!!!!!!!!!!!!!!!!!!!!!!!\n");

    // 받은 메시지를 쪼개서 분석합니다.
    char *ptr = strtok(message, " ");
    char *request = ptr;
    ptr = strtok(NULL, " ");
    char *hierarchy = ptr;
    ptr = strtok(NULL, " \r\n");
    char *version = ptr;
    char *body = NULL;
    if (!strcmp(request, POST))
    {
        for (int i = 0; i < 6; i++)
            ptr = strtok(NULL, "\n");
        body = ptr;
    }

    // 전달할 메시지 string을 만듭니다.
    char responseMessage[BUFFER_SIZE] = "";

    // 전달할 메시지를 형식에 맞추어 작성하는 함수를 호출합니다.
    createResponseMessage(responseMessage, request, hierarchy, version, body);

    // client 에 해당 메시지를 전달합니다.
    if (write(receiveClientSocket, responseMessage, strlen(responseMessage) + 1) <= 0)
        printf("SEND_ERR");
}

void    createResponseMessage(char* responseMessage, char* request, char* hierarchy, char* version, char* body)
{
    // 조건에 맞으면 505 메시지를 반환합니다. (http 버전이 다른 경우 505 메시지 반환)
    if (strcmp(version, HTTP_VERSION))
    {
        strcat(strcat(strcat(strcat(responseMessage, HTTP_VERSION), " "), VERSION_NOT_SUPPORTED), END_LINE);
        strcat(responseMessage, END_LINE);
    }
    // 조건에 맞으면 400 메시지를 반환합니다. (들어오는 요청이 GET이나 POST 가 아니라면 400 메시지 반환)
    else if (strcmp(request, "GET") && strcmp(request, "POST"))
    {
        strcat(strcat(strcat(strcat(responseMessage, HTTP_VERSION), " "), BAD_REQUEST), END_LINE);
        strcat(responseMessage, END_LINE);
    }
    else
    {
        // 해당 파일이 존재하는지 검사해서 있으면 200 OK 반환
        if (!strcmp(hierarchy, "/") || !strcmp(hierarchy, "/index.html") ||
            !strcmp(hierarchy, "/connect.html") || !strcmp(hierarchy, "/login.html"))
        {
            strcat(strcat(strcat(strcat(responseMessage, HTTP_VERSION), " "), OK), END_LINE);
            strcat(strcat(strcat(responseMessage, "Content-Type: "), CONTENT_TYPE), END_LINE);
            strcat(responseMessage, END_LINE);
            char htmlFileBuffer[512] = "";
            // 파일을 요청해서 받아온 내용이 비어 있다면 204 No Content 반환
            if (getHtmlFile(responseMessage, htmlFileBuffer, hierarchy, body))
                strcat(responseMessage, htmlFileBuffer);
        }
        // 서버에 존재하는 파일이 아니면 404 Not Found 반환
        else
        {
            strcat(strcat(strcat(strcat(responseMessage, HTTP_VERSION), " "), NOT_FOUND), END_LINE);
            strcat(responseMessage, END_LINE);
        }
    }
}

int getHtmlFile(char* responseMessage, char* htmlFileBuffer, char* hierarchy, char* body) {
    FILE *fp;
    // 파일에 해당하는 경로 찾아가기
    char fileRoot[100] = "resource";
    strcat(fileRoot, hierarchy);

    if (!strcmp(hierarchy, "/"))
        strcat(fileRoot, "index.html");
    // 파일을 열어서 읽음
    fp = fopen(fileRoot, "r");
    while (feof(fp) == 0) {
        char tmp[100];
        fgets(tmp, 100, fp);
        strcat(htmlFileBuffer, tmp);
    }
    fclose(fp);
    // POST 요청이 들어오면 맞추어서 버퍼 내용을 수정합니다.
    if (!strcmp(hierarchy, "/login.html"))
    {
        for (int i = 0; i < 17; i++) {
            htmlFileBuffer[i + 111] = (char) body[i];
        }
    }

    // 혹시 파일 내용이 없다면 No Content 로 메시지를 수정한 이후 0 리턴
    if (strlen(htmlFileBuffer) < 10)
    {
        for (int i = 0; i < BUFFER_SIZE; i++)
            responseMessage[i] = 0;
        strcat(strcat(strcat(strcat(responseMessage, HTTP_VERSION), " "), NO_CONTENT), END_LINE);
        strcat(responseMessage, END_LINE);
        return 0;
    }
    // 파일 내용이 있다면 -1 리턴
    return -1;
}