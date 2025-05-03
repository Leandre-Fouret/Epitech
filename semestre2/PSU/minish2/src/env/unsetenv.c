/*
** EPITECH PROJECT, 2025
** minish2 (Workspace)
** File description:
** unsetenv
*/

#include "minish.h"


static void delete_var(params_t *myshell, env_t *current, env_t *prev)
{
    env_t *to_delete = NULL;

    if (prev == NULL) {
        *(myshell->head) = current->next;
        to_delete = current;
        current = current->next;
        free(to_delete->key);
        free(to_delete->value);
        free(to_delete);
        return;
    }
    to_delete = current;
    current = current->next;
    prev->next = current;
    free(to_delete->key);
    free(to_delete->value);
    free(to_delete);
}

static void run_unset_loop(params_t *myshell)
{
    env_t *current = *(myshell->head);
    env_t *prev = NULL;
    int index = myshell->command_index;

    for (; current != NULL; current = current->next) {
        if (my_strcmp(current->key, myshell->user_input[index][1]) == 0) {
            delete_var(myshell, current, prev);
        }
        prev = current;
    }
}

void unset_myenv(params_t *myshell)
{
    int index = myshell->command_index;

    if (myshell->user_input[index][1] == NULL) {
        my_printf("unsetenv: Too few arguments.\n");
        myshell->exit_code = 1;
        return;
    }
    run_unset_loop(myshell);
}
