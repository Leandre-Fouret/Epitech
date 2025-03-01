/*
** EPITECH PROJECT, 2024
** find_flags
** File description:
** find several flags of the my_ls command
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

//Flags are : a l R d r t

void check_flag(char *str, spaces_t *storage)
{
    int i = 1;

    while (str[i] == 'a' || str[i] == 'l' || str[i] == 'R' ||
        str[i] == 'd' || str[i] == 'r' || str[i] == 't') {
            if (str[i] == 'a')
                storage->flags[0] = 1;
            if (str[i] == 'l')
                storage->flags[1] = 1;
            if (str[i] == 'R')
                storage->flags[2] = 1;
            if (str[i] == 'd')
                storage->flags[3] = 1;
            if (str[i] == 'r')
                storage->flags[4] = 1;
            if (str[i] == 't')
                storage->flags[5] = 1;
        i++;
    }
}

void display_flags(spaces_t *storage)
{
    for (int i = 0; i < 6; i++) {
        my_put_nbr(storage->flags[i]);
    }
}

void find_flags(char **av, spaces_t *storage)
{
    for (int i = 0; av[i] != NULL; i++) {
        if (av[i][0] == '-')
            check_flag(av[i], storage);
    }
}

void output_flags(int *flags_storage, struct dirent *entry)
{
    if (flags_storage[0]) {
            my_putstr(entry->d_name);
            my_putchar(' ');
        } else {
            if (entry->d_name[0] != '.') {
                my_putstr(entry->d_name);
            my_putchar(' ');
            }
        }
}
