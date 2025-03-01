/*
** EPITECH PROJECT, 2024
** my_strcpy
** File description:
** Copies a string into another
*/

#include <unistd.h>
#include "my.h"

char *my_strcpy(char *dest, char const *src)
{
    int taille = 0;

    while (src[taille] != '\0'){
        taille++;
    }
    for (int i = 0; i < taille; i++){
        dest[i] = src[i];
    }
    dest[taille] = '\0';
    return dest;
}
