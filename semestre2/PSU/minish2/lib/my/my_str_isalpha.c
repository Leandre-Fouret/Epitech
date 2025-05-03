/*
** EPITECH PROJECT, 2024
** B-CPE-100-LIL-1-1-cpoolday06-theophile.riffe
** File description:
** str_isalpha
*/

#include "my.h"

int my_isnum2(char c)
{
    if (c >= '0' && c <= '9')
        return 1;
    return 0;
}

static int my_isalpha(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return 1;
    return 0;
}

int my_str_isalphanumeric(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (!my_isalpha(str[i]) && !my_isnum2(str[i]))
            return 0;
    return 1;
}
