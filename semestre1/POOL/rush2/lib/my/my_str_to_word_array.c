/*
** EPITECH PROJECT, 2024
** my_str_to_word_array
** File description:
** splits a string into words
*/

#include <stdlib.h>
#include <stdio.h>
#include "../../include/my.h"

static int my_str_non_alphanumeric(char const *str, int i)
{
    if ((str[i] > 57 && str[i] < 65)
        || (str[i] > 90 && str[i] < 97)
        || (str[i] > 122)
        || (str[i] < 48)) {
        return 1;
    }
    return 0;
}

static char *my_strncpy2(char *dest, char const *src, int n, int k)
{
    for (int i = k; i < n; i++)
        dest[i - k] = src[i];
    dest[n - k] = '\0';
    return dest;
}

static char *allocate_word(char const *str, int *i, int *k)
{
    char *word = malloc(sizeof(char) * ((*i) - (*k) + 1));

    return my_strncpy2(word, str, *i, *k);
}

static int number_words(char const *str)
{
    int nbr = 0;
    int i = 0;

    while (str[i] != '\0') {
        while (my_str_non_alphanumeric(str, i) == 1) {
            i++;
        }
        while (my_str_non_alphanumeric(str, i) == 0) {
            i++;
        }
        nbr++;
    }
    return nbr;
}

char **my_str_to_word_array(char const *str)
{
    int i = 0;
    int j = 0;
    char **array = malloc(sizeof(char *) * (number_words(str) + 1));
    int k = 0;

    while (str[i] != '\0') {
        while (my_str_non_alphanumeric(str, i) == 1 && str[i] != '\0') {
            i++;
            k++;
        }
        if (str[k] == '\0')
            break;
        while (my_str_non_alphanumeric(str, i) == 0 && str[i] != '\0')
            i++;
        array[j] = allocate_word(str, &i, &k);
        j++;
        k = i;
    }
    array[j] = NULL;
    return array;
}
