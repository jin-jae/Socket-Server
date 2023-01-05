//
// Created by KIM JINJAE on 2022/12/29.
//

#ifndef SERVER_CLIENT_FT_LIBRARY_H
#define SERVER_CLIENT_FT_LIBRARY_H

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#include "exception.h"
#include "server.h"
#include "request.h"

int ft_atoi(char* str);
void    ft_char(char c);
void	ft_print(char *str);

#endif //SERVER_CLIENT_FT_LIBRARY_H
