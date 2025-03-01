/*
** EPITECH PROJECT, 2024
** my_strncmp
** File description:
** reproduces strncmp
*/

#include <stddef.h>

static int min(int a, int b)
{
    if (a <= b)
        return a;
    return b;
}

static int testing2(char const *s1, char const *s2, int *array)
{
    for (int j = 0; j < min(min(array[0], array[1]), array[2]); j++) {
            if (s1[j] > s2[j])
                return 1;
            if (s1[j] < s2[j])
                return -1;
    }
    return 0;
}

int my_strncmp(char const *s1, char const *s2, int n)
{
    int l = 0;
    int l2 = 0;
    int array[3];

    for (int i = 0; s1[i] != '\0'; i++)
        l++;
    for (int i = 0; s2[i] != '\0'; i++)
        l2++;
    array[0] = l;
    array[1] = l2;
    array[2] = n;
    return testing2(s1, s2, array);
}
