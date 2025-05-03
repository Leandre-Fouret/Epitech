/*
** EPITECH PROJECT, 2025
** minish2 (Workspace)
** File description:
** run_command
*/

#include "minish.h"

char *find_path(char **parsed_paths, char *user_input, int j)
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

static char *return_path(params_t *myshell, int i,
    char **parsed_paths)
{
    int index = myshell->command_index;
    char *end = NULL;

    if (myshell->user_input[index][0] == NULL)
        return "\0";
    end = find_path(parsed_paths, myshell->user_input[index][0], i);
    if (end != NULL) {
        return end;
    }
    return NULL;
}

static char *get_full_path(params_t *myshell)
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
        end = return_path(myshell, i, parsed_paths);
        if (end != NULL) {
            free_double_arr(parsed_paths);
            return end;
        }
    }
    free_double_arr(parsed_paths);
    return end;
}

static void execute_simple_command(params_t *myshell,
    char *command_path)
{
    myshell->status = 0;
    my_fork(myshell, command_path);
    if (myshell->status != 0)
        handle_fork_errors(myshell);
    else
        myshell->exit_code = 0;
}

static char *get_command_path(params_t *myshell)
{
    char *command_path = NULL;
    int local_command = 0;
    int index = myshell->command_index;

    for (int i = 0; i < my_strlen(myshell->user_input[index][0]); i++)
    if (myshell->user_input[index][0][i] == '/' ||
        myshell->user_input[index][0][i] == '|')
        local_command = 1;
    command_path = local_command ? my_strdup(myshell->user_input[index][0]) :
    get_full_path(myshell);
    return command_path;
}

void run_command(params_t *myshell)
{
    char *command_path = NULL;
    int index = myshell->command_index;

    command_path = get_command_path(myshell);
    if (command_path == NULL) {
        myshell->exit_code = 1;
        my_printf("%s: Command not found.\n", myshell->user_input[index][0]);
        return;
    }
    if (*command_path == '\0')
        return;
    if (exec_pipeline(myshell))
        return;
    execute_simple_command(myshell, command_path);
    free(command_path);
    return;
}
