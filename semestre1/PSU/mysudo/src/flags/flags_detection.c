/*
** EPITECH PROJECT, 2024
** flags_detection
** File description:
** detects and stocks flags
*/

/**
 * @file flag_detection.c
 * @brief Detect the flags
 *
 * Necessary for the sudo function to work well
 */

#include "include/my_sudo.h"

static void change_struct_flag(char car, flags_t *flags, int i, char **argv)
{
    if (car == 'u') {
        flags->u = true;
        if (argv[i + 1] != NULL)
            flags->username = argv[i + 1];
        else
            flags->problem = 84;
        return;
    }
    if (car == 'g') {
        flags->g = true;
        if (argv[i + 1] != NULL)
            flags->group_name = strdup(argv[i + 1]);
        else
            flags->problem = 84;
        return;
    }
    if (car == 'E')
        flags->E = true;
    if (car == 's')
        flags->s = true;
}

static void add_flag(char **argv, int i, int j, flags_t *flags)
{
    char tab_flags[] = {'u', 'g', 'E', 's'};

    if ((argv[i][j] == 'u' || argv[i][j] == 'g')
        && ((int)strlen(argv[i]) - 1 > j)) {
        flags->problem = 84;
        return;
    }
    for (int k = 0; tab_flags[k] != '\0'; k++) {
        if (argv[i][j] == tab_flags[k]) {
            change_struct_flag(tab_flags[k], flags, i, argv);
            return;
        }
    }
    flags->problem = 84;
}

int search_for_flags(int argc, char **argv, flags_t *flags)
{
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-')
            continue;
        for (int j = 1; j < (int)strlen(argv[i]) && ((i + 1) <= argc); j++) {
            add_flag(argv, i, j, flags);
        }
    }
    return flags->problem;
}
