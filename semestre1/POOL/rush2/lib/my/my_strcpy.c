/*
** EPITECH PROJECT, 2024
** my_strcpy
** File description:
** copies a string into another
*/

#include "../../include/my.h"

char *my_strcpy(char *dest, char const *src)
{
    int l = 0;

    while (src[l] != '\0') {
        dest[l] = src[l];
        l++;
    }
    dest[l] = '\0';
    return dest;
}
