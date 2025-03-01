/*
** EPITECH PROJECT, 2024
** my_strlen
** File description:
** Counts the number of characters found in a string
*/

#include <unistd.h>
#include "my.h"

int my_strlen(char const *str)
{
    char const *a = str;
    int compteur = 0;

    while (*a != '\0'){
        compteur++;
        a++;
    }
    return compteur;
}
