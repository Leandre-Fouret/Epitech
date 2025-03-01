/*
** EPITECH PROJECT, 2024
** my_compute_square_root
** File description:
** returns the square root of a number
*/

#include "../../include/my.h"

int my_compute_square_root(int nb)
{
    int i = 1;

    while (my_compute_power_rec(i, 2) < nb) {
        i++;
    }
    if (my_compute_power_rec(i, 2) == nb)
        return i;
    return 0;
}
