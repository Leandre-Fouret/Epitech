/*
** EPITECH PROJECT, 2024
** my_strdup
** File description:
** Duplicate a string
*/

#include <stdlib.h>

char *my_strdup(const char *str)
{
    int taille = 0;
    char *buffer;

    for (int i = 0; str[i] != '\0'; i++) {
        taille++;
    }
    buffer = malloc(sizeof(char) * taille);
    for (int i = 0; i < taille; i++) {
        buffer[i] = str[i];
    }
    buffer[taille] = '\0';
    return buffer;
}
