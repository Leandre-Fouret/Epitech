/*
** EPITECH PROJECT, 2024
** my_strstr
** File description:
** Finds the first occurence of a substring in a string
*/

#include <stddef.h>
#include "my.h"

static int continue_searching(char *str, char const *to_find, int t, char *p)
{
    int index = 0;
    char *inside = p;

    while (index < t && to_find[index] == *inside){
        index++;
        inside++;
    }
    if (t == index){
        return 1;
    }
    return 0;
}

static int verif(char *str, char const *to_find, int taille_sub, char *p)
{
    if (*p == *to_find){
        if (continue_searching(str, to_find, taille_sub, p) == 1)
            return 1;
    }
}

char *my_strstr(char *str, char const *to_find)
{
    char *pointeur_vers_str = str;
    int taille_main = 0;
    int taille_sub = 0;

    while (str[taille_main] != '\0')
        taille_main++;
    while (to_find[taille_sub] != '\0')
        taille_sub++;
    if (taille_sub == 0)
        return str;
    for (int i = 0; i < taille_main; i++){
        if (verif(str, to_find, taille_sub, pointeur_vers_str) == 1)
            return pointeur_vers_str;
        pointeur_vers_str++;
    }
    return NULL;
}
