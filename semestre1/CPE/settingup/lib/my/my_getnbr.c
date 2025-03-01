/*
** EPITECH PROJECT, 2024
** my_getnbr
** File description:
** Default build
*/

#include "my.h"

int my_getnbr(char const *str)
{
    int result = 0;
    int minus_count = 0;

    while ((*str) == '-' || ((*str) == '+')){
            if (*str == '-')
                minus_count++;
            str++;
        }
    while ((*str >= '0') && (*str <= '9')){
            result = (result * 10) + ((*str) - '0');
            str++;
        }
    if (minus_count % 2 != 0)
        return (result * (-1));
    return result;
}
