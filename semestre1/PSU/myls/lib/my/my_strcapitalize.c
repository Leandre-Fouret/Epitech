/*
** EPITECH PROJECT, 2024
** my_strcapitalize
** File description:
** Capitalizes the first letter of each word
*/

static void replace(char *str, int i)
{
    if (str[i + 1] > 64 && str[i + 1] < 91)
        str[i + 1] = str[i + 1] + 32;
    else if (str[i + 1] > 96 && str[i + 1] < 123)
        str[i + 1] = str[i + 1] - 32;
}

static void check(char *str, int i)
{
    if (i == 0 && str[i] > 96 && str[i] < 123)
        str[i] = str[i] - 32;
    if ((str[i] <= 63 || str[i] >= 91) && (str[i] <= 96 || str[i] >= 123)){
        if (str[i] < '0' || str[i] > '9')
            replace(str, i);
    }
}

char *my_strcapitalize(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] = str[i] + 32;
    for (int i = 0; str[i] != '\0'; i++){
        check(str, i);
    }
    return str;
}
