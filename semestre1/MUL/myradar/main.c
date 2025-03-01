/*
** EPITECH PROJECT, 2024
** my_radar
** File description:
** Main file to open window
*/

#include "radar.h"

static void handle_events(sfRenderWindow *main_window, sfEvent *event,
    int *show_bool)
{
    while (sfRenderWindow_pollEvent(main_window, event)) {
        if (event->type == sfEvtClosed)
            sfRenderWindow_close(main_window);
        if (event->type == sfEvtKeyPressed && event->key.code == sfKeyL)
            show_bool[0] = -1 * show_bool[0];
        if (event->type == sfEvtKeyPressed && event->key.code == sfKeyS)
            show_bool[1] = -1 * show_bool[1];
    }
}

static void show_air(sfRenderWindow *main_window,
    airplane_t *a_tmp, int *show_bool)
{
    if (show_bool[1] == 1)
        sfRenderWindow_drawSprite(main_window, a_tmp->sprite, NULL);
    if (show_bool[0] == 1)
        sfRenderWindow_drawRectangleShape(main_window, a_tmp->box, NULL);
}

static void display_all(struct window_settings *my_set,
    airplane_t **air_storage, tower_t **tow_storage, int *show_bool)
{
    airplane_t *a_tmp = *air_storage;
    tower_t *t_tmp = *tow_storage;
    sfTime delta = sfClock_getElapsedTime(my_set->main_clock);

    while (t_tmp != NULL) {
        if (show_bool[1] == 1)
            sfRenderWindow_drawSprite
                (my_set->main_window, t_tmp->sprite, NULL);
        if (show_bool[0] == 1)
            sfRenderWindow_drawCircleShape
                (my_set->main_window, t_tmp->area, NULL);
        t_tmp = t_tmp->next;
    }
    while (a_tmp != NULL) {
        if (a_tmp->delay <= delta.microseconds / 1000000) {
            show_air(my_set->main_window, a_tmp, show_bool);
        }
        a_tmp = a_tmp->next;
    }
}

static void update_and_display(struct window_settings *my_set,
    tower_t **tow_storage, airplane_t **air_storage, int *show_bool)
{
    sfTime delta;

    delta = sfClock_getElapsedTime(my_set->main_clock);
    sfText_setString(my_set->time_counter,
        int_to_string(delta.microseconds / 1000000));
    sfRenderWindow_clear(my_set->main_window, sfBlack);
    sfRenderWindow_drawSprite(my_set->main_window, my_set->map_sprite, NULL);
    display_all(my_set, air_storage, tow_storage, show_bool);
    sfRenderWindow_drawText(my_set->main_window, my_set->time_counter, NULL);
    delta = sfClock_getElapsedTime(my_set->main_clock);
    update_positions(air_storage, delta);
    check_collisions(my_set, air_storage, tow_storage);
    sfRenderWindow_display(my_set->main_window);
}

static void handle_opened_window(sfRenderWindow *main_window,
    airplane_t **air_storage, tower_t **tow_storage, sfSprite *map_sprite)
{
    sfEvent event;
    sfClock *main_clock = sfClock_create();
    sfText *time_counter = sfText_create();
    sfFont *font = sfFont_createFromFile("assets/font.otf");
    struct window_settings my_set = {main_window,
        map_sprite, main_clock, time_counter};
    int show_bool[2] = {1, 1};

    sfText_setPosition(my_set.time_counter, (sfVector2f){1850, 10});
    sfText_setFont(my_set.time_counter, font);
    while (sfRenderWindow_isOpen(main_window)) {
        handle_events(main_window, &event, show_bool);
        update_and_display(&my_set, tow_storage, air_storage, show_bool);
        if (*air_storage == NULL)
            sfRenderWindow_close(main_window);
    }
    sfClock_destroy(main_clock);
    sfFont_destroy(font);
    sfText_destroy(time_counter);
}

static int manage_window(airplane_t **air_storage, tower_t **tow_storage)
{
    sfVideoMode mode = {1920, 1080, 32};
    sfRenderWindow *main_window = sfRenderWindow_create(mode,
        "My Radar Leandre Fouret", sfDefaultStyle, NULL);
    sfTexture **tab_texture;
    sfTexture *map_texture = sfTexture_createFromFile("assets/map.jpg", NULL);
    sfSprite *map_sprite = sfSprite_create();

    if (!main_window || !map_texture)
        return 84;
    sfSprite_setTexture(map_sprite, map_texture, sfTrue);
    sfRenderWindow_setFramerateLimit(main_window, 60);
    tab_texture = init_elements(air_storage, tow_storage);
    if (!tab_texture)
        return 84;
    handle_opened_window(main_window, air_storage, tow_storage, map_sprite);
    sfSprite_destroy(map_sprite);
    sfTexture_destroy(map_texture);
    free_all(air_storage, tow_storage, tab_texture);
    sfRenderWindow_destroy(main_window);
    return 0;
}

int my_isdigit(char c)
{
    if (c >= '0' && c <= '9')
        return 1;
    return 0;
}

static int check_missing_asset(int *plane_fd, int *tower_fd,
    int *font_fd, int *reverse_fd)
{
    if (*plane_fd == -1 || *tower_fd == -1 ||
        *font_fd == -1 || *reverse_fd == -1) {
        close(*plane_fd);
        close(*tower_fd);
        close(*font_fd);
        close(*reverse_fd);
        my_puterr("Missing asset\n");
        return 84;
    }
    return 0;
}

static int check_exec_main(char **av)
{
    airplane_t *air_storage = NULL;
    tower_t *tow_storage = NULL;
    int plane_fd = open("assets/plane.png", O_RDONLY);
    int tower_fd = open("assets/tower.png", O_RDONLY);
    int font_fd = open("assets/font.otf", O_RDONLY);
    int reverse_fd = open("assets/reverse.png", O_RDONLY);

    if (check_missing_asset(&plane_fd, &tower_fd,
        &font_fd, &reverse_fd) == 84)
        return 84;
    if (verify_file(av[1]) == 84) {
        my_puterr("Wrong configuration file\n");
        return 84;
    }
    extract_file_infos(av[1], &air_storage, &tow_storage);
    return manage_window(&air_storage, &tow_storage);
}

int main(int ac, char **av, char **envp)
{
    int env_index = 0;
    int fd = open(av[1], O_RDONLY);

    if ((ac < 2 || ac > 2) || (fd == -1 && my_strcmp(av[1], "-h") != 0))
        return 84;
    if (my_strcmp(av[1], "-h") == 0) {
        my_putstr("Radar is a simulation of air traffic.\n"
            "The first argument has to be an existing rdr file\n"
            "L and S to switch hitboxes and sprite visibility\n");
        return 0;
    }
    while (1) {
        if (envp[env_index] == NULL)
            return 84;
        if (my_strcmp(envp[env_index], "DISPLAY=:0") == 0)
            break;
        env_index++;
    }
    close(fd);
    return check_exec_main(av);
}
