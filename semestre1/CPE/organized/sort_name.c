/*
** EPITECH PROJECT, 2024
** organized
** File description:
** sort_name
*/

#include "shell.h"

void find_swap_name(elements_t **begin, elements_t *current_node,
    elements_t *next_node, int *swapped)
{
    if (my_strcmp(current_node->name, next_node->name) > 0) {
        current_node->next = next_node->next;
        next_node->next = current_node;
        make_relinks(begin, current_node, next_node);
        *swapped = 1;
    }
}

void find_swap_name_rev(elements_t **begin, elements_t *current_node,
    elements_t *next_node, int *swapped)
{
    if (my_strcmp(current_node->name, next_node->name) < 0) {
        current_node->next = next_node->next;
        next_node->next = current_node;
        make_relinks(begin, current_node, next_node);
        *swapped = 1;
    }
}

int execute_name(elements_t **begin, char **args, int i)
{
    int swapped = 0;
    elements_t *current_node = *begin;
    elements_t *next_node;

    while (current_node->next != NULL) {
        next_node = current_node->next;
        if (my_strcmp(args[i + 1], "-r") != 0)
            find_swap_name(begin, current_node, next_node, &swapped);
        else
            find_swap_name_rev(begin, current_node, next_node, &swapped);
        current_node = next_node;
    }
    return swapped;
}

elements_t *just_sort_name(elements_t *begin, char **args, int i)
{
    int swapped;

    if (begin == NULL)
        return NULL;
    do {
        swapped = execute_name(&begin, args, i);
    } while (swapped);
    return begin;
}
