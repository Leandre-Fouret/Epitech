/*
** EPITECH PROJECT, 2024
** my_strcat
** File description:
** concatenates two strings
*/

char *my_strcat(char *dest, char const *src)
{
    int l = 0;
    int k = 0;

    while (dest[l] != '\0')
        l++;
    while (src[k] != '\0')
        k++;
    for (int j = 0; j < k; j++) {
        dest[l + j] = src[j];
        }
    dest[l + k] = '\0';
    return dest;
}
