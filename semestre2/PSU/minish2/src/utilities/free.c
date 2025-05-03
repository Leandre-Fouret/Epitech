/*
** EPITECH PROJECT, 2025
** minish2 (Workspace)
** File description:
** free
*/

#include "minish.h"

void free_double_arr(char **arr)
{
    for (int i = 0; arr[i] != NULL; i++)
        free(arr[i]);
    free(arr);
}

void free_triple_array(char ***arr)
{
    for (int i = 0; arr[i] != NULL; i++) {
        for (int j = 0; arr[i][j] != NULL; j++)
            free(arr[i][j]);
        free(arr[i]);
    }
    free(arr);
}
