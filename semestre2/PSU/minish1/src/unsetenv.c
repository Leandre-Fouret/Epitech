/*
** EPITECH PROJECT, 2025
** MiniShell1
** File description:
** unsetenv
*/

#include "minish.h"

void del_node(env_linked_t *current, env_linked_t *prev)
{
    env_linked_t *tmp = NULL;

    prev->next = current->next;
    tmp = current;
    free(tmp->value);
    free(tmp->key);
    free(tmp);
}

void find_delete_var(env_linked_t **tab_unsetenv, char **tab,
    int i, env_linked_t **head)
{
    env_linked_t *tmp = NULL;

    if (my_strcmp(tab_unsetenv[0]->key, tab[i]) == 0) {
        if (tab_unsetenv[1] != NULL) {
            del_node(tab_unsetenv[0], tab_unsetenv[1]);
        }
        if (tab_unsetenv[1] == NULL) {
            tmp = *head;
            *head = (*head)->next;
            free(tmp->key);
            free(tmp->value);
            free(tmp);
        }
    }
}

void run_unset_loop(env_linked_t **tab_unsetenv, int len,
    char **tab, env_linked_t **head)
{
    env_linked_t *next_node = NULL;

    for (int i = 1; i < len; i++) {
        tab_unsetenv[0] = *head;
        tab_unsetenv[1] = NULL;
        while (tab_unsetenv[0] != NULL) {
            next_node = tab_unsetenv[0]->next;
            find_delete_var(tab_unsetenv, tab, i, head);
            tab_unsetenv[1] = tab_unsetenv[0];
            tab_unsetenv[0] = next_node;
        }
    }
}

/**
  * @brief Delete a env variable from the linked list
  */
int unset_myenv(env_linked_t **head, char *user_input)
{
    char **tab = NULL;
    int len = 0;
    env_linked_t *tab_unsetenv[2] = {*head, NULL};

    tab = str_in_array(user_input, ' ');
    for (; tab[len] != NULL; len++);
    if (len == 1) {
        my_printf("unsetenv: Too few arguments.\n");
        return 1;
    }
    run_unset_loop(tab_unsetenv, len, tab, head);
    for (int i = 0; i < len; i++)
        free(tab[i]);
    free(tab);
    return 0;
}
