/*
** EPITECH PROJECT, 2024
** other
** File description:
** other functions
*/

#include "hunter.h"
#include "my.h"
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/System.h>
#include <stdlib.h>

void display_h_menu(void)
{
    my_putstr("This my hunter is a 'duck hunt' game made by Léandre Fouret\n");
    my_putstr("To increase your score, you have to shoot on the bats.\n");
    my_putstr("This game ends when three bats reach ");
    my_putstr("the other side of the screen...\n");
}

void set_cursor(sfRenderWindow *main_window)
{
    sfImage *cursor_pic = sfImage_createFromFile("assets/target.png");
    sfCursor* cursor = sfCursor_createFromPixels(
        sfImage_getPixelsPtr(cursor_pic), sfImage_getSize(cursor_pic),
        (sfVector2u){0, 0});

    sfWindow_setMouseCursor((sfWindow *)main_window, cursor);
}

static char *int_to_string(int num)
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

void update_score(player_t *scores)
{
    char *converted = int_to_string(scores->score);

    sfText_setString(scores->tmp_score, converted);
    free(converted);
}

void store_texts(player_t *scores, sfFont *font, game_sys_t *storage)
{
    scores->score_text = sfText_create();
    sfText_setFont(scores->score_text, font);
    sfText_setString(scores->score_text, "Score : ");
    sfText_setCharacterSize(scores->score_text, 50);
    sfText_setColor(scores->score_text, sfRed);
    sfText_setPosition(scores->score_text, (sfVector2f){50, 50});
    sfText_setFont(scores->tmp_score, font);
    sfText_setCharacterSize(scores->tmp_score, 50);
    sfText_setColor(scores->tmp_score, sfRed);
    sfText_setPosition(scores->tmp_score, (sfVector2f){50, 120});
    storage->score = scores;
}

int launch_sound(char *path, int repeat, game_sys_t *storage)
{
    sfMusic *music = sfMusic_createFromFile(path);

    storage->music = music;
    if (!music)
        return 84;
    if (repeat) {
        sfMusic_setLoop(music, sfTrue);
        sfMusic_setVolume(music, 40.0f);
    }
    sfMusic_play(music);
    return 0;
}
