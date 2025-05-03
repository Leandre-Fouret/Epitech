/*
** EPITECH PROJECT, 2025
** minish2 (Workspace)
** File description:
** freeenv
*/

#include "minish.h"

void free_env(env_t **head)
{
    env_t *tmp = *head;
    env_t *current = *head;

    while (current != NULL) {
        tmp = current;
        current = current->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
    free(head);
}
