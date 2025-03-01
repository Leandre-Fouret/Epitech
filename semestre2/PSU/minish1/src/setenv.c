/*
** EPITECH PROJECT, 2025
** MiniShell1
** File description:
** setenv
*/

#include "minish.h"

/**
 * @brief Check if a env variable already exists and replace it if it does
 * @param **head The head of the linked list which contains env
 * @param *node The prepared node to check similarity with existing ones
 * @return int The boolean that indicates if variable already exist
 */
static int check_already_exists(env_linked_t **head, env_linked_t *node)
{
    env_linked_t *current = *head;

    for (; current != NULL; current = current->next) {
        if (my_strcmp(node->key, current->key) == 0) {
            free(current->value);
            current->value = my_strdup(node->value);
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Creates the new node, check if exists and add it
 * @param **head The head of the linked list which contains env
 * @param *node The node to create
 * @param *user_input To extract the params from it
 */
static int add_env_variables(env_linked_t **head,
    env_linked_t *node, char *user_input)
{
    char *tmp = NULL;

    strtok(user_input, " ");
    node->key = my_strdup(strtok(NULL, " "));
    tmp = strtok(NULL, " ");
    if (tmp != NULL)
        node->value = my_strdup(tmp);
    node->next = NULL;
    if (!check_already_exists(head, node)) {
        return add_node(head, node);
    }
    free(node->key);
    free(node->value);
    free(node);
    return 1;
}

static int check_chars_alone(char *user_input,
    env_linked_t **head, env_linked_t *node)
{
    int letters = 0;

    for (int i = 6; user_input[i] != 0; i++) {
        if (user_input[i] != ' ') {
            letters = 1;
            break;
        }
    }
    if (!letters) {
        display_env(head);
        free(node);
        return 1;
    }
    return 0;
}

static void check_myenv_errors(char *user_input, int *out)
{
    if (user_input[7] >= '0' && user_input[7] <= '9') {
        my_printf("setenv: Variable name must begin with a letter.\n");
        *out = 1;
    } else if (!my_str_isalpha(user_input + 7) &&
        !my_str_isnum(user_input + 7)) {
        my_printf("setenv: Variable name must contain "
            "alphanumeric characters.\n");
        *out = 1;
    }
}

static int exec_myenv(int space_count, env_linked_t **head,
    env_linked_t *node, char *user_input)
{
    int out = 0;

    if (space_count == 2 || space_count == 1) {
        if (user_input[7] < '0' || user_input[7] > '9')
            out = add_env_variables(head, node, user_input);
        check_myenv_errors(user_input, &out);
    }
    if (space_count > 2) {
        my_printf("setenv: Too many arguments.\n");
        free(node);
        out = 1;
    }
    return out;
}

/**
  * @brief Create new variable environments in the linked list
  * @param **head The head of the linked list which contains env
  * @param *user_input The command from the user to add the the list
  */
int set_myenv(env_linked_t **head, char *user_input)
{
    env_linked_t *node = malloc(sizeof(env_linked_t));
    int space_count = 0;
    int out = 0;

    if (node == NULL)
        return 1;
    if (check_chars_alone(user_input, head, node))
        return 1;
    for (int i = 0; i < my_strlen(user_input); i++)
        if (user_input[i] == ' ')
            space_count++;
    out = exec_myenv(space_count, head, node, user_input);
    return out;
}
