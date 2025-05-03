/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** check_nb_bots
*/

#include "amazed.h"

static int is_integer(char *line)
{
    int len = my_strlen(line);

    for (int i = 0; i < len - 1; i++) {
        if (line[i] > '9' || line[i] < '0')
            return 0;
    }
    return 1;
}

int check_nb_bots(stdin_t *current)
{
    int nbr = 0;

    if (current == NULL)
        return 0;
    nbr = my_getnbr(current->line);
    if (nbr < 1 || is_integer(current->line) == 0)
        return 0;
    return 1;
}
