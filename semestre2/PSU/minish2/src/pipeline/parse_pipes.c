/*
** EPITECH PROJECT, 2025
** minish2 (Workspace)
** File description:
** parse_pipes
*/

#include "minish.h"

static void contain_pipe(params_t *myshell, int i, pipes_t **pipes)
{
    int index = myshell->command_index;
    pipes_t *new_node = NULL;

    if (my_strcmp(myshell->user_input[index][i], "|") == 0) {
        new_node = malloc(sizeof(pipes_t));
        new_node->index = i;
        new_node->type = 2;
        new_node->next = NULL;
        add_node_pipe(pipes, new_node);
        return;
    }
}

// for (int j = 0; myshell->user_input[index][i][j] != '\0'; j++) {
    // if (myshell->user_input[index][i][j] == '|') {
        // new_node = malloc(sizeof(pipes_t));
        // new_node->index = i;
        // new_node->subindex = j;
        // new_node->type = 1;
        // new_node->next = NULL;
        // add_node_pipe(pipes, new_node);
    // }
// }
static int is_local_command(char **command)
{
    for (int i = 0; command[0][i] != '\0'; i++) {
        if (command[0][i] == '/')
            return 1;
    }
    return 0;
}

static char *get_command_path(char **command, params_t *myshell)
{
    int local_command = 0;
    char *path = NULL;

    if (command == NULL || *command == NULL) {
        my_puterr("Invalid null command\n");
        myshell->exit_code = 1;
        return NULL;
    }
    local_command = is_local_command(command);
    path = (!local_command) ? get_full_pipe_path(myshell, command[0]) :
        my_strdup(command[0]);
    if (!path) {
        my_puterr(command[0]);
        my_puterr(": Command not found.\n");
        myshell->exit_code = 1;
        return NULL;
    }
    return path;
}

static int exec_final_command(pipes_t **pipes, params_t *myshell)
{
    int index = myshell->command_index;
    int len = 0;
    int begin_index = 0;
    pipes_t *new_node = malloc(sizeof(pipes_t));

    for (; myshell->user_input[index][len] != NULL; len++);
    begin_index = find_begin(myshell->user_input[index], len);
    begin_index = (begin_index == 0) ? begin_index : begin_index + 1;
    new_node->command = dup_double_arr_sel(myshell->user_input[index],
        begin_index, len);
    new_node->command_path = get_command_path(new_node->command, myshell);
    new_node->type = 2;
    new_node->next = NULL;
    if (new_node->command_path == NULL)
        return 0;
    add_node_pipe(pipes, new_node);
    return 1;
}

static int execute_pipes(params_t *myshell, pipes_t **pipes)
{
    pipes_t *current = *pipes;

    for (; current != NULL; current = current->next) {
        if (current->type == 2) {
            current->command = parse_space_individual(current->index,
                myshell, '|');
        }
        current->command_path = get_command_path(current->command, myshell);
        if (current->command_path == NULL)
            return 0;
    }
    return exec_final_command(pipes, myshell);
}

static void parse_and_exec(params_t *myshell, pipes_t **pipes)
{
    if (!execute_pipes(myshell, pipes))
        return;
    fork_pipes_2(myshell, pipes);
}

int exec_pipeline(params_t *myshell)
{
    int index = myshell->command_index;
    pipes_t **pipes = malloc(sizeof(pipes_t *));

    if (!pipes)
        return 1;
    *pipes = NULL;
    for (int i = 0; myshell->user_input[index][i] != NULL; i++)
        contain_pipe(myshell, i, pipes);
    if (*pipes != NULL) {
        parse_and_exec(myshell, pipes);
        return 1;
    }
    return 0;
}
