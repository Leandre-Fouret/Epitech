/*
** EPITECH PROJECT, 2024
** my_compute_square_root
** File description:
** Returns the square root of the number given as argument
*/

#include "my.h"

int my_compute_square_root(int nb)
{
    int p = 0;

    if (nb > 2147483647 || nb < -2147483648)
        return 0;
    if (nb < 0)
        return 0;
    if (nb == 1)
        return 1;
    while (p * p != nb){
        p++;
        if (p == nb){
            return 0;
        }
    }
    if (p > 2147483647 || p < -2147483648)
        return 0;
    return p;
}
