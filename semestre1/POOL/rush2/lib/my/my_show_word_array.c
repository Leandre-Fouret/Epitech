/*
** EPITECH PROJECT, 2024
** my_show_word_array
** File description:
** displays the coontent of an array of words
*/

#include "../../include/my.h"

int my_show_word_array(char const **tab)
{
    int i = 0;

    while (tab[i] != 0) {
        my_putstr(tab[i]);
        my_putstr("\n");
        i++;
    }
}
