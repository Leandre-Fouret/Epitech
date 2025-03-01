/*
** EPITECH PROJECT, 2024
** my_strncpy
** File description:
** copies n character of a string
*/

char *my_strncpy(char *dest, char const *src, int n)
{
    int l = 0;

    for (int i = 0; src[i] != '\0'; i++)
        l++;
    for (int j = 0; j < n; j++) {
        dest[j] = src[j];
        }
    if (n > l)
        dest[l + 1] = '\0';
    return dest;
}
