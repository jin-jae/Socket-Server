//
// Created by KIM JINJAE on 2022/12/29.
//
#include "exception.h"

void    throwException(char *exception) {
    if (exception == "SOCK_ERR")
        ft_print("Socket Error\n");
    if (exception == "BIND_ERR")
        ft_print("Bind Error\n");
    if (exception == "LISTEN_ERR")
        ft_print("Listen Error\n");
    if (exception == "ACCEPT_ERR")
        ft_print("Accept Error\n");

    return;
}