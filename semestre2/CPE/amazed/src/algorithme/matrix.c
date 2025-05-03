/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** matrix
*/

#include "amazed.h"

static int get_index(room_t **rooms, char **parsed_line,
    int which)
{
    room_t *current = *rooms;
    int index = 0;

    if (which != 0 && which != 1)
        return -3;
    for (; current; current = current->next) {
        if (my_strcmp(parsed_line[which], current->name) == 0) {
            return index;
        }
        if (current->name[0] != '#')
            index++;
    }
    return -2;
}

static void add_link(int **matrix, char **parsed_line,
    room_t **rooms)
{
    int index_a = get_index(rooms, parsed_line, 0);
    int index_b = get_index(rooms, parsed_line, 1);

    matrix[index_a][index_b] = 1;
}

static void mirror_matrix(int **matrix, int len)
{
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            matrix[j][i] = (matrix[i][j]) ? 1 : matrix[j][i];
        }
    }
}

static void parse_links(room_t **rooms, stdin_t **input, int **links)
{
    char **parsed_line = NULL;
    stdin_t *curr_in = *input;

    for (; !is_link(curr_in->line); curr_in = curr_in->next);
    for (; curr_in; curr_in = curr_in->next) {
        parsed_line = my_str_to_word_array(curr_in->line, '-');
        add_link(links, parsed_line, rooms);
        free_double_arr(parsed_line);
    }
}

static int **create_default_matrix(int len)
{
    int **links = NULL;

    links = malloc(sizeof(int *) * len);
    if (!links) {
        my_puterr("Error allocating main matrix\n");
        return NULL;
    }
    *links = NULL;
    for (int i = 0; i < len; i++) {
        links[i] = malloc(sizeof(int) * len);
        if (!links[i]) {
            my_puterr("Error allocating subarray in matrix\n");
            return NULL;
        }
        for (int j = 0; j < len; j++)
            links[i][j] = 0;
    }
    return links;
}

int **store_links(room_t **rooms, stdin_t **input)
{
    int len = 0;
    room_t *current = *rooms;
    int **links = NULL;

    for (; current; current = current->next)
            len++;
    len = len - 2;
    links = create_default_matrix(len);
    if (!links || !*links)
        return NULL;
    parse_links(rooms, input, links);
    mirror_matrix(links, len);
    return links;
}
