/*
** EPITECH PROJECT, 2024
** my_putstr
** File description:
** displays the characters of a string
*/

#include "../../include/my.h"

int my_putstr(char const *str)
{
    int l = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        l++;
    }
    for (int h = 0; h < l; h++) {
        my_putchar(str[h]);
    }
    return 0;
}
