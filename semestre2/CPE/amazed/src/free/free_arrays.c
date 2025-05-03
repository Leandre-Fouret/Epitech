/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** free_arrays
*/

#include "amazed.h"

void free_matrix(int **matrix, room_t **rooms)
{
    room_t *current = *rooms;
    int len = 0;

    for (; current; current = current->next)
        if (current->name[0] != '#')
            len++;
    for (int i = 0; i < len; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void free_double_arr(char **arr)
{
    for (int i = 0; arr[i] != NULL; i++) {
        free(arr[i]);
    }
    free(arr);
}
