/*
** EPITECH PROJECT, 2024
** myhunter
** File description:
** myhunter
*/

#include "my.h"
#include <SFML/Graphics.h>
#include <stdlib.h>
#include "hunter.h"
#include <time.h>

int iscollision(bat_t **bats, sfMouseButtonEvent event,
    player_t *scores, game_sys_t *storage)
{
    bat_t *tmp = *bats;
    sfFloatRect bat_bounds;
    sfVector2f click_pos;
    sfVector2i pixel_pos = {event.x, event.y};

    while (tmp != NULL) {
        click_pos = sfRenderWindow_mapPixelToCoords
            (storage->main_window, pixel_pos, NULL);
        bat_bounds = sfSprite_getGlobalBounds(tmp->sprite);
        if (sfFloatRect_contains(&bat_bounds, click_pos.x, click_pos.y)) {
            tmp->isdead = 1;
            scores->score++;
        }
        tmp = tmp->next;
    }
}

void analyze_event(game_sys_t *storage, sfEvent *event, player_t *scores)
{
    while (sfRenderWindow_pollEvent(storage->main_window, event)) {
        if ((event)->type == sfEvtClosed)
            sfRenderWindow_close(storage->main_window);
        if (event->type == sfEvtMouseButtonPressed) {
            launch_sound("assets/pistol-shot.ogg", 0, storage);
            iscollision(&(storage->bats), event->mouseButton, scores, storage);
        }
    }
}

static void set_background(sfSprite *background)
{
    sfTexture *back_texture = sfTexture_createFromFile
    ("assets/fond2.jpg", NULL);

    sfSprite_setTexture(background, back_texture, sfTrue);
}

static int handle_frames(game_sys_t *storage, player_t *scores)
{
    sfRenderWindow_clear(storage->main_window, sfBlack);
    sfRenderWindow_drawSprite(storage->main_window,
        storage->background, NULL);
    sfRenderWindow_drawText(storage->main_window,
    scores->score_text, NULL);
    update_score(scores);
    sfRenderWindow_drawText(storage->main_window, scores->tmp_score, NULL);
    draw_bats(&(storage->bats), storage->main_window, scores);
    storage->mytime = sfClock_getElapsedTime(storage->clock);
    storage->bat_time = sfClock_getElapsedTime(storage->bat_clock);
    storage->seconds = storage->mytime.microseconds / 1000000.0;
    storage->bat_seconds = storage->bat_time.microseconds / 1000000.0;
    delete_dead_bats(&(storage->bats));
    sfRenderWindow_display(storage->main_window);
    if (update_clocks(storage) == 84)
        return 84;
    return 0;
}

void destroy_all(game_sys_t *storage)
{
    bat_t *tmp = storage->bats;

    while (tmp != NULL) {
        sfSprite_destroy(tmp->sprite);
        tmp = tmp->next;
    }
    sfClock_destroy(storage->clock);
    sfClock_destroy(storage->bat_clock);
    sfMusic_destroy(storage->music);
    sfSprite_destroy(storage->background);
    sfText_destroy(storage->score->score_text);
    sfFont_destroy(storage->score->font);
    sfRenderWindow_destroy(storage->main_window);
}

void game_loop(game_sys_t *storage, player_t *scores)
{
    storage->position.x = 0;
    set_background(storage->background);
    storage->clock = sfClock_create();
    storage->bat_clock = sfClock_create();
    while (sfRenderWindow_isOpen(storage->main_window)) {
        analyze_event(storage, &(storage->event), scores);
        if (handle_frames(storage, scores))
            sfRenderWindow_close(storage->main_window);
        if (scores->missed >= 3) {
            sfRenderWindow_close(storage->main_window);
            my_putstr("GAME OVER\nScore : ");
            my_put_nbr(scores->score);
        }
    }
    destroy_all(storage);
}

static int conditions(int ac, char **av, game_sys_t *storage, player_t *scores)
{
    sfFont *font = sfFont_createFromFile("assets/Bokor-Regular.ttf");

    scores->font = font;
    scores->score = 0;
    scores->missed = 0;
    scores->tmp_score = sfText_create();
    store_texts(scores, font, storage);
    set_cursor(storage->main_window);
    sfRenderWindow_setFramerateLimit(storage->main_window, 60);
    if (launch_sound("assets/darkest-halloween-night-246680.ogg",
        1, storage) == 84)
        return 84;
    if (ac == 1) {
        game_loop(storage, scores);
        return 0;
    }
    return 84;
}

static int main2(int ac, char **av)
{
    sfVideoMode mode[] = {1919, 1080, 32};
    sfRenderWindow *main_window = sfRenderWindow_create(*mode,
        "MyHunter", sfDefaultStyle, NULL);
    sfEvent event;
    bat_t *bats = NULL;
    sfClock *clock;
    sfClock *bat_clock;
    sfTime mytime;
    sfTime bat_time;
    player_t scores;
    sfSprite *background = sfSprite_create();
    game_sys_t storage = {mode, main_window, event, bats,
        clock, bat_clock, mytime, bat_time, (float)0.0,
        (float)0.0, background, (sfVector2f){0, 0}};

    return conditions(ac, av, &storage, &scores);
}

int main(int ac, char **av)
{
    if (ac == 2 && av[1][1] == 'h') {
        display_h_menu();
        return 0;
    }
    return main2(ac, av);
}
