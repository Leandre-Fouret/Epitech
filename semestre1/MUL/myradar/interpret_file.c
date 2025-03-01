/*
** EPITECH PROJECT, 2024
** my_radar
** File description:
** Add elements from the congig file
*/

#include "radar.h"

char *int_to_string(int num)
{
    int len = 0;
    int n = num;
    char *str;

    do {
        len++;
        n /= 10;
    } while (n > 0);
    str = (char *)malloc(len + 1);
    str[len] = '\0';
    for (int i = len - 1; i >= 0; i--) {
        str[i] = (num % 10) + '0';
        num /= 10;
    }
    return str;
}

static void get_info(char *buffer, char *line, int *i)
{
    int index = 0;

    memset(buffer, 0, sizeof(char) * 50);
    while (line[*i] != ' ' && line[*i] != '\n' && line[*i] != '\0') {
        buffer[index] = line[*i];
        (*i)++;
        index++;
    }
}

static void add_plane_to_storage(airplane_t *new, int info, int arg_index)
{
    switch (arg_index) {
    case 0:
        new->dx = info;
        break;
    case 1:
        new->dy = info;
        break;
    case 2:
        new->ax = info;
        break;
    case 3:
        new->ay = info;
        break;
    case 4:
        new->speed = info;
        break;
    case 5:
        new->delay = info;
        break;
    }
}

static void add_tower_to_storage(tower_t *new, int info, int arg_index)
{
    switch (arg_index) {
    case 0:
        new->x = info;
        break;
    case 1:
        new->y = info;
        break;
    case 2:
        new->radius = info * 2;
        break;
    }
}

void get_airplane(airplane_t **air_storage, char *line)
{
    char *buffer = malloc(sizeof(char) * 50);
    int info;
    airplane_t *new_plane = malloc(sizeof(airplane_t));
    int arg_index = 0;

    if (new_plane == NULL || buffer == NULL)
        return;
    for (int i = 2; line[i] != '\n' && line[i] != '\0'; i++) {
        if (my_isdigit(line[i])) {
            get_info(buffer, line, &i);
            info = my_getnbr(buffer);
            add_plane_to_storage(new_plane, info, arg_index);
            arg_index++;
        }
    }
    free(buffer);
    new_plane->next = *air_storage;
    *air_storage = new_plane;
}

void get_tower(tower_t **tow_storage, char *line)
{
    char *buffer = malloc(sizeof(char) * 50);
    int info;
    tower_t *new_tower = malloc(sizeof(tower_t));
    int arg_index = 0;

    if (buffer == NULL || new_tower == NULL)
        return;
    for (int i = 2; line[i] != '\n' && line[i] != '\0'; i++) {
        if (my_isdigit(line[i])) {
            new_tower->clock = sfClock_create();
            get_info(buffer, line, &i);
            info = my_getnbr(buffer);
            add_tower_to_storage(new_tower, info, arg_index);
            arg_index++;
        }
    }
    free(buffer);
    new_tower->next = *tow_storage;
    *tow_storage = new_tower;
}

int extract_file_infos(char *path,
    airplane_t **air_storage, tower_t **tow_storage)
{
    FILE *stream;
    size_t len = 0;
    int nread = 0;
    char *line = NULL;

    stream = fopen(path, "r");
    nread = getline(&line, &len, stream);
    while (nread != -1) {
        if (*line == 'A')
            get_airplane(air_storage, line);
        if (*line == 'T')
            get_tower(tow_storage, line);
        nread = getline(&line, &len, stream);
    }
    free(line);
    fclose(stream);
    return 0;
}
