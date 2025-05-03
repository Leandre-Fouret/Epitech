/*
** EPITECH PROJECT, 2025
** minish2 (Workspace)
** File description:
** env
*/

#include "minish.h"

void display_env(params_t *myshell)
{
    env_t *current = *myshell->head;

    if (*myshell->head == NULL || myshell->head == NULL)
        return;
    for (; current != NULL; current = current->next) {
        my_printf("%s=", current->key);
        if (current->value == NULL)
            my_printf("\n");
        if (current->value != NULL)
            my_printf("%s\n", current->value);
    }
    return;
}
