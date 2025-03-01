/*
** EPITECH PROJECT, 2024
** my_find_prime_sup
** File description:
** Returns the smallest prime number greater or equal to arg
*/

#include "my.h"

int my_find_prime_sup(int nb)
{
    if (nb > 2147483647 || nb < -2147483648){
        return 0;
    }
    while (my_is_prime(nb) == 0){
        nb++;
    }
    if (nb > 2147483647 || nb < -2147483648){
        return 0;
    }
    return nb;
}
