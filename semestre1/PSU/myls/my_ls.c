/*
** EPITECH PROJECT, 2024
** lyls
** File description:
** Recode the ls shell command
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

// Here, check for the 'd' flag
void display_all(spaces_t *storage, int ac)
{
    if (double_array_len(storage->global_file_space) > 0) {
        for (int i = 0; storage->global_file_space[i] != NULL; i++) {
            my_putstr(storage->global_file_space[i]);
            my_putstr("  ");
        }
        if (storage->flags[3] == 0)
            my_putchar('\n');
    }
    if (storage->flags[3] == 0)
        display_directories_content(storage, ac);
    else
        display_directories_names(storage);
}

int double_array_len(char **tab)
{
    int size = 0;

    for (int i = 0; tab[i] != NULL; i++) {
        size++;
    }
    return size;
}

int open_folder(char const *pathname, int ac, int *flags_storage)
{
    DIR *streamfold = opendir(pathname);
    struct dirent *entry;

    if (streamfold == NULL)
        exit(84);
    entry = readdir(streamfold);
    while (entry != NULL) {
        output_flags(flags_storage, entry);
        entry = readdir(streamfold);
    }
    closedir(streamfold);
    my_putchar('\n');
    return 0;
}

int handle_main(char **av, int ac)
{
    spaces_t storage;
    int nb_file = 0;
    int error_occured = 0;

    get_nb_file(&nb_file, ac, av);
    storage.folder_index = 0;
    storage.global_folder_space = malloc(ac - 1);
    storage.file_index = 0;
    storage.global_file_space = malloc(ac - 1);
    storage.flags = malloc(sizeof(int) * 6);
    for (int i = 0; i < 6; i++)
        storage.flags[i] = 0;
    find_flags(av, &storage);
    if (choose_which_file(av, ac, nb_file, &storage) == 84)
        error_occured = 1;
    display_all(&storage, ac);
    if (error_occured == 1)
        return 84;
    else
        return 0;
}
//call a free_all function in the handle_main function

int main(int ac, char **av)
{
    return handle_main(av, ac);
}
