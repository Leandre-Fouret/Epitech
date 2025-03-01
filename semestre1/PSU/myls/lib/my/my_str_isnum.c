/*
** EPITECH PROJECT, 2024
** my_str_isnum
** File description:
** Returns a boolean given the printability of a string
*/

int my_str_isnum(char const *str)
{
    int verif = 0;
    int taille = 0;

    while (str[taille] != '\0')
        taille++;
    if (taille == 0)
        return 1;
    for (int i = 0; str[i] != '\0'; i++){
        if (str[i] >= '0' && str[i] <= '9')
            verif++;
    }
    if (verif == taille)
        return 1;
    return 0;
}
