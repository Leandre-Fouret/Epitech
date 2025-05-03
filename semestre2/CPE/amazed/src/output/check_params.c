/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** check_params
*/

#include "amazed.h"

int check_inter_params(room_t **rooms, room_t *current, specifiers_t *params)
{
    if (!current->next) {
        my_puterr("Invalid specifier definition\n");
        return 84;
    }
    params->start = (my_strcmp(current->name, "##start") == 0)
    ? params->start + 1 : params->start;
    params->end = (my_strcmp(current->name, "##end") == 0)
    ? params->end + 1 : params->end;
    if (params->start > 1)
        my_puterr("Double start definition\n");
    if (params->end > 1)
        my_puterr("Double end definition\n");
    if (params->start > 1 || params->end > 1)
        return 84;
    my_printf("%s\n", current->name);
    if (check_names(rooms, current->next) == 84)
        return 84;
    if (check_coordinates(rooms, current->next) == 84)
        return 84;
    return 0;
}

int check_end_params(specifiers_t *params)
{
    if (params->start != 1)
        my_puterr("Missing start definition\n");
    if (params->end != 1)
        my_puterr("Missing end definition\n");
    if (params->start != 1 || params->end != 1)
        return 84;
    return 0;
}
