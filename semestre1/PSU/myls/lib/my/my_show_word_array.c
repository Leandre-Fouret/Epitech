/*
** EPITECH PROJECT, 2024
** my_show_word_array
** File description:
** Displays the content of an array of words
*/

#include "my.h"

int my_show_word_array(char *const *tab)
{
    for (int i = 0; tab[i] != 0; i++){
        my_putstr(tab[i]);
        my_putstr("\n");
    }
    return 0;
}
