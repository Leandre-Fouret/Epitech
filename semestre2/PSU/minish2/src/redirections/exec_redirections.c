/*
** EPITECH PROJECT, 2025
** minish2 (Workspace)
** File description:
** exec_redirections
*/

#include "minish.h"

void exec_redirect_glue_r(params_t *myshell, params_t *subshell)
{
    char ***final_commands = parse_glue(myshell, '>');

    if (final_commands != NULL) {
        subshell->user_input = final_commands;
        fork_redirections(subshell);
    }
}

void exec_redirect_space_r(params_t *myshell, params_t *subshell,
    int index, int i)
{
    char ***final_commands = parse_space
        (myshell->user_input[index], i, myshell, '>');

    if (final_commands != NULL) {
        subshell->user_input = final_commands;
        fork_redirections(subshell);
    }
}

void exec_redirect_glue_l(params_t *myshell, params_t *subshell)
{
    char ***final_commands = parse_glue(myshell, '<');

    if (final_commands != NULL) {
        subshell->user_input = final_commands;
        fork_redirections(subshell);
    }
}

void exec_redirect_space_l(params_t *myshell, params_t *subshell,
    int index, int i)
{
    char ***final_commands = parse_space
        (myshell->user_input[index], i, myshell, '<');

    if (final_commands != NULL) {
        subshell->user_input = final_commands;
        fork_redirections(subshell);
    }
}
