/*
** EPITECH PROJECT, 2025
** minish2 (Workspace)
** File description:
** utilities
*/

#include "minish.h"

int is_printable(char *str, size_t len_read)
{
    for (size_t i = 0; i < len_read; i++) {
        if ((str[i] < 32 || str[i] > 126) && str[i] != '\n' &&
            str[i] != '\t' && str[i] != '\0') {
            return 0;
        }
    }
    return 1;
}

char **dup_double_arr(char **arr)
{
    int len = 0;
    char **new_arr = NULL;

    for (; arr[len] != NULL; len++);
    new_arr = malloc(sizeof(char *) * (len + 1));
    if (!new_arr)
        return NULL;
    new_arr[len] = NULL;
    for (int i = 0; i < len; i++) {
        new_arr[i] = my_strdup(arr[i]);
    }
    return new_arr;
}

char **dup_double_arr_sel(char **arr, int a, int b)
{
    char **new_arr = NULL;
    int len = b - a;

    new_arr = malloc(sizeof(char *) * (len + 1));
    if (!new_arr)
        return NULL;
    new_arr[len] = NULL;
    for (int i = 0; i < len; i++) {
        new_arr[i] = my_strdup(arr[a + i]);
    }
    return new_arr;
}

int add_node_pipe(pipes_t **head, pipes_t *node)
{
    pipes_t *current = *head;

    if (*head == NULL) {
        *head = node;
        return 1;
    }
    for (; current->next != NULL; current = current->next);
    current->next = node;
    return 0;
}
