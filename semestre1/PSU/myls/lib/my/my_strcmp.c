/*
** EPITECH PROJECT, 2024
** my_strcmp
** File description:
** Compare two strings
*/

int my_strcmp(char const *s1, char const *s2)
{
    int taille_s1 = 0;
    int taille_s2 = 0;
    int max;

    while (s1[taille_s1] != '\0')
        taille_s1++;
    while (s2[taille_s2] != '\0')
        taille_s2++;
    max = taille_s1;
    if (taille_s1 > taille_s2)
        max = taille_s1;
    if (taille_s1 < taille_s2)
        max = taille_s2;
    for (int i = 0; i < max; i++){
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
    }
    return 0;
}
