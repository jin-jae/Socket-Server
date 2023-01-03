//
// Created by KIM JINJAE on 2022/12/29.
//
#include "exception.h"

void    throwException(char *exception) {
    ft_print("exception: ");
    if !(strcmp(exception, "SOCK_ERR")) {
        ft_print("Socket Error\n");
    }
    if !(strcmp(exception, "BIND_ERR")) {
        ft_print("Bind Error\n");
    }
    if !(strcmp(exception, "LISTEN_ERR")) {
        ft_print("Listen Error\n");
    }
    if !(strcmp(exception, "ACCEPT_ERR")) {
        ft_print("Accept Error\n");
    }
    return;
}