/*
** EPITECH PROJECT, 2024
** my_strncat
** File description:
** Concatenates two strings
*/

#include "my.h"

char *my_strncat(char *dest, char const *src, int nb)
{
    int taille_dest = 0;
    int index_src = 0;
    int taille_src = 0;

    while (dest[taille_dest] != 0)
        taille_dest++;
    while (src[taille_src] != 0)
        taille_src++;
    if (nb > taille_src)
        nb = taille_src;
    for (index_src; index_src != nb; index_src++){
        dest[taille_dest] = src[index_src];
        taille_dest++;
    }
    dest[taille_dest] = '\0';
    return dest;
}
