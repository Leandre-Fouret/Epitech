/*
** EPITECH PROJECT, 2024
** my_compute_power_rec
** File description:
** Raises nb to the power of p
*/

#include "my.h"

int my_compute_power_rec(int nb, int p)
{
    long int retour = nb;

    if (p < 0) {
        return 0;
    } else if (p == 0) {
        return 1;
    }
    if (p == 1) {
        return retour;
    }
    retour = nb * my_compute_power_rec(nb, p - 1);
    if (retour > 2147483647 || retour < -2147483648){
        return 0;
    }
    return retour;
}
