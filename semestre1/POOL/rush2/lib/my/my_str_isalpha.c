/*
** EPITECH PROJECT, 2024
** my_str_isalpha
** File description:
** checks if a string only contains letters
*/

static int my_str_checks_alpha(char const *str, int i)
{
    for (int j = 0; j < i; j++) {
        if ((str[i] > 57 && str[i] < 65)
        || (str[i] > 90 && str[i] < 97)
        || (str[i] > 122)
        || (str[i] < 48)) {
        return 0;
        }
    }
    return 1;
}

int my_str_isalpha(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (my_str_checks_alpha(str, i) == 0)
            return 0;
        i++;
    }
    return 1;
}
