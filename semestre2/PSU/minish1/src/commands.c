/*
** EPITECH PROJECT, 2025
** MiniShell1
** File description:
** Handle the execution with fork of the none-builtins commands
*/

/**
 * @file commands.c
 * @brief All the functions that interpret and execute the binaries in PATH
 *
 * When we write a command in a terminal (like 'ls'), it is a binary file
 * stored somewhere on the computer indicated by the PATH environment variable.
 * We make sure to find local and global binaries to execute them while taking
 * care of potential segfaulting programs. For that, we use fork.
 */

#include "minish.h"

static void free_path_array(char **pathdeux)
{
    for (int i = 0; pathdeux[i] != NULL; i++)
        free(pathdeux[i]);
    free(pathdeux);
}

/**
 * @brief Creates the path with the custom command and check if exists
 * @param **pathdeux The double array whith each path of the PATH env variable
 * @param *user_input The custom command entered by the user
 * @param j The index of pathdeux to know which path to check
 * @return char* The found path if exists, else NULL
 */
char *find_path(char **pathdeux, char *user_input, int j)
{
    int result = 0;
    char *extension = malloc(sizeof(char) * STRING_SIZE);

    my_strcpy(extension, pathdeux[j]);
    my_strcat(extension, "/");
    my_strcat(extension, user_input);
    result = access(extension, F_OK);
    if (result == 0) {
        return extension;
    }
    free(extension);
    return NULL;
}

/**
 * @brief Get the absolute path of a linux command
 * @param **head The head of the linked list which contains env
 * @param *user_input The command entered by the user
 * @return char* The absolute path if found, else NULL
 */
char *get_full_path(env_linked_t **head, char *user_input)
{
    char *path = NULL;
    char **pathdeux = NULL;
    env_linked_t *current = *head;
    char *end = NULL;

    for (; my_strcmp(current->key, "PATH") != 0; current = current->next);
    path = my_strdup(current->value);
    pathdeux = str_in_array(path, ':');
    free(path);
    for (int i = 0; pathdeux[i] != NULL; i++) {
        end = find_path(pathdeux, user_input, i);
        if (end != NULL) {
            free_path_array(pathdeux);
            return end;
        }
    }
    free_path_array(pathdeux);
    return NULL;
}

/**
 * @brief Inserts a node content inside a double array
 * @param *current The node to insert
 * @param **global The double array to fill
 * @param index The index of 'global' in which to insert the node
 */
static void insert_index(env_linked_t *current, char **global, int index)
{
    char *tmp = NULL;
    int len = my_strlen(current->key);

    if (current->value != NULL)
        len += my_strlen(current->value);
    tmp = malloc(sizeof(char) * (len + 2));
    if (!tmp)
        return;
    tmp[0] = 0;
    my_strcat(tmp, current->key);
    my_strcat(tmp, "=");
    if (current->value != NULL)
        my_strcat(tmp, current->value);
    global[index] = tmp;
}

/**
 * @brief Creates a double array from a linked list
 * @param **head The head of the linked list which contains env
 * @return char** The double array created
 */
char **convert_list_doublearr(env_linked_t **head)
{
    env_linked_t *current = *head;
    int len = 0;
    char **global = NULL;
    int index = 0;

    for (; current != NULL; current = current->next)
        len++;
    global = malloc(sizeof(char *) * (len + 1));
    if (!global)
        return NULL;
    for (int i = 0; i < len + 1; i++)
        global[i] = NULL;
    current = *head;
    for (; current != NULL; current = current->next) {
        insert_index(current, global, index);
        index++;
    }
    return global;
}

/**
 * @brief Handles the execution of a not-built-in program
 * @param *user_input The custom command entered by the user
 * @param **head The linked list whith the env variables
 * @return int A simple status code
 */
void run_command(char *user_input, env_linked_t **head, int *return_status)
{
    char *path = NULL;
    int status = 0;
    int is_slash = 0;
    char **tab_fork[2] = {str_in_array(user_input, ' '),
        convert_list_doublearr(head)};

    for (int i = 0; i < my_strlen(tab_fork[0][0]); i++)
        if (user_input[i] == '/')
            is_slash = 1;
    if (!is_slash)
        path = get_full_path(head, tab_fork[0][0]);
    if (path == NULL)
        path = my_strdup(tab_fork[0][0]);
    my_fork(path, tab_fork, &status);
    handle_fork_errors(tab_fork, &status, path, return_status);
    if (*return_status == 50)
        *return_status = 1;
    else
        *return_status = status;
}
