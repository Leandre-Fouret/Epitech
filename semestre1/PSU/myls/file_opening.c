/*
** EPITECH PROJECT, 2024
** file_opening
** File description:
** manage which file to open and how
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/sysmacros.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "my.h"
#include "spaces.h"

void get_error_occurence(char **av, spaces_t *storage,
    int *error_occured, int i)
{
    if (info_file(av[i], storage) == 84)
        *error_occured = 1;
}

// In this funtion, check for the 'a' flag
int loop(char **av, int ac, spaces_t *storage)
{
    int error_occured = 0;

    for (int i = 1; i < ac; i++) {
            if (av[i][0] != '-')
                get_error_occurence(av, storage, &error_occured, i);
        }
    if (error_occured == 1)
        return 84;
    else
        return 0;
}

int choose_which_file(char **av, int ac, int nb_file, spaces_t *storage)
{
    if (nb_file > 0) {
        return loop(av, ac, storage);
    }
    if (nb_file == 0) {
        return info_file(".", storage);
    }
}

void display_directories_content(spaces_t *storage, int ac)
{
    if (double_array_len(storage->global_file_space) == 0 &&
    double_array_len(storage->global_folder_space) == 1) {
        for (int i = 0; storage->global_folder_space[i] != NULL; i++) {
            open_folder(storage->global_folder_space[i], ac, storage->flags);
        }
    } else {
        for (int i = 0; storage->global_folder_space[i] != NULL; i++) {
            my_putstr(storage->global_folder_space[i]);
            my_putstr(":\n");
            open_folder(storage->global_folder_space[i], ac, storage->flags);
        }
    }
}

void display_directories_names(spaces_t *storage)
{
    for (int i = 0; storage->global_folder_space[i] != NULL; i++) {
        my_putstr(storage->global_folder_space[i]);
        my_putstr("  ");
    }
}
