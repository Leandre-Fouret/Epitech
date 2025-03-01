/*
** EPITECH PROJECT, 2024
** my_find_prime_sup
** File description:
** finds the next prime
*/

#include "../../include/my.h"

int my_find_prime_sup(int nb)
{
    while (my_is_prime(nb) != 1) {
        nb++;
    }
    return nb;
}
