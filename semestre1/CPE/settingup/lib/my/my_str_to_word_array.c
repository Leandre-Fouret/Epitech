/*
** EPITECH PROJECT, 2024
** my_str_to_word_array
** File description:
** Converts a string into an array
*/

#include "my.h"
#include <stdlib.h>

int char_isalphanumeric(char carac)
{
    if ((carac >= 'A' && carac <= 'Z')
        || (carac >= 'a' && carac <= 'z')
        || (carac >= '0' && carac <= '9')){
            return 1;
        }
        return 0;
}

char *letter(char const *str, int i)
{
    int len = 0;
    char *word;

    for (int j = i; char_isalphanumeric(str[j]); j++){
        len++;
    }
    word = malloc(sizeof(char) * (len + 1));
    for (int index = 0; char_isalphanumeric(str[index + i]); index++){
        word[index] = str[index + i];
    }
    return word;
}

char **my_str_to_word_array(char const *str)
{
    int word_count = 0;
    char **global_space;
    int word_index = 0;

    for (int lettre = 0; str[lettre] != '\0'; lettre++){
        if (char_isalphanumeric(str[lettre])
            && char_isalphanumeric(str[lettre - 1]) == 0)
            word_count++;
    }
    global_space = malloc(sizeof(char *) * (word_count + 1));
    global_space[word_count] = NULL;
    for (int lettre = 0; str[lettre] != '\0'; lettre++)
        if (str[lettre] == '\n') {
            global_space[word_index] = letter(str, lettre);
            word_index++;
        }
    return global_space;
}
