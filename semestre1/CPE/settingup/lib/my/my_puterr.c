/*
** EPITECH PROJECT, 2024
** my_puterr
** File description:
** Print a string in the stderr
*/

#include <unistd.h>
#include "my.h"

int my_puterr(char const *str)
{
    int taille = 0;

    while (str[taille] != '\0'){
        write(2, &(str[taille]), 1);
        taille++;
    }
    return 0;
}
