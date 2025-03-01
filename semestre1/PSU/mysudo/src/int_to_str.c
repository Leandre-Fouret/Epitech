/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** int_to_string
*/

/**
 * @file int_to_str.c
 * @brief Convert an integer into a char *
 *
 * Contains the function to convert an integer paramter into a char* parameter
 */

#include "include/my_sudo.h"

int my_strlen(char const *str)
{
    int l = 0;

    for (int i = 0; str[i] != '\0'; i++)
        l++;
    return l;
}

int my_len_nbr(int nb)
{
    int cpt = (nb <= 0) ? 1 : 0;

    while (nb != 0) {
        nb /= 10;
        cpt++;
    }
    return cpt;
}

static char *my_strcatchar(char *dest, char const character)
{
    int k = my_strlen(dest);

    dest[k] = character;
    dest[k + 1] = '\0';
    return dest;
}

static char *add_to_string(int nb, char *str)
{
    if (nb < 0) {
        str = my_strcatchar(str, '-');
        nb = -nb;
    }
    if (nb >= 10) {
        str = add_to_string(nb / 10, str);
    }
    str = my_strcatchar(str, '0' + nb % 10);
    return str;
}

char *turns_int_to_string(int nb)
{
    int length = my_len_nbr(nb);
    char *string_nbr = malloc(sizeof(char) * (length + 1));

    if (!string_nbr)
        return "";
    string_nbr[0] = '\0';
    return add_to_string(nb, string_nbr);
}
