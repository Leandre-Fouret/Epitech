/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** store_input
*/

#include "amazed.h"

static char *my_clean_str(char *str)
{
    if (str == NULL || str[0] == '\0' || str[0] == '\n')
        return NULL;
    if (my_strcmp("##start", str) == 0 || my_strcmp("##end", str) == 0) {
        return str;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '#' && i == 0)
            str[i] = '\0';
        if (str[i] == '#')
            str[i] = '\0';
    }
    return str;
}

static void exec_store(stdin_t **input, char *line)
{
    stdin_t *node = malloc(sizeof(stdin_t));

    if (!node)
        return;
    if (!line) {
        node->next = NULL;
        node->line = NULL;
        add_node(input, node);
        return;
    }
    if (line[0] == '\0') {
        free(node);
        return;
    }
    node->next = NULL;
    node->line = my_strdup(line);
    add_node(input, node);
}

void store_stdin(stdin_t **input)
{
    char *line = NULL;
    char *clean = NULL;
    size_t line_len = 0;

    while (getline(&line, &line_len, stdin) != -1) {
        if (my_strlen(line) > 0 && line[my_strlen(line) - 1] == '\n')
            line[my_strlen(line) - 1] = '\0';
        clean = my_clean_str(line);
        exec_store(input, clean);
    }
    free(line);
}
