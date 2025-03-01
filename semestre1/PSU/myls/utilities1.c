/*
** EPITECH PROJECT, 2024
** utilities1
** File description:
** useful functions
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

filetype_t const BITMASKS[7] = {
    {__S_IFBLK, &tmp_putstr, "block device\n"},
    {__S_IFCHR, &tmp_putstr, "character_device\n"},
    {__S_IFDIR, &put_in_folder_buffer, "directory\n"},
    {__S_IFIFO, &tmp_putstr, "FIFO/pipe\n"},
    {__S_IFLNK, &tmp_putstr, "symlink\n"},
    {__S_IFREG, &put_in_file_buffer, "regular file\n"},
    {__S_IFSOCK, &tmp_putstr, "socket\n"}
};

int put_in_folder_buffer(char const *pathname, spaces_t *storage, char *str)
{
    storage->global_folder_space[storage->folder_index] = my_strdup(pathname);
    (storage->folder_index)++;
    return 0;
}

int put_in_file_buffer(char const *pathname, spaces_t *storage, char *str)
{
    storage->global_file_space[storage->file_index] = my_strdup(pathname);
    (storage->file_index)++;
    return 0;
}

int tmp_putstr(char const *pathname, spaces_t *storage, char *str)
{
    my_putstr("Bitmask found but not handled => ");
    my_putstr(str);
}

int info_file(char const *pathname, spaces_t *storage)
{
    struct stat statbuf;
    int error_occured = 0;

    if (lstat(pathname, &statbuf) == -1) {
        my_puterr("ls: cannot access '");
        my_puterr(pathname);
        my_puterr("': No such file or directory\n");
        error_occured = 1;
        exit(84);
    }
    for (int i = 0; i < 7; i++) {
        if ((statbuf.st_mode & __S_IFMT) == BITMASKS[i].bitmask) {
            BITMASKS[i].function(pathname, storage, BITMASKS[i].description);
        }
    }
    if (error_occured == 1)
        return 84;
    else
        return 0;
}

void get_nb_file(int *nb_file, int ac, char **av)
{
    for (int i = 1; i < ac; i++) {
            if (av[i][0] != '-')
                (*nb_file)++;
    }
}
