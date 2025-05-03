/*
** EPITECH PROJECT, 2025
** browse_line.c
** File description:
** C file for browseline function
*/

#include "amazed.h"

static int analyse_line(room_t **rooms, room_t *current, specifiers_t *params)
{
    if (my_strncmp(current->name, "##", 2) == 0) {
        if (check_inter_params(rooms, current, params) == 84)
            return 84;
        current = current->next;
        return 0;
    }
    if (check_names(rooms, current) == 84)
        return 84;
    if (check_coordinates(rooms, current) == 84)
        return 84;
    my_printf("%s %s %s\n", current->name, current->x, current->y);
    return 0;
}

int browse_line(room_t **rooms)
{
    room_t *current = *rooms;
    specifiers_t params = {0, 0};

    my_printf("#rooms\n");
    for (; current; current = current->next) {
        if (analyse_line(rooms, current, &params) == 84)
            return 84;
    }
    return check_end_params(&params);
}
