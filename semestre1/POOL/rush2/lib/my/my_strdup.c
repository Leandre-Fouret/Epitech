/*
** EPITECH PROJECT, 2024
** my_strdup
** File description:
** copies a string into allocated memory
*/

#include <stdlib.h>
#include "../../include/my.h"

char *my_strdup(char const *src)
{
    char *str = malloc(sizeof(char) * (my_strlen(src) + 1));
    int index = 0;

    for (int i = 0; i < my_strlen(src) + 1; i++) {
        str[i] = src[i];
        index++;
    }
    str[index] = '\0';
    return str;
}
