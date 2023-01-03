//
// Created by KIM JINJAE on 2022/12/29.
//

#ifndef SERVER_CLIENT_FT_LIBRARY_H
#define SERVER_CLIENT_FT_LIBRARY_H

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#include "exception.h"
#include "server.h"

void    ft_char(char c);
void	ft_print(char *str);
//void    *ft_memset(void *param, int num, size_t len);
int ft_atoi(char* str);

#endif //SERVER_CLIENT_FT_LIBRARY_H
