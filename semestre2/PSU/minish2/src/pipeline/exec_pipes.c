/*
** EPITECH PROJECT, 2025
** minish2 (Workspace)
** File description:
** exec_pipes
*/

#include "minish.h"

// static void free_pipe_exec(char ***commands_pipe,
//     char **commands_path)
// {
//     free_triple_array(commands_pipe);
//     free_double_arr(commands_path);
// }

char *get_full_pipe_path(params_t *myshell, char *command)
{
    char *path = NULL;
    char **parsed_paths = NULL;
    env_t *current = *myshell->head;
    char *end = NULL;

    for (; my_strcmp(current->key, "PATH") != 0; current = current->next);
    path = my_strdup(current->value);
    parsed_paths = my_str_to_word_array(path, ':');
    free(path);
    for (int i = 0; parsed_paths[i] != NULL; i++) {
        end = find_path(parsed_paths, command, i);
        if (end != NULL) {
            free_double_arr(parsed_paths);
            return end;
        }
    }
    free_double_arr(parsed_paths);
    return NULL;
}

// static int error_occured(params_t *myshell, char ***commands,
//     char **commands_path)
// {
//     int error = 0;

//     if (commands_path[0] == NULL) {
//         my_printf("%s: Command not found.\n", commands[0][0]);
//         error = 1;
//     }
//     if (commands_path[1] == NULL) {
//         my_printf("%s: Command not found.\n", commands[1][0]);
//         error = 1;
//     }
//     if (error) {
//         free_double_arr(commands_path);
//         free_triple_array(commands);
//         myshell->exit_code = 1;
//     }
//     return error;
// }

// void exec_pipe(char ***commands_pipe, params_t *myshell)
// {
//     int local_command1 = 0;
//     int local_command2 = 0;
//     char **commands_path = malloc(sizeof(char *) * 3);

//     commands_path[2] = NULL;
//     for (int i = 0; i < my_strlen(commands_pipe[0][0]); i++)
//         if (commands_pipe[0][0][i] == '/')
//             local_command1 = 1;
//     for (int i = 0; i < my_strlen(commands_pipe[1][0]); i++)
//         if (commands_pipe[1][0][i] == '/')
//                 local_command2 = 1;
//     commands_path[0] = local_command1 ? my_strdup(commands_pipe[0][0]) :
//         get_full_pipe_path(myshell, commands_pipe[0][0]);
//     commands_path[1] = local_command2 ? my_strdup(commands_pipe[1][0]) :
//         get_full_pipe_path(myshell, commands_pipe[1][0]);
//     if (error_occured(myshell, commands_pipe, commands_path))
//         return;
//     fork_pipe(myshell, commands_pipe, commands_path);
//     free_pipe_exec(commands_pipe, commands_path);
// }
