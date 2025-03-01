/*
** EPITECH PROJECT, 2023
** B-CPE-110 : Setting Up Shell
** File description:
** shell.h
*/

#ifndef SHELL_H
    #define SHELL_H
    #include <stdlib.h>
    #include <unistd.h>
    #include "my.h"

typedef enum type {
    ACTUATOR,
    DEVICE,
    PROCESSOR,
    SENSOR,
    WIRE
} type_t;

typedef struct elements_s {
    int id;
    type_t elem_type;
    char *name;
    struct elements_s *next;
} elements_t;

// To be implemented
int add(void *data, char **args);
int del(void *data, char **args);
int sort(void *data, char **args);
int disp(void *data, char **args);

// Already implemented
int workshop_shell(void *data);

//My functions
void type_to_str(char *str, type_t type);
elements_t *just_sort_name(elements_t *begin, char **args, int i);
elements_t *just_sort_type(elements_t *begin, char **args, int i);
void relink_body(elements_t *begin, elements_t *current_node,
    elements_t *next_node);
void make_relinks(elements_t **begin, elements_t *current_node,
    elements_t *next_node);
elements_t *just_sort_id(elements_t *begin, char **args, int i);

#endif /* SHELL_H */
