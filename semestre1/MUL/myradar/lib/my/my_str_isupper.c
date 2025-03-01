/*
** EPITECH PROJECT, 2024
** my_str_isupper
** File description:
** Returns a boolean given the printability of a string
*/

#include "my.h"

int my_str_isupper(char const *str)
{
    int verif = 0;
    int taille = 0;

    while (str[taille] != '\0')
        taille++;
    if (taille == 0)
        return 1;
    for (int i = 0; str[i] != '\0'; i++){
        if (str[i] >= 'A' && str[i] <= 'Z')
            verif++;
    }
    if (verif == taille)
        return 1;
    return 0;
}
