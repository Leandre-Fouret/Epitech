/*
** EPITECH PROJECT, 2024
** my_strstr
** File description:
** returns the first occurence of a char in a string
*/

#include <stddef.h>

static int testing(char *str, char const *to_find, int *array)
{
    for (int j = 0; j < array[1]; j++) {
            if (str[array[2] + j] != to_find[j])
                return 0;
    }
    return 1;
}

char *my_strstr(char *str, char const *to_find)
{
    int l = 0;
    int l2 = 0;
    int array[3];

    for (int i = 0; str[i] != '\0'; i++)
        l++;
    for (int i = 0; to_find[i] != '\0'; i++)
        l2++;
    for (int i = 0; i <= l - l2; i++) {
        array[0] = l;
        array[1] = l2;
        array[2] = i;
        if (testing(str, to_find, array) == 1) {
            return &str[i];
        }
    }
    return NULL;
}
