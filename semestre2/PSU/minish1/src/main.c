/*
** EPITECH PROJECT, 2025
** mysh
** File description:
** Main file
*/

/**
 * @file main.c
 * @brief Handle the main functions of the 'Minishell1' project
 *
 * Contains all the base of the minishell project.
 * Check for errors, get properly user input and interpret it
 * several ways to know what to do with it.
 */

#include "minish.h"

/**
 * @brief Removes the spaces at then end of the string
 * @param *input The user input to 'clean'
 */


/**
 * @brief Add the new env variable in the linked list
 * @param **head The head of the env linked list
 * @param *node The node to add in the linked list
 */
int add_node(env_linked_t **head, env_linked_t *node)
{
    env_linked_t *current = *head;

    if (*head == NULL) {
        *head = node;
        return 1;
    }
    for (; current->next != NULL; current = current->next);
    current->next = node;
    return 0;
}

/**
 * @brief Parse the values and copy them in the newly allocated node
 * @param **envp The environment variables
 * @param i The index to know which variable to add
 * @return env_linked_t* The created node
 */
env_linked_t *create_node(char **envp, int i)
{
    env_linked_t *node = malloc(sizeof(env_linked_t));

    if (!node)
        return NULL;
    node->key = my_strdup(strtok(envp[i], "="));
    node->value = my_strdup(strtok(NULL, ""));
    node->next = NULL;
    return node;
}

/**
 * @brief Get the environment variables to put them in a linked list
 *
 * @param **envp The environment variables used for execve
 * @return env_linked_t The head of the linked list
 */
env_linked_t **get_all_env(char **envp)
{
    env_linked_t **head = malloc(sizeof(env_linked_t *));
    env_linked_t *node = NULL;

    if (!head)
        return NULL;
    if (envp == NULL || *envp == NULL)
        return NULL;
    *head = NULL;
    for (int i = 0; envp[i] != NULL; i++) {
        node = create_node(envp, i);
        add_node(head, node);
    }
    return head;
}

/**
 * @brief Free the env linked list
 * @param **head The head of the linked list which contains env
 */
static void free_env(env_linked_t **head)
{
    env_linked_t *tmp = *head;
    env_linked_t *current = *head;

    while (current != NULL) {
        tmp = current;
        current = current->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
    free(head);
}

static void set_status_shell(int *status_shell)
{
    if (*status_shell == -1)
        *status_shell = 1;
}

static void run_main_loop(env_linked_t **head, int *status_shell)
{
    int raw_out = 0;
    int exit = 0;
    char *current_previous = malloc(sizeof(char) * STRING_SIZE);

    if (current_previous == NULL)
        return;
    current_previous[0] = 0;
    getcwd(current_previous, STRING_SIZE);
    while (1) {
        raw_out = run_shell(head, status_shell, &exit, current_previous);
        if (exit || raw_out == -1) {
            set_status_shell(status_shell);
            free_env(head);
            free(current_previous);
            break;
        }
    }
}

/**
 * @brief Runs the shell and handles the exit function
 *
 * @param argc The number of cli arguments
 * @param **argv The array of arguments
 * @param **envp The environment variables used for execve
 * @return int The main status code
 */
int main(int argc, char **argv, char **envp)
{
    int status_shell = 0;
    env_linked_t **head = NULL;

    argc = argc;
    argv = argv;
    head = get_all_env(envp);
    if (*head == NULL || head == NULL)
        return 1;
    run_main_loop(head, &status_shell);
    return status_shell;
}
