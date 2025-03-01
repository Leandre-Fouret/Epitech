/*
** EPITECH PROJECT, 2024
** my_put_nbr
** File description:
** displays the number given as a parameter
*/

#include "../../include/my.h"

static int checkn(int n2)
{
    if (n2 == -2147483648) {
        my_putchar('-');
        my_putchar('2');
        return my_put_nbr(147483648);
    } else if (n2 == 2147483647) {
        my_putchar('2');
        return my_put_nbr(147483647);
    }
    return 0;
}

static int check0(int nb)
{
    if (nb == 0) {
        my_putchar('0');
        return 0;
    } else if (nb == -2147483648 || nb == 2147483647) {
        checkn(nb);
        return 0;
    } else {
        return 1;
    }
    return 1;
}

int my_put_nbr(int nb)
{
    if (check0(nb) == 0){
        return 0;
    }
    if (nb < 0) {
        my_putchar('-');
        nb = nb * -1;
    }
    if (nb < 10) {
        my_putchar(48 + nb);
        return 0;
    }
    my_put_nbr(nb / 10);
    my_putchar(48 + nb % 10);
    return 0;
}
