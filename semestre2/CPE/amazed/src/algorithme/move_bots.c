/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** move_bots
*/

#include "amazed.h"
#include <stdbool.h>

static char *search_name(room_t **rooms, int index)
{
    room_t *current = *rooms;
    int i = 0;

    for (; current; current = current->next) {
        if (current->name[0] == '#')
            continue;
        if (i == index)
            return current->name;
        i++;
    }
    return NULL;
}

static int len_best_path(amazed_t *params)
{
    int len = 0;

    for (int i = 0; params->best_path[i] != -1; i++) {
        len++;
    }
    return len;
}

static void print_moves(room_t **rooms, amazed_t *params, int lap, int i)
{
    if (search_name(rooms, params->best_path[(lap - 1) - i]) != NULL) {
        my_printf("P%d-%s", i + 1, search_name(
            rooms, params->best_path[(lap - 1) - i]));
        if (i < lap - 1 && i < params->nb_bots - 1)
            my_printf(" ");
    }
}

void output_bots(amazed_t *params, room_t **rooms)
{
    int *new = NULL;
    int len = len_best_path(params);

    if (params->nb_bots > len) {
        new = malloc(sizeof(int) * (params->nb_bots + 1));
        if (new == NULL)
            return;
        for (int i = 0; i < len; i++)
            new[i] = params->best_path[i];
        for (int i = len; i < params->nb_bots + 1; i++)
            new[i] = -1;
        free(params->best_path);
        params->best_path = new;
    }
    for (int lap = 1; lap < params->nb_bots + 2; lap++) {
        for (int i = 0; i < lap && i < params->nb_bots; i++)
            print_moves(rooms, params, lap, i);
        my_printf("\n");
    }
    free(params->best_path);
}
