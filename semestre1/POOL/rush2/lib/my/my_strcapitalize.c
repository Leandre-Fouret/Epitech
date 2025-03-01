/*
** EPITECH PROJECT, 2024
** my_strcapitalize
** File description:
** puts all first letters of a word in capitals
*/

static char *my_strlowcase2(char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] >= 65 && str[i] <= 90)
            str[i] = str[i] + 32;
        i++;
    }
    return str;
}

static int my_str_majoring(char *str, int i)
{
    if (((str[i] > 57 && str[i] < 65)
        || (str[i] > 90 && str[i] < 97)
        || (str[i] > 122)
        || (str[i] < 48))
        && (str[i + 1] >= 97 && str[i + 1] <= 122)) {
        return 1;
    }
    return 0;
}

char *my_strcapitalize(char *str)
{
    int i = 0;

    str = my_strlowcase2(str);
    if (i == 0 && (str[i] >= 97 && str[i] <= 122)) {
        str[i] = str[i] - 32;
        i++;
    }
    while (str[i] != '\0' && str[i + 1] != '\0') {
        if (my_str_majoring(str, i) == 1)
            str[i + 1] = str[i + 1] - 32;
        i++;
    }
    return str;
}
