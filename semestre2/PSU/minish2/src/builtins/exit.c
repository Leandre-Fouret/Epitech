/*
** EPITECH PROJECT, 2025
** minish2
** File description:
** exit
*/

#include "minish.h"

void my_exit(params_t *myshell)
{
    int index = myshell->command_index;

    if (my_strcmp((const char *) myshell->user_input[index][0], "exit") == 0) {
        myshell->exit_code = (myshell->user_input[1] == NULL)
            ? myshell->exit_code :
            my_getnbr((const char *)myshell->user_input[index][1]);
        myshell->to_exit = 1;
    }
}
