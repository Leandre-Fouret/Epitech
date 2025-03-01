/*
** EPITECH PROJECT, 2024
** my_radar
** File description:
** Check and handle collisions between planes and tower control
*/

#include "radar.h"

static void delete_found_plane(airplane_t **air_storage,
    airplane_t *to_free, airplane_t *prev_a)
{
    if (prev_a == NULL)
        *air_storage = to_free->next;
    else
        prev_a->next = to_free->next;
    sfSprite_destroy(to_free->sprite);
    sfRectangleShape_destroy(to_free->box);
    free(to_free);
}

// table : prev1 prev2 to_delete1 to_delete2
static void delete_planes(airplane_t **air_storage, airplane_t **table)
{
    airplane_t *tmp_a = *air_storage;
    airplane_t *prev_a = NULL;
    airplane_t *to_free = NULL;

    while (tmp_a != NULL) {
        if (tmp_a == table[2] || tmp_a == table[3]) {
            to_free = tmp_a;
            tmp_a = tmp_a->next;
            delete_found_plane(air_storage, to_free, prev_a);
            continue;
        }
        prev_a = tmp_a;
        tmp_a = tmp_a->next;
    }
}

static int in_collision(airplane_t *current_a, airplane_t *tmp_a)
{
    sfVector2f position1 = sfRectangleShape_getPosition(current_a->box);
    sfVector2f position2 = sfRectangleShape_getPosition(tmp_a->box);
    int over_x = position1.x < position2.x + 20 &&
        position1.x + 20 > position2.x;
    int over_y = position1.y < position2.y + 20 &&
        position1.y + 20 > position2.y;

    return over_x && over_y;
}

static int collide_in_tower(tower_t *tower, airplane_t **table)
{
    sfVector2f position1 = sfRectangleShape_getPosition(table[2]->box);
    sfVector2f position_t = sfCircleShape_getPosition(tower->area);
    int radius_t = sfCircleShape_getRadius(tower->area);
    int close_x = fmax(position1.x, fmin(position_t.x, position1.x + 20));
    int close_y = fmax(position1.y, fmin(position_t.y, position1.y + 20));
    int dist_x = close_x - position_t.x;
    int dist_y = close_y - position_t.y;

    return (dist_x * dist_x + dist_y * dist_y) <=
        my_compute_power_rec(radius_t, 2);
}

static int look_in_towers(airplane_t **air_storage, tower_t **tow_storage,
    airplane_t **table)
{
    tower_t *tmp_t = *tow_storage;

    while (tmp_t != NULL) {
        if (collide_in_tower(tmp_t, table)) {
            return 0;
        }
        tmp_t = tmp_t->next;
    }
    delete_planes(air_storage, table);
    return 1;
}

static int check_subplane(struct window_settings *my_set,
    airplane_t *current_a, airplane_t ***planes_infos, tower_t **tow_storage)
{
    sfTime delta;

    delta = sfClock_getElapsedTime(my_set->main_clock);
    if (delta.microseconds / 1000000 >= (*(planes_infos[2]))->delay) {
        if (in_collision(current_a, *(planes_infos[2]))) {
            planes_infos[1][2] = current_a;
            planes_infos[1][3] = *(planes_infos[2]);
            return look_in_towers(planes_infos[0],
                tow_storage, planes_infos[1]);
        }
    }
    return -1;
}

static int look_for_others(airplane_t ***planes_infos, tower_t **tow_storage,
    airplane_t *current_a, struct window_settings *my_set)
{
    airplane_t *tmp_a = *(planes_infos[0]);
    int result = 0;

    while (tmp_a != NULL) {
        if (tmp_a == current_a) {
            tmp_a = tmp_a->next;
            continue;
        }
        planes_infos[2] = &tmp_a;
        result = check_subplane(my_set, current_a, planes_infos, tow_storage);
        if (result == -1) {
            planes_infos[1][1] = tmp_a;
            tmp_a = tmp_a->next;
        }
        if (result == 0 || result == 1)
            return result;
    }
    return -1;
}

void check_collisions(struct window_settings *my_set,
    airplane_t **air_storage, tower_t **tow_storage)
{
    airplane_t *current_a = *air_storage;
    airplane_t *table[4] = {NULL, NULL, NULL, NULL};
    airplane_t **planes_infos[3] = {air_storage, table, NULL};
    airplane_t *next_a = NULL;
    sfTime delta;

    table[0] = NULL;
    while (current_a != NULL) {
        next_a = current_a->next;
        delta = sfClock_getElapsedTime(my_set->main_clock);
        if (delta.microseconds / 1000000 >= current_a->delay) {
            look_for_others(planes_infos, tow_storage,
                current_a, my_set);
        }
        current_a = next_a;
    }
}
