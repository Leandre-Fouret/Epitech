/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** free_rooms
*/

#include "amazed.h"

void free_rooms(room_t **rooms)
{
    room_t *tmp = *rooms;
    room_t *current = *rooms;

    while (current != NULL) {
        tmp = current;
        current = current->next;
        free(tmp->name);
        free(tmp->x);
        free(tmp->y);
        free(tmp);
    }
    free(rooms);
}
