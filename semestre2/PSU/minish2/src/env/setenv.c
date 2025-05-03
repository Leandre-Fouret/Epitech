/*
** EPITECH PROJECT, 2025
** minish2 (Workspace)
** File description:
** setenv
*/

#include "minish.h"

static int check_already_exists(env_t **head, env_t *node)
{
    env_t *current = *head;

    for (; current != NULL; current = current->next) {
        if (my_strcmp(node->key, current->key) == 0) {
            free(current->value);
            current->value = my_strdup(node->value);
            return 1;
        }
    }
    return 0;
}

static int add_env_variables(params_t *myshell, env_t *node)
{
    int index = myshell->command_index;

    node->key = my_strdup(myshell->user_input[index][1]);
    node->value = (myshell->user_input[index][2] == NULL) ?
        0 : my_strdup(myshell->user_input[index][2]);
    node->next = NULL;
    if (!check_already_exists(myshell->head, node)) {
        return add_node(myshell->head, node);
    }
    free(node->key);
    free(node->value);
    free(node);
    return 1;
}

static void check_myenv_errors(params_t *myshell)
{
    int index = myshell->command_index;

    if (myshell->user_input[index][1][0] >= '0' &&
        myshell->user_input[index][1][0] <= '9') {
        my_printf("setenv: Variable name must begin with a letter.\n");
        myshell->exit_code = 1;
    } else if (!my_str_isalphanumeric(myshell->user_input[index][1])) {
        my_printf("setenv: Variable name must contain "
            "alphanumeric characters.\n");
        myshell->exit_code = 1;
    }
}

static void exec_myenv(params_t *myshell, env_t *node)
{
    int index = myshell->command_index;

    if (myshell->user_input[index][1][0] < '0' ||
        myshell->user_input[index][1][0] > '9')
        myshell->exit_code = add_env_variables(myshell, node);
    check_myenv_errors(myshell);
}

void set_myenv(params_t *myshell)
{
    env_t *node = malloc(sizeof(env_t));
    int nb_args = 1;
    int index = myshell->command_index;

    for (; myshell->user_input[index][nb_args] != NULL; nb_args++);
    if (node == NULL || myshell->user_input[index][1] == NULL) {
        display_env(myshell);
        return;
    }
    if (nb_args > 3) {
        my_printf("setenv: Too many arguments.\n");
        free(node);
        myshell->exit_code = 1;
        return;
    }
    exec_myenv(myshell, node);
}
