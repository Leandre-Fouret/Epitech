/*
** EPITECH PROJECT, 2025
** minish2 (Workspace)
** File description:
** parsing
*/

#include "minish.h"

static void error_message(params_t *myshell, char delimiter)
{
    if (delimiter == '|')
        my_puterr("Invalid null command.\n");
    else
        my_puterr("Missing name for redirect.\n");
    myshell->exit_code = 1;
}

char ***parse_glue(params_t *myshell, char delimiter)
{
    int index = myshell->command_index;
    char **commands_pipe = NULL;
    char ***final_commands = malloc(sizeof(char **) * 3);
    char *all = malloc(sizeof(char) * MAX_INPUT_SIZE);

    all[0] = 0;
    final_commands[2] = NULL;
    commands_pipe = dup_double_arr(myshell->user_input[index]);
    for (int i = 0; commands_pipe[i] != NULL; i++) {
        if (i != 0)
            my_strcat(all, " ");
        my_strcat(all, commands_pipe[i]);
    }
    free_double_arr(commands_pipe);
    if (!fill_final_commands(all, final_commands, myshell, delimiter))
        return NULL;
    return final_commands;
}

char ***parse_space(char **commands, int i, params_t *myshell,
    char delimiter)
{
    int len = 0;
    char **first_part = NULL;
    char **second_part = NULL;
    char ***final_commands = malloc(sizeof(char **) * 3);

    if (!final_commands)
        return NULL;
    for (; commands[len] != NULL; len++);
    first_part = dup_double_arr_sel(commands, 0, i);
    second_part = dup_double_arr_sel(commands, i + 1, len);
    final_commands[2] = NULL;
    final_commands[0] = first_part;
    final_commands[1] = second_part;
    if (first_part[0] == NULL || second_part[0] == NULL) {
        error_message(myshell, delimiter);
        free_triple_array(final_commands);
        return NULL;
    }
    return final_commands;
}

int find_begin(char **user_input, int i)
{
    int begin = 0;

    for (int j = 0; j < i; j++) {
        if (my_strcmp(user_input[j], "|") == 0)
            begin = j;
    }
    return begin;
}

char **parse_space_individual(int i, params_t *myshell,
    char delimiter)
{
    int len = 0;
    int index = myshell->command_index;
    char **first_part = NULL;
    int begin_index = 0;

    for (; myshell->user_input[index][len] != NULL; len++);
    begin_index = find_begin(myshell->user_input[index], i);
    begin_index = (begin_index == 0) ? begin_index : begin_index + 1;
    first_part = dup_double_arr_sel(myshell->user_input[index],
        begin_index, i);
    if (first_part[0] == NULL) {
        error_message(myshell, delimiter);
        free_double_arr(first_part);
        return NULL;
    }
    return first_part;
}

int fill_final_commands(char *all,
    char ***final_commands, params_t *myshell, char delimiter)
{
    char **commands_pipe = NULL;

    if (all[0] == delimiter || all[my_strlen(all) - 1] == delimiter) {
        error_message(myshell, delimiter);
        free(final_commands);
        return 0;
    }
    commands_pipe = my_str_to_word_array((const char *) all, delimiter);
    free(all);
    final_commands[0] = my_str_to_word_array((const char *)
        commands_pipe[0], ' ');
    final_commands[1] = my_str_to_word_array((const char *)
        commands_pipe[1], ' ');
    return 1;
}
