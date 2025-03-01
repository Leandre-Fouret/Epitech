/*
** EPITECH PROJECT, 2024
** my_radar
** File description:
** header file
*/

#ifndef MY_RADAR
    #define MY_RADAR
    #include <SFML/Graphics.h>
    #include <SFML/System.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <sys/stat.h>
    #include <stdio.h>
    #include <string.h>
    #include <ctype.h>
    #include <math.h>
    #include "my.h"
    #define ARRIVAL_TOLERANCE 8


typedef struct airplane_s {
    int dx;
    int dy;
    int ax;
    int ay;
    int speed;
    int delay;
    sfSprite *sprite;
    sfRectangleShape *box;
    struct airplane_s *next;
} airplane_t;

typedef struct tower_s {
    int x;
    int y;
    int radius;
    sfSprite *sprite;
    sfCircleShape *area;
    sfClock *clock;
    struct tower_s *next;
} tower_t;

struct window_settings {
    sfRenderWindow *main_window;
    sfSprite *map_sprite;
    sfClock *main_clock;
    sfText *time_counter;
};

struct motion_settings {
    airplane_t **air_storage;
    tower_t **tow_storage;
    airplane_t *current_a;
    airplane_t **table;
};

//Functions
int verify_file(char *path);
int extract_file_infos(char *path,
    airplane_t **air_storage, tower_t **tow_storage);
void free_all(airplane_t **airplane, tower_t **tower, sfTexture **tab_texture);
int my_isdigit(char c);
sfTexture **init_elements(airplane_t **air_storage, tower_t **tow_storage);
int update_positions(airplane_t **air_storage, sfTime delta);
void check_collisions(struct window_settings *my_set,
    airplane_t **air_storage, tower_t **tow_storage);
void free_towers(tower_t *curr_t, tower_t *tmp_t);
char *int_to_string(int num);

#endif
