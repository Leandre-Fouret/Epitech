/*
** EPITECH PROJECT, 2024
** add_display
** File description:
** function to add and display elements of the linked list
*/

#include "shell.h"

static char *print_typed_value(type_t type)
{
    char *result = malloc(sizeof(char) * 10);

    if (result == NULL)
        return my_strdup("MALLOCERR");
    for (int i = 0; i < 10; i++)
        result[i] = 0;
    if (type == ACTUATOR)
        my_strcat(result, "ACTUATOR");
    if (type == DEVICE)
        my_strcat(result, "DEVICE");
    if (type == PROCESSOR)
        my_strcat(result, "PROCESSOR");
    if (type == SENSOR)
        my_strcat(result, "SENSOR");
    if (type == WIRE)
        my_strcat(result, "WIRE");
    return result;
}

int disp(void *data, char **args)
{
    elements_t **begin = (elements_t **)data;
    elements_t *tmp;
    char *result;

    if (args[0] != NULL)
        return 84;
    tmp = *begin;
    while (tmp != NULL) {
        result = print_typed_value(tmp->elem_type);
        if (my_strcmp(result, "MALLOCERR") == 0)
            return 84;
        my_printf("%s n°%i - \"%s\"\n", result, tmp->id, tmp->name);
        free(result);
        tmp = tmp->next;
    }
    return 0;
}

static void check_if_exists(elements_t *tmp, int *found, int *i)
{
    while (tmp != NULL) {
        if (tmp->id == *i) {
            *found = 1;
            break;
        }
        tmp = tmp->next;
    }
}

static int new_id(elements_t **linked_list)
{
    elements_t *tmp;
    int i = 0;
    int found;

    while (1) {
        tmp = *linked_list;
        found = 0;
        check_if_exists(tmp, &found, &i);
        if (!found)
            return i;
        i++;
    }
}

static int check_add_args(char **args, int i)
{
    if (args[i + 0] == NULL || args[i + 1] == NULL)
        return -1;
    if (my_strcmp("ACTUATOR", args[i + 0]) == 0 ||
        my_strcmp("DEVICE", args[i + 0]) == 0 ||
        my_strcmp("PROCESSOR", args[i + 0]) == 0 ||
        my_strcmp("SENSOR", args[i + 0]) == 0 ||
        my_strcmp("WIRE", args[i + 0]) == 0) {
            return 0;
        }
    return -1;
}

static type_t str_to_type(char *str)
{
    if (my_strcmp("ACTUATOR", str) == 0)
        return ACTUATOR;
    if (my_strcmp("DEVICE", str) == 0)
        return DEVICE;
    if (my_strcmp("PROCESSOR", str) == 0)
        return PROCESSOR;
    if (my_strcmp("SENSOR", str) == 0)
        return SENSOR;
    if (my_strcmp("WIRE", str) == 0)
        return WIRE;
    return 84;
}

static int push_new(elements_t **begin, char **args, int i)
{
    elements_t *tmp = malloc(sizeof(elements_t));
    int id = new_id(begin);

    if (tmp == NULL)
        return 84;
    my_printf("%s n°%i - \"%s\" added.\n", args[i], id, args[i + 1]);
    tmp->elem_type = str_to_type(args[i]);
    tmp->id = id;
    tmp->name = my_strdup(args[i + 1]);
    tmp->next = *begin;
    *begin = tmp;
    return 0;
}

int add(void *data, char **args)
{
    int cur_arg = 0;
    elements_t **begin = (elements_t **)data;
    int i = 0;

    for (; args[i] != NULL; i++);
    if (i == 0)
        return 84;
    for (; args[cur_arg] != NULL; cur_arg += 2) {
        if (check_add_args(args, cur_arg) == -1)
            return 84;
    }
    cur_arg = 0;
    for (; args[cur_arg] != NULL; cur_arg += 2) {
        if (push_new(begin, args, cur_arg) == 84)
            return 84;
    }
    return 0;
}
