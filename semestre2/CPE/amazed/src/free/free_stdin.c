/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** free_stdin
*/

#include "amazed.h"

void free_stdin(stdin_t **input)
{
    stdin_t *tmp = *input;
    stdin_t *current = *input;

    while (current != NULL) {
        tmp = current;
        current = current->next;
        free(tmp->line);
        free(tmp);
    }
    free(input);
}
