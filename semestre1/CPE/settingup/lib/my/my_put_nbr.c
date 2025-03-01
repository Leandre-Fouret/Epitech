/*
** EPITECH PROJECT, 2024
** my_put_nbr
** File description:
** Displays the values of an integer
*/

#include <unistd.h>
#include "my.h"

static void strict_pos(int nb, long inc, int nb_dizaines, long *result)
{
    int i = 0;

    while ((nb / inc) != 0){
        inc = inc * 10;
        nb_dizaines++;
    }
    nb_dizaines--;
    while (i <= nb_dizaines) {
        *result = '0' + (nb % inc / (inc / 10));
        inc = inc / 10;
        my_putchar(*result);
        i++;
    }
}

int my_put_nbr(int nb)
{
    long inc = 1;
    int nb_dizaines = 0;
    long result;

    if (nb < 0){
        my_putchar('-');
        nb = (-1 * nb);
    }
    strict_pos(nb, inc, nb_dizaines, &result);
    if (nb == 0){
        my_putchar('0');
    }
    my_putchar('\n');
    return 0;
}
