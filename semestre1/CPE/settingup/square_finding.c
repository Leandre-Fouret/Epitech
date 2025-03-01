/*
** EPITECH PROJECT, 2024
** square_finding
** File description:
** Find the biggest square
*/

#include "my.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "setup.h"

int check_not_square(maps_t *maps, int i, int colonne, int size)
{
    if (my_strlen(maps->map_array[i]) < colonne + size)
        return -1;
    for (int j = colonne; j < colonne + size; j++) {
        if (maps->map_array[i][j] != '.')
            return -1;
    }
}

int check_square(maps_t *maps, int ligne, int colonne, int size)
{
    if (my_getnbr(maps->map_buffer) < ligne + size)
        return -1;
    for (int i = ligne; i < ligne + size; i++) {
        if (check_not_square(maps, i, colonne, size) == -1)
            return -1;
    }
    return 1;
}

void pre_check_square_loop(maps_t *maps, int ligne,
    int colonne, biggest_t *bsq)
{
    int size = 0;
    int tmp_col = colonne;

    for (; maps->map_array[ligne][tmp_col] == '.'; size++)
        tmp_col++;
        if (size < bsq->size)
            return;
        while (check_square(maps, ligne, colonne, size) == -1)
            size--;
        if (size > bsq->size) {
            bsq->size = size;
            bsq->line = ligne;
            bsq->col = colonne;
        }
        size = 0;
}

void pre_check_square(maps_t *maps, int ligne, int colonne, biggest_t *bsq)
{
    if (maps->map_array[ligne][colonne] == '.') {
        pre_check_square_loop(maps, ligne, colonne, bsq);
    }
}

void find_squares(maps_t *maps, int nb_lines, int nb_cols, biggest_t *bsq)
{
    for (int ligne = 0; ligne < nb_lines; ligne++) {
        for (int colonne = 0; colonne < nb_cols; colonne++) {
            pre_check_square(maps, ligne, colonne, bsq);
        }
    }
}
