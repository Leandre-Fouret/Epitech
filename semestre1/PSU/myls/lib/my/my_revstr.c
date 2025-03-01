/*
** EPITECH PROJECT, 2024
** my_revstr
** File description:
** Reverses a string
*/

#include <unistd.h>
#include "my.h"

char *my_revstr(char *str)
{
    int taille = 0;
    int tailleC;
    char stock;

    while (str[taille] != '\0'){
        taille++;
    }
    taille--;
    tailleC = taille;
    for (int lettre = 0; lettre <= taille / 2; lettre++){
        stock = str[lettre];
        str[lettre] = str[tailleC];
        str[tailleC] = stock;
        tailleC--;
    }
    return str;
}
