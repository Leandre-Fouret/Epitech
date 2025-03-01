/*
** EPITECH PROJECT, 2024
** my_radar
** File description:
** Update and handle the planes motion
*/

#include "radar.h"

static float calculate_distance(int dx, int dy, int ax, int ay)
{
    return sqrtf(powf(ax - dx, 2) + powf(ay - dy, 2));
}

static int has_reached_destination(airplane_t *plane)
{
    float distance = calculate_distance
        (plane->dx, plane->dy, plane->ax, plane->ay);

    return (distance < ARRIVAL_TOLERANCE);
}

static void update_plane_position(airplane_t *plane,
    float move_x, float move_y, float step)
{
    plane->dx += move_x * step;
    plane->dy += move_y * step;
    if ((move_x > 0 && plane->dx > plane->ax) ||
        (move_x < 0 && plane->dx < plane->ax)) {
        plane->dx = plane->ax;
    }
    if ((move_y > 0 && plane->dy > plane->ay) ||
        (move_y < 0 && plane->dy < plane->ay)) {
        plane->dy = plane->ay;
    }
    sfSprite_setPosition(plane->sprite, (sfVector2f){plane->dx, plane->dy});
    sfRectangleShape_setPosition(plane->box,
        (sfVector2f){plane->dx, plane->dy});
}

static void move_plane_step(airplane_t *plane)
{
    float dx = plane->ax - plane->dx;
    float dy = plane->ay - plane->dy;
    float distance = calculate_distance(plane->dx, plane->dy,
        plane->ax, plane->ay);
    float move_x;
    float move_y;

    if (distance < ARRIVAL_TOLERANCE) {
        plane->dx = plane->ax;
        plane->dy = plane->ay;
        sfSprite_setPosition(plane->sprite,
            (sfVector2f){plane->dx, plane->dy});
        sfRectangleShape_setPosition(plane->box,
            (sfVector2f){plane->dx, plane->dy});
        return;
    }
    move_x = dx / distance;
    move_y = dy / distance;
    update_plane_position(plane, move_x, move_y, plane->speed * 0.1);
}

static void delete_plane(airplane_t **air_storage, airplane_t *prev,
    airplane_t *to_delete)
{
    if (prev == NULL)
        *air_storage = to_delete->next;
    else
        prev->next = to_delete->next;
    sfSprite_destroy(to_delete->sprite);
    sfRectangleShape_destroy(to_delete->box);
    free(to_delete);
}

int update_positions(airplane_t **air_storage, sfTime delta)
{
    airplane_t *current = *air_storage;
    airplane_t *prev = NULL;
    airplane_t *to_delete;

    while (current != NULL) {
        if (current->delay <= delta.microseconds / 1000000)
            move_plane_step(current);
        if (has_reached_destination(current)) {
            to_delete = current;
            delete_plane(air_storage, prev, to_delete);
            current = prev ? prev->next : *air_storage;
        } else {
            prev = current;
            current = current->next;
        }
    }
    return 0;
}
