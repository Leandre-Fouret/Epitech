/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** main
*/

#include "amazed.h"

int main(void)
{
    stdin_t **input = malloc(sizeof(stdin_t *));
    room_t **rooms = malloc(sizeof(room_t *));
    amazed_t params = {0, 0, 0, 0, NULL};
    int exit_code = 0;

    if (execute_main(input, rooms) == 84)
        return 84;
    sort_input(rooms, input);
    exit_code = display_and_run(rooms, input, &params);
    free_stdin(input);
    free_rooms(rooms);
    return exit_code;
}
// for (room_t *tmp = *rooms; tmp != NULL; tmp = tmp->next) {
//     printf("%s %s %s\n", tmp->name, tmp->x, tmp->y);
// }
