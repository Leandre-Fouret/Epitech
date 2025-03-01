/*
** EPITECH PROJECT, 2025
** MiniShell1
** File description:
** get and clean the user input
*/

#include "minish.h"

/**
 * @file clean_and_get.c
 * @brief Get the user input and clean it
 *
 * Get the user input with getline and clean it
 * by removing the spaces and tabs
 */

static void exec_shell(char **input_curr_prev, int *return_status,
    env_linked_t **head, int *exit)
{
    int exit_status = *return_status;

    if (my_strncmp("exit", input_curr_prev[0], 4) == 0) {
        if (my_exit(input_curr_prev[0], &exit_status)) {
            *exit = 1;
            free(input_curr_prev[0]);
            *return_status = exit_status;
            return;
        }
    }
    if (!run_builtins(input_curr_prev[0], head, return_status,
        input_curr_prev[1])) {
        run_command(input_curr_prev[0], head, return_status);
    }
    free(input_curr_prev[0]);
}

void trim_loop(char *start, int *last_was_space, char **current)
{
    if (*start == ' ' || *start == '\t') {
        if (!(*last_was_space)) {
            **current = ' ';
            (*current)++;
            *last_was_space = 1;
        }
    } else {
        **current = *start;
        (*current)++;
        *last_was_space = 0;
    }
}

void trim_and_normalize_spaces(char *input)
{
    char *start = input;
    char *current = input;
    int last_was_space = 0;
    size_t len = my_strlen(input);

    if (len > 0 && input[len - 1] == '\n')
        input[len - 1] = '\0';
    while (*start && (*start == ' ' || *start == '\t'))
        start++;
    while (*start) {
        trim_loop(start, &last_was_space, &current);
        start++;
    }
    if (last_was_space && current > input)
        current--;
    *current = '\0';
}

/**
 * @brief Display the prompt and get the user input
 * @param **head The head of the linked list which contains env
 * @return int The shell status code
 */
int run_shell(env_linked_t **head, int *return_status, int *exit,
    char *current_previous)
{
    char *user_input = NULL;
    size_t len_read = 0;
    char *input_curr_prev[2] = {NULL, current_previous};

    write(1, "$> ", 3);
    if (getline(&user_input, &len_read, stdin) == -1) {
        return -1;
    }
    user_input[my_strlen(user_input)] = 0;
    if (user_input[0] == 0 || user_input[0] == ' ') {
        *return_status = 0;
        return 0;
    }
    trim_and_normalize_spaces(user_input);
    input_curr_prev[0] = user_input;
    exec_shell(input_curr_prev, return_status, head, exit);
    return *return_status;
}
