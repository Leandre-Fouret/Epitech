/*
** EPITECH PROJECT, 2025
** libmy
** File description:
** my_str_to_word_array
*/

#include "my.h"

static int is_delimiter(char c, char delimiter, int *inquote)
{
    if (c == '"' || c == '\'')
        *inquote = !(*inquote);
    return ((c == delimiter || c == '\t' || c == '\n') &&
        !(*inquote));
}

static void browse_string(char c, int *count, int *inquote, char delimiter)
{
    int inword = 0;
    int local_quote = *inquote;

    if (c == '"' || c == '\'')
        local_quote = !local_quote;
    if ((c == delimiter || c == '\t' || c == '\n')
        && !local_quote)
        inword = 0;
    else if (!inword) {
        inword = 1;
        (*count)++;
    }
}

static int count_total_words(char const *str, char delimiter, int *inquote)
{
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        browse_string(str[i], &count, inquote, delimiter);
    }
    return count;
}

static char *insert_word(char const **str_address,
    char delimiter, int *inquote)
{
    char const *str = *str_address;
    char const *begin;
    int size = 0;
    char *new_word = NULL;

    while (*str && is_delimiter(*str, delimiter, inquote))
        str++;
    begin = str;
    while (*str && !is_delimiter(*str, delimiter, inquote))
        str++;
    size = str - begin;
    new_word = malloc(sizeof(char) * (size + 1));
    if (new_word == NULL)
        return NULL;
    my_strncpy(new_word, begin, size);
    new_word[size] = '\0';
    *str_address = str;
    return new_word;
}

static void clean_tab(char **tab)
{
    for (int i = 0; tab[i] != NULL; i++) {
        if (my_strlen(tab[i]) == 0) {
            free(tab[i]);
            tab[i] = NULL;
        }
    }
}

char **my_str_to_word_array(char const *str, char delimiter)
{
    int inquote = 0;
    int word_counter = count_total_words(str, delimiter, &inquote);
    char **tab = malloc(sizeof(char *) * (word_counter + 1));
    char *tmp_word = NULL;

    inquote = 0;
    if (tab == NULL)
        return NULL;
    for (int i = 0; i < word_counter; i++) {
        tmp_word = insert_word(&str, delimiter, &inquote);
        tab[i] = tmp_word;
    }
    tab[word_counter] = NULL;
    clean_tab(tab);
    return tab;
}
