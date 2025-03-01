/*
** EPITECH PROJECT, 2024
** flag_s
** File description:
** runs the shell
*/

/**
 * @file flag_s.c
 * @brief Execute a shell
 *
 * Execute a shell from the env variable
 */

#include "../../include/my_sudo.h"

/**
 * @brief Create the shell
 *
 * @param *shell The shell path to execute
 * @return void
 */
void spawn_shell(char *shell)
{
    execlp(shell, shell, NULL);
}
