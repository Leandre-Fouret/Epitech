/*
** EPITECH PROJECT, 2025
** minish2
** File description:
** run_builtins
*/

#include "minish.h"

int run_builtins(params_t *myshell)
{
    int index = myshell->command_index;
    tab_builtins_t tab[NB_BUILT_IN] = {
        {"cd", &my_cd},
        {"setenv", &set_myenv},
        {"env", &display_env},
        {"unsetenv", &unset_myenv},
        {"exit", &my_exit}
    };

    for (int i = 0; i < NB_BUILT_IN; i++) {
        if (my_strcmp(tab[i].command, myshell->user_input[index][0]) == 0) {
            (tab[i].builtin_func)(myshell);
            return 1;
        }
    }
    return 0;
}
