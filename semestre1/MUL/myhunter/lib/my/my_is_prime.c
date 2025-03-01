/*
** EPITECH PROJECT, 2024
** my_is_prime
** File description:
** Is 1 if the number given as argument is prime, else 0
*/

#include "my.h"

int my_is_prime(int nb)
{
    if (nb > 2147483647 || nb < -2147483648){
        return 0;
    }
    if (nb <= 1){
        return 0;
    }
    for (int i = 2; i < nb; i++){
        if (nb % i == 0){
            return 0;
        }
    }
    return 1;
}
