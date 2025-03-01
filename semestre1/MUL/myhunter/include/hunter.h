/*
** EPITECH PROJECT, 2024
** hunter
** File description:
** headers
*/

#ifndef MYHUNTER
    #define MYHUNTER
    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>

typedef struct bat {
    sfTexture *texture;
    sfSprite *sprite;
    sfVector2f position;
    sfIntRect rect;
    int isdead;
    struct bat *next;
} bat_t;

typedef struct player {
    int score;
    sfText *score_text;
    sfText *tmp_score;
    int missed;
    sfFont *font;
} player_t;

typedef struct game_system {
    sfVideoMode *mode;
    sfRenderWindow *main_window;
    sfEvent event;
    bat_t *bats;
    sfClock *clock;
    sfClock *bat_clock;
    sfTime mytime;
    sfTime bat_time;
    float seconds;
    float bat_seconds;
    sfSprite *background;
    sfVector2f position;
    sfMusic *music;
    player_t *score;
} game_sys_t;

int create_bat(bat_t **mybat, sfVector2f position);
void draw_bats(bat_t **bats, sfRenderWindow *main_window, player_t *scores);
void move_rect(bat_t **bats, int offset, int max_value);
void delete_dead_bats(bat_t **bats);
int update_clocks(game_sys_t *storage);
void display_h_menu(void);
void set_cursor(sfRenderWindow *main_window);
void update_score(player_t *scores);
void store_texts(player_t *scores, sfFont *font, game_sys_t *storage);
int launch_sound(char *path, int repeat, game_sys_t *storage);

#endif
