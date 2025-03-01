/*
** EPITECH PROJECT, 2024
** my_strupcase
** File description:
** Puts every letter of a string in uppercase
*/

#include "my.h"

char *my_strupcase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++){
        if (str[i] > 96 && str[i] < 123){
            str[i] = str[i] - 32;
        }
    }
    return str;
}
