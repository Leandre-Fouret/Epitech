/*
** EPITECH PROJECT, 2024
** settingup_func
** File description:
** Contains the two main settingup functions
*/

#include "my.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "setup.h"

void settingup1_bis(maps_t *maps, biggest_t *bsq, int *mapfd)
{
    int nb_lines = 0;
    int nb_cols = 0;
    char **map_array;

    nb_lines = my_getnbr(maps->map_buffer);
    nb_cols = get_nb_cols(maps->map_buffer);
    map_array = malloc(sizeof(char *) * (nb_lines + 1));
    put_map_in_array(maps->map_buffer, map_array, nb_lines);
    maps->map_array = map_array;
    launch_principal_functions(maps, nb_lines, nb_cols, bsq);
    close_and_free(mapfd, maps);
}

int settingup1(int ac, char **av)
{
    struct stat sb;
    biggest_t bsq = {0, 0, 0};
    maps_t maps;
    int mapfd = open(av[1], O_RDONLY);
    int i = 0;

    stat(av[1], &sb);
    if (sb.st_size == 0)
        return 84;
    maps.map_buffer = malloc(sizeof(char) * sb.st_size);
    if (read(mapfd, maps.map_buffer, sb.st_size) == -1)
        return 84;
    if (my_getnbr(maps.map_buffer) > 3000)
        return 84;
    settingup1_bis(&maps, &bsq, &mapfd);
    return 0;
}

int settingup2(int size, char **av, char **map_array)
{
    int nb_lines = size;
    int nb_cols = size;
    biggest_t bsq = {0, 0, 0};
    maps_t maps = {av[1], map_array};
    int mapfd = open(av[1], O_RDONLY);

    for (int i = 0; i < size; i++) {
        if (map_array[0][i] != '.' && map_array[0][i] != 'o')
            return 84;
    }
    find_squares(&maps, nb_lines, nb_cols, &bsq);
    replace_square(&maps, &bsq);
    display_double_array(maps.map_array, nb_cols);
    free(map_array);
    return 0;
}
