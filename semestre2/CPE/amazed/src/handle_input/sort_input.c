/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** sort_input
*/

#include "amazed.h"

static void init_node(char **parsed_line, room_t *node)
{
    if (!parsed_line[1]) {
        node->x = my_strdup("-1");
        node->y = my_strdup("-1");
        return;
    } else
        node->x = my_strdup(parsed_line[1]);
    if (!parsed_line[2]) {
        node->y = my_strdup("-1");
        return;
    } else
        node->y = my_strdup(parsed_line[2]);
}

static void store_each_elements(room_t **rooms, char **parsed_line)
{
    room_t *node = malloc(sizeof(room_t));

    if (!node) {
        my_puterr("Error allocating memory for node in room_t\n");
        return;
    }
    node->name = my_strdup(parsed_line[0]);
    init_node(parsed_line, node);
    append(rooms, node);
}

static void add_empty_line(room_t **rooms)
{
    room_t *new = malloc(sizeof(room_t));

    if (!new) {
        my_puterr("Problem with memory allocation of room_t empty\n");
        return;
    }
    new->name = NULL;
    new->x = NULL;
    new->y = NULL;
    append(rooms, new);
}

void sort_input(room_t **rooms, stdin_t **input)
{
    stdin_t *tmp_line = *input;
    char **parsed_line = NULL;

    tmp_line = tmp_line->next;
    for (; tmp_line != NULL; tmp_line = tmp_line->next) {
        if (is_link(tmp_line->line))
            break;
        if (!tmp_line->line) {
            add_empty_line(rooms);
            continue;
        }
        parsed_line = my_str_to_word_array(tmp_line->line, ' ');
        store_each_elements(rooms, parsed_line);
        free_double_arr(parsed_line);
    }
}
