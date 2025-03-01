/*
** EPITECH PROJECT, 2024
** my_isneg
** File description:
** Shows if int argument is negative or positive
*/

#include <unistd.h>
#include "my.h"

int my_isneg(int n)
{
    if (n < 0) {
        my_putchar('N');
    } else {
        my_putchar('P');
    }
    my_putchar('\n');
    return 0;
}
