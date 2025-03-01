/*
** EPITECH PROJECT, 2024
** organized
** File description:
** sort
*/

#include "shell.h"

void relink_body(elements_t *begin, elements_t *current_node,
    elements_t *next_node)
{
    elements_t *prev_node = begin;

    while (prev_node->next != current_node) {
        prev_node = prev_node->next;
    }
    prev_node->next = next_node;
}

void make_relinks(elements_t **begin, elements_t *current_node,
    elements_t *next_node)
{
    if (current_node == *begin) {
        *begin = next_node;
    } else
        relink_body(*begin, current_node, next_node);
}

int sort(void *data, char **args)
{
    elements_t **begin = (elements_t **)data;
    int j = 0;

    for (; args[j] != NULL; j++);
    j--;
    for (; j >= 0; j--) {
        if (my_strcmp(args[j], "-r") == 0)
            continue;
        if (my_strcmp(args[j], "TYPE") == 0)
            *begin = just_sort_type(*begin, args, j);
        if (my_strcmp(args[j], "NAME") == 0)
            *begin = just_sort_name(*begin, args, j);
        if (my_strcmp(args[j], "ID") == 0)
            *begin = just_sort_id(*begin, args, j);
        if (my_strcmp(args[j], "TYPE") != 0 && my_strcmp(args[j], "NAME") != 0
            && my_strcmp(args[j], "ID") != 0)
            return 84;
    }
    return 0;
}
