/*
** EPITECH PROJECT, 2024
** settingup
** File description:
** settingup
*/

#include "my.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "setup.h"

int get_nb_cols(char *map_buffer)
{
    int nb = 0;
    int index = 0;

    while (map_buffer[index] != '\n' && map_buffer[index] != '\0')
        index++;
    index++;
    while (map_buffer[index] != '\n' && map_buffer[index] != '\0') {
        nb++;
        index++;
    }
    return nb;
}

void display_double_array(char **map_array, int nb_cols)
{
    for (int i = 0; map_array[i] != NULL; i++) {
        write(1, map_array[i], nb_cols);
        my_putchar('\n');
    }
}

void put_map_in_array(char *map_buffer, char **map_array, int nb_lines)
{
    int nb_cols = get_nb_cols(map_buffer);
    int index = 0;

    while (map_buffer[index] != '\n')
        index++;
    index++;
    for (int ligne = 0; ligne < nb_lines; ligne++) {
        map_array[ligne] = malloc(sizeof(char) * (nb_cols + 1));
        for (int lettre = 0; lettre < nb_cols; lettre++) {
            map_array[ligne][lettre] = map_buffer
                [(nb_cols + 1) * ligne + index + lettre];
        }
    }
}

void launch_principal_functions(maps_t *maps, int nb_lines,
    int nb_cols, biggest_t *bsq)
{
    find_squares(maps, nb_lines, nb_cols, bsq);
    replace_square(maps, bsq);
    display_double_array(maps->map_array, nb_cols);
}

static int verif_empty(char **av, int size)
{
    int pt = 0;

    if (my_strlen(av[2]) == 0) {
        return -1;
    }
    for (int i = 0; i < my_strlen(av[2]); i++) {
        if (av[2][i] == '.')
            pt++;
    }
    if (pt == my_strlen(av[2]))
        return 1;
    return 0;
}

static int three_args(char **av, char **map)
{
    if (my_getnbr(av[1]) <= 0)
            return 84;
    map = malloc(sizeof(char *) * my_getnbr(av[1]));
    if (verif_empty(av, my_getnbr(av[1])) == -1)
        return 0;
    if (verif_empty(av, my_getnbr(av[1]))) {
        gen_empty(my_getnbr(av[1]), map);
        display_double_array(map, my_getnbr(av[1]));
        return 0;
    } else if (my_getnbr(av[1]) > 2500)
        return 84;
    else
        generate_map(my_getnbr(av[1]), av[2], av, map);
    return settingup2(my_getnbr(av[1]), av, map);
}

int main(int ac, char **av)
{
    char **map;

    if (ac == 2) {
        if (open(av[1], O_RDONLY) == -1)
            return 84;
        return settingup1(ac, av);
    }
    if (ac == 3) {
        if (my_strlen(av[2]) == 0)
            return 84;
        return three_args(av, map);
    }
    return 84;
}
