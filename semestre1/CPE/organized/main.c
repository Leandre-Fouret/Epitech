/*
** EPITECH PROJECT, 2024
** bsorganized
** File description:
** main
*/

#include "shell.h"

int main(void)
{
    elements_t *linked_list = NULL;
    elements_t *current;
    elements_t *tmp;

    if (workshop_shell(&linked_list) == 84) {
        current = linked_list;
        while (current != NULL) {
            tmp = current;
            current = current->next;
            free(tmp->name);
            free(tmp);
    }
        return 84;
    }
    return 0;
}
