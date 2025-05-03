/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** browse_tunnels
*/

#include "amazed.h"

static int error_wrong_tunnel(char **parsed_line)
{
    my_puterr("Invalid tunnel definition\n");
    free_double_arr(parsed_line);
    return 84;
}

static int room_exists(room_t **rooms, char *tmp_room)
{
    room_t *current = *rooms;

    for (; current; current = current->next) {
        if (my_strcmp(current->name, tmp_room) == 0)
            return 1;
    }
    return 0;
}

static int check_tunnel(char **line, room_t **rooms)
{
    int a_exists = 0;
    int b_exists = 0;

    a_exists = room_exists(rooms, line[0]);
    b_exists = room_exists(rooms, line[1]);
    if (!a_exists || !b_exists) {
        my_puterr("Room does not exists in tunnel definition\n");
        free_double_arr(line);
        return 84;
    }
    return 0;
}

static int loop_tunnels(room_t **rooms, stdin_t *current)
{
    char **parsed_line = NULL;

    while (current) {
        if (current->line == NULL) {
            my_puterr("Remove empty lines\n");
            return 84;
        }
        parsed_line = my_str_to_word_array(current->line, '-');
        if (!parsed_line[0] || !parsed_line[1])
            return error_wrong_tunnel(parsed_line);
        if (check_tunnel(parsed_line, rooms) == 84)
            return 84;
        my_printf("%s\n", current->line);
        free_double_arr(parsed_line);
        current = current->next;
    }
    return 0;
}

int browse_tunnels(stdin_t **input, room_t **rooms)
{
    stdin_t *current = *input;

    for (; current; current = current->next)
        if (is_link(current->line))
            break;
    if (!current) {
        my_puterr("No tunnel detected. Can't find a way.\n");
        return 84;
    }
    my_printf("#tunnels\n");
    return loop_tunnels(rooms, current);
}
