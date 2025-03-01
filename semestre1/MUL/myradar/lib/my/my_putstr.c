/*
** EPITECH PROJECT, 2024
** my_putstr
** File description:
** Displays one by one the characters of a string
*/

#include <unistd.h>
#include "my.h"

int my_putstr(char const *str)
{
    int taille = 0;

    while (str[taille] != '\0'){
        my_putchar(str[taille]);
        taille++;
    }
    return 0;
}
