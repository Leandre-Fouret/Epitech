/*
** EPITECH PROJECT, 2024
** my_revstr
** File description:
** reverses a string
*/

static void my_operations(char *array, int i, int j)
{
    int temp;

    temp = array[i];
    array[i] = array[j - 1];
    array[j - 1] = temp;
}

char *my_revstr(char *str)
{
    int l = 0;
    int j = 0;

    for (int i = 0; str[i] != '\0'; i++)
        l++;
    while (j < l / 2) {
        my_operations(str, j, l - j);
        j++;
    }
    return str;
}
