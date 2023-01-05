//
// Created by KIM JINJAE on 2022/12/29.
//
#include "library.h"

int ft_atoi(char* str)
{
    int ans;
    int arr[10];
    int i;
    int j;

    ans = 0;
    i = 0;
    while (*str)
    {
        arr[i] = *str - '0';
        str++;
        i++;
    }
    j = 1;
    while (i > 0)
    {
        ans += arr[i] * j;
        j *= 10;
        i--;
    }
    return ans;
}

void    ft_char(char c)
{
    write(1, &c, 1);
}

void	ft_print(char *str)
{
    while (*str)
    {
        ft_char(*str);
        str++;
    }
}