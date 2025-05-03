/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** check_main_errors
*/

#include "amazed.h"

int display_and_run(room_t **rooms, stdin_t **input, amazed_t *params)
{
    int rooms_exit = 0;
    int tunnels_exit = 0;
    int algo_exit = 0;

    my_printf("#number_of_robots\n%s\n", (*input)->line);
    params->nb_bots = my_getnbr((*input)->line);
    rooms_exit = browse_line(rooms);
    if (rooms_exit != 84)
        tunnels_exit = browse_tunnels(input, rooms);
    if (rooms_exit != 84 && tunnels_exit != 84)
        algo_exit = run_algo(rooms, input, params);
    return (rooms_exit == 84 || tunnels_exit == 84 ||
        algo_exit == 84) ? 84 : 0;
}

static int check_main_errors(stdin_t **input, room_t **rooms)
{
    if (!input || !rooms) {
        my_puterr("Error allocating memory for stdin_t and"
            " room_t strutures\n");
        free(input);
        free(rooms);
        return 84;
    }
    return 0;
}

int execute_main(stdin_t **input, room_t **rooms)
{
    *input = NULL;
    *rooms = NULL;
    if (check_main_errors(input, rooms) == 84)
        return 84;
    *input = NULL;
    *rooms = NULL;
    store_stdin(input);
    if (check_nb_bots(*input) == 0) {
        my_puterr("The number of robots you entered is invalid.\n");
        free(rooms);
        free_stdin(input);
        return 84;
    }
    return 0;
}
