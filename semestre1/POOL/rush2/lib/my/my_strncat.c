/*
** EPITECH PROJECT, 2024
** my_strncat
** File description:
** concatenates n characters of a string
*/

static int minimum(int a, int b)
{
    if (a <= b)
        return a;
    return b;
}

char *my_strncat(char *dest, char const *src, int n)
{
    int l = 0;
    int k = 0;

    while (dest[l] != '\0')
        l++;
    while (src[k] != '\0')
        k++;
    for (int j = 0; j < minimum(k, n); j++) {
        dest[l + j] = src[j];
        }
    dest[l + minimum(k, n)] = '\0';
    return dest;
}
