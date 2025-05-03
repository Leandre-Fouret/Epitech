/*
** EPITECH PROJECT, 2025
** minish2 (Workspace)
** File description:
** get_env
*/

#include "minish.h"

int add_node(env_t **head, env_t *node)
{
    env_t *current = *head;

    if (*head == NULL) {
        *head = node;
        return 1;
    }
    for (; current->next != NULL; current = current->next);
    current->next = node;
    return 0;
}

static env_t *create_node(char **envp, int i)
{
    env_t *node = malloc(sizeof(env_t));

    if (!node)
        return NULL;
    node->key = my_strdup(strtok(envp[i], "="));
    node->value = my_strdup(strtok(NULL, ""));
    node->next = NULL;
    return node;
}

env_t **get_all_env(char **envp)
{
    env_t **head = malloc(sizeof(env_t *));
    env_t *node = NULL;

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
