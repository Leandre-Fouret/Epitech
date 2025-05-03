/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** append_node
*/

#include "amazed.h"

void add_node(stdin_t **input, stdin_t *node)
{
    stdin_t *current = *input;

    if (current == NULL) {
        *input = node;
        node->next = NULL;
        return;
    }
    for (; current->next != NULL; current = current->next);
    node->next = NULL;
    current->next = node;
}

void append(room_t **head, room_t *node)
{
    room_t *current = *head;

    if (*head == NULL) {
        *head = node;
        node->next = NULL;
        return;
    }
    for (; current->next != NULL; current = current->next);
    node->next = NULL;
    current->next = node;
}
