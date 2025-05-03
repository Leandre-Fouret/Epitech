/*
** EPITECH PROJECT, 2025
** minish2 (Workspace)
** File description:
** path_redirection_command
*/

#include "minish.h"

char *find_path_r(char **parsed_paths, char *user_input, int j)
{
    int result = 0;
    char *extension = malloc(sizeof(char) * MAX_INPUT_SIZE);

    my_strcpy(extension, parsed_paths[j]);
    my_strcat(extension, "/");
    my_strcat(extension, user_input);
    result = access(extension, F_OK);
    if (result == 0) {
        return extension;
    }
    free(extension);
    return NULL;
}

static char *get_full_path_redirection(params_t *subshell)
{
    char *path = NULL;
    char **parsed_paths = NULL;
    env_t *current = *subshell->head;
    char *end = NULL;

    for (; my_strcmp(current->key, "PATH") != 0; current = current->next);
    path = my_strdup(current->value);
    parsed_paths = my_str_to_word_array(path, ':');
    free(path);
    for (int i = 0; parsed_paths[i] != NULL; i++) {
        end = find_path_r(parsed_paths, subshell->user_input[0][0], i);
        if (end != NULL) {
            free_double_arr(parsed_paths);
            return end;
        }
    }
    free_double_arr(parsed_paths);
    return NULL;
}

char *run_command_redirection(params_t *subshell)
{
    int local_command = 0;
    char *command_path = NULL;

    for (int i = 0; i < my_strlen(subshell->user_input[0][0]); i++)
        if (subshell->user_input[0][0][i] == '/')
            local_command = 1;
    command_path = local_command ? my_strdup(subshell->user_input[0][0]) :
        get_full_path_redirection(subshell);
    if (command_path == NULL) {
        subshell->exit_code = 1;
        my_printf("%s: Command not found.\n", subshell->user_input[0][0]);
        return NULL;
    }
    return command_path;
}
