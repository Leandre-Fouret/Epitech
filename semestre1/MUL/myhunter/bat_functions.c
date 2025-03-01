/*
** EPITECH PROJECT, 2024
** bat_functions
** File description:
** functions about the bat
*/

#include "my.h"
#include <SFML/Graphics.h>
#include <stdlib.h>
#include "hunter.h"
#include <time.h>

int create_bat(bat_t **mybat, sfVector2f position)
{
    sfSprite *bat_sprite = sfSprite_create();
    sfIntRect rect = {-30, 0, 28, 26};
    sfTexture *bat_texture = sfTexture_createFromFile
    ("assets/imagebat.png", NULL);
    sfVector2f scale = {5, 5};
    bat_t *new = malloc(sizeof(bat_t));

    if (!bat_texture)
        return 84;
    sfSprite_setScale(bat_sprite, scale);
    sfSprite_setTexture(bat_sprite, bat_texture, sfTrue);
    sfSprite_setTextureRect(bat_sprite, rect);
    new->texture = bat_texture;
    new->sprite = bat_sprite;
    new->rect = rect;
    new->position = position;
    new->isdead = 0;
    new->next = *mybat;
    *mybat = new;
    return 0;
}

void delete_dead_bats(bat_t **bats)
{
    bat_t *tmp = *bats;
    bat_t *prev = *bats;

    if (bats == NULL || *bats == NULL) {
        return;
    }
    if (tmp != NULL && tmp->isdead) {
        *bats = tmp->next;
        free(tmp);
        return;
    }
    while (tmp != NULL && tmp->isdead == 0) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return;
    prev->next = tmp->next;
    free(tmp);
}

void draw_bats(bat_t **bats, sfRenderWindow *main_window, player_t *scores)
{
    bat_t *tmp = *bats;

    while (tmp != NULL) {
        if (tmp->position.x > 1920) {
            tmp->isdead = 1;
            scores->missed++;
        }
        sfRenderWindow_drawSprite(main_window, tmp->sprite, NULL);
        tmp = tmp->next;
    }
}

void move_rect(bat_t **bats, int offset, int max_value)
{
    bat_t *tmp = *bats;

    while (tmp != NULL) {
        tmp->rect.left += offset;
        if (tmp->rect.left >= max_value - offset)
            tmp->rect.left = 0;
        tmp->position.x += 40;
        sfSprite_setPosition(tmp->sprite, tmp->position);
        sfSprite_setTextureRect(tmp->sprite, tmp->rect);
        tmp = tmp->next;
    }
}

int update_clocks(game_sys_t *storage)
{
    if (storage->seconds > 0.15) {
        move_rect(&(storage->bats), 28, 85);
        sfClock_restart(storage->clock);
    }
    if (storage->bat_seconds > 0.5) {
        storage->position.x = 0;
        storage->position.y = rand() % 990;
        if (create_bat(&(storage->bats), storage->position) == 84)
            return 84;
        sfClock_restart(storage->bat_clock);
    }
    return 0;
}
