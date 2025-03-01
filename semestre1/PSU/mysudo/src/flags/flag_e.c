/*
** EPITECH PROJECT, 2024
** flag_E
** File description:
** sanitizing the environment
*/

#include "../../include/my_sudo.h"

int sanitize_without_e(char *username)
{
    char *home = malloc(sizeof(char) * strlen("/home/") + strlen(username));

    if (!home) {
        perror("malloc of sanitizing failed\n");
        return 84;
    }
    sprintf(home, "/home/%s", username);
    setenv("MY_SUDO_USER", username, 1);
    setenv("MY_SUDO_UID", turns_int_to_string(getuid()), 1);
    setenv("MY_SUDO_GID", turns_int_to_string(getgid()), 1);
    setenv("MY_SUDO_HOME", home, 1);
    return 0;
}

int sanitize_environment(char *username)
{
    char *home = "/root";
    char *shell = "/bin/bash";

    clearenv();
    setenv("HOME", home, 1);
    setenv("USER", username, 1);
    setenv("LOGNAME", username, 1);
    setenv("SHELL", shell, 1);
    setenv("MAIL", "/var/mail/user", 1);
    return 0;
}

//Sans -E : HOME USERNAME MAIL. Avec -E : My_SUDO_USER,
//SUDO UID, SUDO GID, SUDO_COMMAND, SUDO_HOME
