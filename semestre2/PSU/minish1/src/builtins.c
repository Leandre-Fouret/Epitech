/*
** EPITECH PROJECT, 2025
** MiniShell1
** File description:
** Contains the builtins function management
*/

/**
 * @file builtins.c
 * @brief All the functions that interpret and execute the built-in functions
 *
 * The built-in functions are functions that do not belong to linux executables
 * which means they cannot be executed with execve.
 * It includes cd | env | setenv | unsetenv and the interpretation function
 * The exit function is already in the main funtion in the main.c file.
 */

#include "minish.h"

/**
 * @brief Display each of the environment variables
 * @param **head The head of the linked list which contains env
 */

void display_env(env_linked_t **head)
{
    env_linked_t *current = *head;

    if (*head == NULL || head == NULL)
        return;
    for (; current != NULL; current = current->next) {
        my_printf("%s=", current->key);
        if (current->value == NULL)
            my_printf("\n");
        if (current->value != NULL)
            my_printf("%s\n", current->value);
    }
    return;
}

int my_exit(char *user_input, int *exit_status)
{
    char **all = str_in_array(user_input, ' ');

    if (all[1] != NULL) {
        *exit_status = my_getnbr(all[1]);
    }
    if (my_strcmp("exit", all[0]) == 0) {
        for (int i = 0; all[i] != NULL; i++)
            free(all[i]);
        free(all);
        return 1;
    }
    for (int i = 0; all[i] != NULL; i++)
        free(all[i]);
    free(all);
    return 0;
}

/**
  * @brief Check if the user input is a built-in before execve
  * @param *user_input The user input with all its commands
  * @param **head The head of the linked list which contains env
  * @return int A boolean to indicate if a built-in was found
  */
int run_builtins(char *user_input, env_linked_t **head, int *status,
    char *current_previous)
{
    int out = 0;

    if (my_strncmp(user_input, "env", 3) == 0) {
        display_env(head);
        out = 1;
    }
    if (my_strncmp(user_input, "setenv", 6) == 0) {
        out = 1;
        *status = set_myenv(head, user_input);
    }
    if (my_strncmp(user_input, "unsetenv", 8) == 0) {
        *status = unset_myenv(head, user_input);
        out = 1;
    }
    if (my_strncmp(user_input, "cd", 2) == 0) {
        *status = my_cd(user_input, head, current_previous);
        out = 1;
    }
    return out;
}
