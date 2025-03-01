/*
** EPITECH PROJECT, 2024
** my_compute_power_rec
** File description:
** recursive function raising to a power
*/

#include "../../include/my.h"

int my_compute_power_rec(int nb, int p)
{
    int result = nb;

    if (p < 0)
        return 0;
    if (p == 0)
        return 1;
    result = (my_compute_power_rec(nb, p - 1) * nb);
    return result;
}
