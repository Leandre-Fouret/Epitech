/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** utilities
*/

#include "amazed.h"

int is_link(char *line)
{
    if (!line)
        return 0;
    for (int i = 0; line[i] != '\0'; i++)
        if (line[i] == '-')
            return 1;
    return 0;
}
