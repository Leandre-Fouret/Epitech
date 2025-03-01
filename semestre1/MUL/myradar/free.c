/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** Free functions
*/

#include "radar.h"

void free_towers(tower_t *curr_t, tower_t *tmp_t)
{
    while (curr_t != NULL) {
        tmp_t = curr_t;
        curr_t = curr_t->next;
        sfSprite_destroy(tmp_t->sprite);
        sfCircleShape_destroy(tmp_t->area);
        free(tmp_t);
    }
}

void free_all(airplane_t **airplane, tower_t **tower, sfTexture **tab_texture)
{
    airplane_t *tmp_a;
    airplane_t *curr_a = *airplane;
    tower_t *tmp_t = NULL;
    tower_t *curr_t = *tower;

    while (curr_a != NULL) {
        tmp_a = curr_a;
        curr_a = curr_a->next;
        sfSprite_destroy(tmp_a->sprite);
        sfRectangleShape_destroy(tmp_a->box);
        free(tmp_a);
    }
    free_towers(curr_t, tmp_t);
    sfTexture_destroy(tab_texture[0]);
    sfTexture_destroy(tab_texture[1]);
    free(tab_texture);
}
