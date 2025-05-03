/*
** EPITECH PROJECT, 2025
** check_names.c
** File description:
** C file for check_names function
*/

#include "amazed.h"

int check_names(room_t **rooms, room_t *current)
{
    room_t *tmp = *rooms;

    while (tmp != current) {
        if (tmp->name == NULL) {
            my_puterr("Error: Remove empty lines\n");
            return 84;
        }
        if (my_strcmp(current->name, tmp->name) == 0) {
            my_puterr("Error: Duplicated room name\n");
            return 84;
        }
        tmp = tmp->next;
    }
    return 0;
}
