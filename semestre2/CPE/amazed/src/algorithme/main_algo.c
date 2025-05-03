/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** main_algo
*/

#include "amazed.h"

void analyse_room(amazed_t *params, room_t *current)
{
    int index = 0;

    while (current) {
        if (my_strcmp(current->name, "##start") == 0 && current->next) {
            params->start = index;
            current = current->next;
        }
        if (my_strcmp(current->name, "##end") == 0 && current->next) {
            params->end = index;
            current = current->next;
        }
        if (current->name[0] != '#')
            index++;
        current = current->next;
    }
    params->len_matrix = index;
}

int run_algo(room_t **rooms, stdin_t **input, amazed_t *params)
{
    int **matrix = store_links(rooms, input);
    room_t *current = *rooms;
    int exit_path = 0;

    if (!matrix)
        return 84;
    analyse_room(params, current);
    my_printf("#moves\n");
    exit_path = shortest_path(matrix, params);
    if (exit_path == 0)
        output_bots(params, rooms);
    free_matrix(matrix, rooms);
    return exit_path;
}

// room_t *current = *rooms;
// int len = 0;
// for (; current; current = current->next)
//     if (current->name[0] != '#')
//         len++;
//     my_printf("#moves\n");
//     for (int i = 0; i < len; i++) {
//         for (int j = 0; j < len; j++) {
//             printf("%i ", matrix[i][j]);
//         }
//         printf("\n");
//}
