/*
** EPITECH PROJECT, 2024
** my_strncpy
** File description:
** Copies n chars from a str into another
*/

char *my_strncpy(char *dest, char const *src, int n)
{
    int taille = 0;

    while (src[taille] != '\0') {
        taille++;
    }
    for (int i = 0; i < n; i++) {
        if (i < taille)
            dest[i] = src[i];
        if (i == taille) {
            dest[i] = '\0';
            return dest;
        }
    }
    return dest;
}
