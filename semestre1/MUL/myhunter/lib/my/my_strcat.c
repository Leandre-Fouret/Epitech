/*
** EPITECH PROJECT, 2024
** my_strcat
** File description:
** Concatenates two strings
*/

#include "my.h"

char *my_strcat(char *dest, char const *src)
{
    int taille_dest = 0;
    int index_src = 0;

    while (dest[taille_dest] != 0)
        taille_dest++;
    for (index_src; src[index_src] != 0; index_src++){
        dest[taille_dest] = src[index_src];
        taille_dest++;
    }
    dest[taille_dest] = '\0';
    return dest;
}
