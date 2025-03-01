/*
** EPITECH PROJECT, 2024
** map
** File description:
** map generation and modification
*/

#include "my.h"
#include "setup.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void gen_empty(int size, char **map)
{
    char *tmp;

    for (int i = 0; i < size; i++) {
        tmp = malloc(sizeof(char) * size);
        for (int j = 0; j < size; j++) {
            tmp[j] = 'x';
        }
        map[i] = tmp;
    }
    map[size] = NULL;
}

void replace_square(maps_t *maps, biggest_t *bsq)
{
    for (int i = bsq->line; i < bsq->line + bsq->size; i++) {
        for (int j = bsq->col; j < bsq->col + bsq->size; j++) {
            maps->map_array[i][j] = 'x';
        }
    }
}

void close_and_free(int *mapfd, maps_t *maps)
{
    close(*mapfd);
    for (int i = 0; i < my_getnbr(maps->map_buffer); i++) {
        free(maps->map_array[i]);
    }
    free(maps->map_buffer);
}

void restart_pattern(int *index, char **av)
{
    if (*index == my_strlen(av[2]))
        *index = 0;
}

void generate_map(int size, char *pattern, char **av, char **map)
{
    int total = (size * size) + size;
    int index = 0;
    char *tmp;

    for (int i = 0; i < size; i++) {
        tmp = malloc(sizeof(char) * size + 1);
        for (int j = 0; j < size; j++) {
            tmp[j] = pattern[index];
            index++;
            restart_pattern(&index, av);
        }
        tmp[size] = '\0';
        map[i] = tmp;
    }
    map[size] = NULL;
}
