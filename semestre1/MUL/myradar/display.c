/*
** EPITECH PROJECT, 2024
** my_radar
** File description:
** Manage the display of all the planes and towers
*/

#include "radar.h"

void textures_for_planes(sfSprite *tmp_sprite, sfTexture *plane_texture,
    sfTexture *reverse_texture, airplane_t *plane)
{
    if (plane->dx < plane->ax)
        sfSprite_setTexture(tmp_sprite, plane_texture, sfTrue);
    else
        sfSprite_setTexture(tmp_sprite, reverse_texture, sfTrue);
}

void init_planes(airplane_t **air_storage, sfTexture *plane_texture,
    sfTexture *reverse_texture)
{
    airplane_t *a_tmp = *air_storage;
    sfSprite *tmp_sprite;
    sfRectangleShape *box;

    while (a_tmp != NULL) {
        tmp_sprite = sfSprite_create();
        box = sfRectangleShape_create();
        textures_for_planes(tmp_sprite, plane_texture, reverse_texture, a_tmp);
        sfSprite_setPosition(tmp_sprite, (sfVector2f){a_tmp->dx, a_tmp->dy});
        sfSprite_setScale(tmp_sprite, (sfVector2f){0.07, 0.07});
        sfRectangleShape_setPosition(box, (sfVector2f){a_tmp->dx, a_tmp->dy});
        sfRectangleShape_setOutlineColor(box, sfGreen);
        sfRectangleShape_setFillColor(box, sfTransparent);
        sfRectangleShape_setOutlineThickness(box, 1);
        sfRectangleShape_setSize(box, (sfVector2f){20, 20});
        a_tmp->sprite = tmp_sprite;
        a_tmp->box = box;
        a_tmp = a_tmp->next;
    }
}

void set_circle(sfCircleShape *area, tower_t *t_tmp)
{
    sfCircleShape_setPosition(area, (sfVector2f)
            {t_tmp->x + (45.0f / 2.0f), t_tmp->y + (45.0f / 2.0f)});
    sfCircleShape_setRadius(area, t_tmp->radius * 2);
        sfCircleShape_setFillColor(area, sfTransparent);
        sfCircleShape_setOutlineColor(area, sfRed);
        sfCircleShape_setOutlineThickness(area, 2);
        sfCircleShape_setOrigin(area, (sfVector2f)
            {t_tmp->radius * 2, t_tmp->radius * 2});
}

void init_towers(tower_t **tow_storage, sfTexture *tower_texture)
{
    tower_t *t_tmp = *tow_storage;
    sfSprite *tmp_sprite;
    sfCircleShape *area;

    while (t_tmp != NULL) {
        tmp_sprite = sfSprite_create();
        area = sfCircleShape_create();
        sfSprite_setTexture(tmp_sprite, tower_texture, sfTrue);
        sfSprite_setPosition(tmp_sprite, (sfVector2f){t_tmp->x, t_tmp->y});
        sfSprite_setScale(tmp_sprite, (sfVector2f){0.1, 0.1});
        set_circle(area, t_tmp);
        t_tmp->sprite = tmp_sprite;
        t_tmp->area = area;
        t_tmp = t_tmp->next;
    }
}

sfTexture **init_elements(airplane_t **air_storage, tower_t **tow_storage)
{
    sfTexture **tab_texture = malloc(sizeof(sfTexture *) * 3);
    sfTexture *plane_texture =
        sfTexture_createFromFile("assets/plane.png", NULL);
    sfTexture *tower_texture =
        sfTexture_createFromFile("assets/tower.png", NULL);
    sfTexture *reverse_texture =
        sfTexture_createFromFile("assets/reverse.png", NULL);

    if (!tab_texture)
        return NULL;
    memset(tab_texture, 0, sizeof(sfTexture *) * 2);
    init_planes(air_storage, plane_texture, reverse_texture);
    init_towers(tow_storage, tower_texture);
    tab_texture[0] = plane_texture;
    tab_texture[1] = tower_texture;
    tab_texture[2] = reverse_texture;
    return tab_texture;
}
