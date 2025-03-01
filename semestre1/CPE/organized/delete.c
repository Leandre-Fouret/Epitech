/*
** EPITECH PROJECT, 2024
** organized
** File description:
** delete
*/

#include "shell.h"

void type_to_str(char *str, type_t type)
{
    for (int i = 0; i < 10; i++)
        str[i] = 0;
    if (type == ACTUATOR)
        my_strcat(str, "ACTUATOR");
    if (type == DEVICE)
        my_strcat(str, "DEVICE");
    if (type == PROCESSOR)
        my_strcat(str, "PROCESSOR");
    if (type == SENSOR)
        my_strcat(str, "SENSOR");
    if (type == WIRE)
        my_strcat(str, "WIRE");
}

static void delete_head(elements_t *current, elements_t **begin,
    char *str_type, int to_delete)
{
    if (current != NULL && current->id == to_delete) {
        type_to_str(str_type, current->elem_type);
        my_printf("%s n°%i - \"%s\" deleted.\n", str_type, current->id,
            current->name);
        *begin = current->next;
        free(current);
        return;
    }
}

static void display_deleted(char *str_type, elements_t *current,
    elements_t *prev)
{
    type_to_str(str_type, current->elem_type);
    my_printf("%s n°%i - \"%s\" deleted.\n", str_type, current->id,
        current->name);
    prev->next = current->next;
    free(current);
}

static void find_and_delete(char **args, elements_t **begin, char *str_type)
{
    int to_delete;
    elements_t *current = *begin;
    elements_t *prev = *begin;

    for (int i = 0; args[i] != NULL; i++) {
        current = *begin;
        prev = *begin;
        to_delete = my_getnbr(args[i]);
        if (begin == NULL || *begin == NULL)
            return;
        delete_head(current, begin, str_type, to_delete);
        while (current != NULL && current->id != to_delete) {
            prev = current;
            current = current->next;
        }
        if (current == NULL) {
            continue;
        }
        display_deleted(str_type, current, prev);
    }
}

static int is_num(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}

static int verif_if_exists(elements_t **begin, char **args, int i)
{
    elements_t *tmp = *begin;
    int found = 0;

    while (tmp != NULL) {
        if (tmp->id == my_getnbr(args[i])) {
            found = 1;
        }
        tmp = tmp->next;
    }
    return found;
}

static int verif_del_args(char **args, elements_t **begin)
{
    int found = 0;

    for (int i = 0; args[i] != NULL; i++) {
        if (!is_num(args[i]))
            return 84;
        found = verif_if_exists(begin, args, i);
    }
    if (!found)
        return 84;
    return 0;
}

int del(void *data, char **args)
{
    elements_t **begin = (elements_t **)data;
    char *str_type = malloc(sizeof(char) * 10);

    if (verif_del_args(args, begin) == 84)
        return 84;
    if (str_type == NULL)
        return 84;
    find_and_delete(args, begin, str_type);
    free(str_type);
    return 0;
}
