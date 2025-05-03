/*
** EPITECH PROJECT, 2025
** check_coordinates.c
** File description:
** C file for check coords function
*/

#include "amazed.h"

int check_coordinates(room_t **rooms, room_t *current)
{
    room_t *tmp = *rooms;

    while (tmp != current) {
        if (my_strncmp(tmp->name, "##", 2) == 0) {
            tmp = tmp->next;
            continue;
        }
        if (tmp->x[0] == '-' || tmp->y[0] == '-') {
            my_puterr("Error: Need coordinates for any rooms\n");
            return 84;
        }
        if (my_strcmp(tmp->x, current->x) == 0 &&
            my_strcmp(tmp->y, current->y) == 0) {
            my_puterr("Error: Same coordinates for two rooms or more\n");
            return 84;
        }
        tmp = tmp->next;
    }
    return 0;
}
