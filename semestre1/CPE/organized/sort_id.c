/*
** EPITECH PROJECT, 2024
** organized
** File description:
** sort_id
*/

#include "shell.h"

void find_swap_id(elements_t **begin, elements_t *current_node,
    elements_t *next_node, int *swapped)
{
    if (current_node->id > current_node->next->id) {
        current_node->next = next_node->next;
        next_node->next = current_node;
        make_relinks(begin, current_node, next_node);
        *swapped = 1;
    }
}

void find_swap_id_rev(elements_t **begin, elements_t *current_node,
    elements_t *next_node, int *swapped)
{
    if (current_node->id < current_node->next->id) {
        current_node->next = next_node->next;
        next_node->next = current_node;
        make_relinks(begin, current_node, next_node);
        *swapped = 1;
    }
}

int execute_id(elements_t **begin, char **args, int i)
{
    int swapped = 0;
    elements_t *current_node = *begin;
    elements_t *next_node;

    while (current_node->next != NULL) {
        next_node = current_node->next;
        if (my_strcmp(args[i + 1], "-r") != 0)
            find_swap_id(begin, current_node, next_node, &swapped);
        else
            find_swap_id_rev(begin, current_node, next_node, &swapped);
        current_node = next_node;
    }
    return swapped;
}

elements_t *just_sort_id(elements_t *begin, char **args, int i)
{
    int swapped;

    if (begin == NULL)
        return NULL;
    do {
        swapped = execute_id(&begin, args, i);
    } while (swapped);
    return begin;
}
