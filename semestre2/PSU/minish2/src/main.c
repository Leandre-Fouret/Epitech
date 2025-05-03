/*
** EPITECH PROJECT, 2025
** minish2
** File description:
** main
*/

#include "minish.h"

static void fill_commands_arr(char ***commands, char *token, int *index)
{
    char *command_part = NULL;

    while (1) {
        token = strtok(NULL, ";");
        if (token == NULL)
            break;
        command_part = my_strdup(token);
        commands[*index] = my_str_to_word_array
            ((const char *) command_part, ' ');
        (*index)++;
    }
}

static void parse_commands(params_t *myshell, char *buffer)
{
    char *token = NULL;
    char *command_part = NULL;
    char ***commands = NULL;
    int index = 1;

    commands = malloc(sizeof(char **) * MAX_COMMANDS);
    if (!commands)
        return;
    token = strtok(buffer, ";");
    if (token == NULL) {
        commands[0] = NULL;
        myshell->user_input = commands;
        return;
    }
    command_part = my_strdup(token);
    commands[0] = my_str_to_word_array((const char *) command_part, ' ');
    fill_commands_arr(commands, token, &index);
    commands[index] = NULL;
    myshell->user_input = commands;
}

static void execute_shell_commands(params_t *myshell)
{
    for (; myshell->user_input[myshell->command_index] != NULL;
        myshell->command_index++) {
        if (check_redirections(myshell))
            continue;
        if (!run_builtins(myshell))
            run_command(myshell);
    }
}

static void run_main_loop(params_t *myshell)
{
    char *buffer = NULL;
    size_t len_read = 0;

    while (1) {
        write(1, "$> ", 3);
        myshell->command_index = 0;
        if (getline(&buffer, &len_read, stdin) == -1) {
            free(buffer);
            break;
        }
        if (!is_printable(buffer, len_read) || my_strlen(buffer) == 1)
            continue;
        parse_commands(myshell, buffer);
        execute_shell_commands(myshell);
        free_triple_array(myshell->user_input);
        if (myshell->to_exit)
            break;
    }
}

void run_shell(params_t *myshell)
{
    myshell->current_previous = malloc(sizeof(char) * MAX_INPUT_SIZE);
    if (myshell->current_previous == NULL)
        return;
    myshell->current_previous[0] = 0;
    getcwd(myshell->current_previous, MAX_INPUT_SIZE);
    run_main_loop(myshell);
}

int main(int ac, char **av, char **envp)
{
    params_t myshell = {NULL, envp, ac, av, 0, 0, NULL, 0, {0},
        NULL, 0, 0, NULL};

    myshell.head = get_all_env(envp);
    if (*(myshell.head) == NULL || myshell.head == NULL)
        return 1;
    run_shell(&myshell);
    free_env(myshell.head);
    return myshell.exit_code;
}
