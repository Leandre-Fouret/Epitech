/*
** EPITECH PROJECT, 2024
** my_swap
** File description:
** Swap the content of two integers with the adresses
*/

#include <unistd.h>
#include "my.h"

void my_swap(int *a, int *b)
{
    int stock = *b;

    *b = *a;
    *a = stock;
}
