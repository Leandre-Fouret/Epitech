/*
** EPITECH PROJECT, 2024
** organized
** File description:
** sort_type
*/

#include "shell.h"

void find_swap_type(elements_t **begin, elements_t *current_node,
    elements_t *next_node, int *swapped)
{
    char *str_type = malloc(sizeof(char) * 10);
    char *str_type_next = malloc(sizeof(char) * 10);

    if (str_type == NULL || str_type_next == NULL)
        return;
    type_to_str(str_type, current_node->elem_type);
    type_to_str(str_type_next, current_node->next->elem_type);
    if (my_strcmp(str_type, str_type_next) > 0) {
        current_node->next = next_node->next;
        next_node->next = current_node;
        make_relinks(begin, current_node, next_node);
        *swapped = 1;
    }
    free(str_type);
    free(str_type_next);
}

void find_swap_type_rev(elements_t **begin, elements_t *current_node,
    elements_t *next_node, int *swapped)
{
    char *str_type = malloc(sizeof(char) * 10);
    char *str_type_next = malloc(sizeof(char) * 10);

    if (str_type == NULL || str_type_next == NULL)
        return;
    type_to_str(str_type, current_node->elem_type);
    type_to_str(str_type_next, current_node->next->elem_type);
    if (my_strcmp(str_type, str_type_next) < 0) {
        current_node->next = next_node->next;
        next_node->next = current_node;
        make_relinks(begin, current_node, next_node);
        *swapped = 1;
    }
    free(str_type);
    free(str_type_next);
}

int execute_type(elements_t **begin, char **args, int i)
{
    elements_t *next_node;
    int swapped = 0;
    elements_t *current_node = *begin;

    while (current_node->next != NULL) {
        next_node = current_node->next;
        if (my_strcmp(args[i + 1], "-r") != 0)
            find_swap_type(begin, current_node, next_node, &swapped);
        else
            find_swap_type_rev(begin, current_node, next_node, &swapped);
        current_node = next_node;
    }
    return swapped;
}

elements_t *just_sort_type(elements_t *begin, char **args, int i)
{
    int swapped;

    if (begin == NULL)
        return NULL;
    do {
        swapped = execute_type(&begin, args, i);
    } while (swapped);
    return begin;
}
