/*
** EPITECH PROJECT, 2024
** my_strncmp
** File description:
** reproduces strncmp
*/

#include <stddef.h>

static int abs(int a)
{
    if (a < 0)
        return -1 * a;
    return a;
}

static int max(int a, int b)
{
    if (a >= b)
        return a;
    return b;
}

static int testing3(char const *s1, char const *s2, int *array)
{
    for (int j = 0; j < max(array[0], array[1]) -
        abs(array[0] - array[1]); j++) {
            if (s1[j] > s2[j])
                return 1;
            if (s1[j] < s2[j])
                return -1;
    }
    return 0;
}

int my_strcmp(char const *s1, char const *s2)
{
    int l = 0;
    int l2 = 0;
    int array[2];

    for (int i = 0; s1[i] != '\0'; i++)
        l++;
    for (int i = 0; s2[i] != '\0'; i++)
        l2++;
    array[0] = l;
    array[1] = l2;
    return testing3(s1, s2, array);
}
